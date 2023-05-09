/*
  SD
    DI/MOSI -> GPIO13 / D7 ok
    DO/MISO -> GPIO12 / D6 ok
    SCK     -> GPIO14 / D5 ok
    CS      -> GPIO15 / D8 unexpected behaviour at boot

  RTC
    RST/CE   -> GPIO0 / D3 ok
    DAT/IO   -> GPIO4 / D2 ok
    CLK/SCLK -> GPIO5 / D1 ok

  ADC_MUX
    CMD      -> GPIO16 / D0 ok

  LEDS
    ERROR_LED_PIN    -> GPIO2 / D4 / builtin led / PULLED UP
*/

#include <Arduino.h>
#include <Ticker.h>
#include <rtc.h>
#include <adc_mux.h>
#include <storage.h>

#define RTC_IO_PIN 4
#define RTC_SCLK_PIN 5
#define RTC_CE_PIN 0
#define SD_CS_PIN 15
#define ADC_MUX_CMD_PIN 16
#define ERROR_LED_PIN 2

#define SAMPLE_RATE 1

Rtc rtc(RTC_IO_PIN, RTC_SCLK_PIN, RTC_CE_PIN);
AdcMux adcMux(ADC_MUX_CMD_PIN);
Storage storage(SD_CS_PIN);
Ticker sampleTicker;
Ticker savingTicker;

bool sampleTrigger = true;
bool savingTrigger = true;
bool errorFound = false;

void setTime(uint16_t *date, uint16_t *time)
{
  RtcDateTime now = rtc.getTime();
  *date = FAT_DATE(now.Year(), now.Month(), now.Day());
  *time = FAT_TIME(now.Hour(), now.Minute(), now.Second());
}

void setup()
{
  Serial.begin(9600);

  pinMode(ERROR_LED_PIN, OUTPUT);
  digitalWrite(ERROR_LED_PIN, HIGH);

  while (!Serial)
  {
    continue;
  }
  Serial.printf("\n");

  errorFound = errorFound || !rtc.begin();

  errorFound = errorFound || !storage.begin(setTime);

  String timestamp = rtc.getTimeStr();

  errorFound = errorFound || !storage.createSession(timestamp);

  if (errorFound)
  {
    return;
  }

  if (storage.settings.debug == 1)
  {
    Serial.printf("================= Time =================\n");
    Serial.printf("%s \n", timestamp.c_str());
    Serial.printf("=============== Settings ===============\n");
    Serial.printf("Sample Rate = %d \n", storage.settings.sampleRateMs);
    Serial.printf("Saving Rate = %d \n", storage.settings.savingRateMs);
    Serial.printf("Current Gain = %f \n", storage.settings.currentGain);
    Serial.printf("Current offset = %f \n", storage.settings.currentOffset);
    Serial.printf("Voltage Gain = %f \n", storage.settings.voltageGain);
    Serial.printf("Voltage offset = %f \n", storage.settings.voltageOffset);
    Serial.printf("========================================\n");
  }

  sampleTicker.attach(storage.settings.sampleRateMs / 1000.0, []
                      { sampleTrigger = true; });

  savingTicker.attach(storage.settings.savingRateMs / 1000.0, []
                      { savingTrigger = true; });

  adcMux.begin();
}

void loop()
{
  if (errorFound)
  {
    digitalWrite(ERROR_LED_PIN, LOW);
    return;
  }

  if (sampleTrigger)
  {
    sampleTrigger = false;

    Measurement measurement;
    measurement.voltage = adcMux.values[0] * storage.settings.voltageGain + storage.settings.voltageOffset;
    measurement.current = adcMux.values[1] * storage.settings.currentGain + storage.settings.currentOffset;
    measurement.time = adcMux.time;

    if (storage.settings.debug == 1)
    {
      Serial.printf("Current_a = %f | Current_d = %d | ", measurement.current, adcMux.values[1]);
      Serial.printf("Voltage_a = %f | Voltage_d = %d \n", measurement.voltage, adcMux.values[0]);
    }

    storage.keepMeasurement(measurement);
  }

  if (savingTrigger)
  {
    savingTrigger = false;

    errorFound = !storage.saveMeasurements();
  }

  adcMux.update();
}
