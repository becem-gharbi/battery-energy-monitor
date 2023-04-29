
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
#include <rtc.h>
#include <SPI.h>
#include <SD.h>
#include <Ticker.h>
#include <adc_mux.h>

#define RTC_IO_PIN 4
#define RTC_SCLK_PIN 5
#define RTC_CE_PIN 2
#define SD_CS_PIN 15
#define ADC_MUX_CMD_PIN 16

#define SAMPLE_RATE 1

Rtc rtc(RTC_IO_PIN, RTC_SCLK_PIN, RTC_CE_PIN);
String timestamp;
File myFile;
Ticker ticker;
AdcMux adcMux(ADC_MUX_CMD_PIN);

bool timeElapsed = false;

void setup()
{
  Serial.begin(115200);

  rtc.begin();

  if (!SD.begin(SD_CS_PIN))
  {
    Serial.println("[SD] initialization failed");
    return;
  }

  Serial.println("[SD] initialized");

  adcMux.begin();

  ticker.attach(SAMPLE_RATE, []
                { timeElapsed = true; });
}

void loop()
{
  adcMux.update();

  // Serial.print("[ADC 1] ");
  // Serial.println(adcMux.values[0]);

  if (timeElapsed)
  {
    timeElapsed = false;
    timestamp = rtc.getTimestamp();
    Serial.println(timestamp);
  }
}
