
/*
  SD
    DI/MOSI -> GPIO13
    DO/MISO -> GPIO12
    SCK     -> GPIO14
    CS      -> GPIO15

  RTC
    RST/CE   -> GPIO2
    DAT/IO   -> GPIO4
    CLK/SCLK -> GPIO5

  ADC_MUX
    CMD      -> GPIO16
*/

#include <Arduino.h>
#include <Ticker.h>
#include <rtc.h>
#include <adc_mux.h>
#include <storage.h>

#define RTC_IO_PIN 4
#define RTC_SCLK_PIN 5
#define RTC_CE_PIN 2
#define SD_CS_PIN 15
#define ADC_MUX_CMD_PIN 16

#define SAMPLE_RATE 1

Rtc rtc(RTC_IO_PIN, RTC_SCLK_PIN, RTC_CE_PIN);
AdcMux adcMux(ADC_MUX_CMD_PIN);
Storage storage(SD_CS_PIN);
Ticker ticker;

bool timeElapsed = false;

void setTime(uint16_t *date, uint16_t *time)
{
  RtcDateTime now = rtc.getTime();
  *date = FAT_DATE(now.Year(), now.Month(), now.Day());
  *time = FAT_TIME(now.Hour(), now.Minute(), now.Second());
}

void setup()
{
  Serial.begin(9600);

  while (!Serial)
  {
    continue;
  }

  rtc.begin();

  storage.begin(setTime);

  adcMux.begin(storage.settings.data.adcMuxCtrlDelayMs);

  String timestamp = rtc.getTimeStr();

  storage.createSession(timestamp);

  Measurement mes;
  mes.current = 10;
  mes.voltage = 70;
  mes.timestamp = 0;

  storage.saveMeasurement(mes);

  ticker.attach(storage.settings.data.sampleRateMs / 1000.0, []
                { timeElapsed = true; });
}

void loop()
{
  adcMux.update();

  if (timeElapsed)
  {
    timeElapsed = false;
  }
}
