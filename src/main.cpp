
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
String timestamp;
Ticker ticker;

bool timeElapsed = false;

void setup()
{
  Serial.begin(115200);

  storage.begin();

  rtc.begin();

  adcMux.begin();

  ticker.attach(SAMPLE_RATE, []
                { timeElapsed = true; });
}

void loop()
{
  adcMux.update();

  if (timeElapsed)
  {
    timeElapsed = false;
    timestamp = rtc.getTimestamp();
    // Serial.println(timestamp);
  }
}
