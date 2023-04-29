
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
*/

#include <Arduino.h>
#include <rtc.h>
#include <SPI.h>
#include <SD.h>

File myFile;
Rtc rtc(4, 5, 2);
String timestamp;

void setup()
{
  Serial.begin(115200);

  rtc.begin();

  if (!SD.begin(15))
  {
    Serial.println("[SD] initialization failed");
    return;
  }

  Serial.println("[SD] initialized");
}

void loop()
{
  timestamp = rtc.getTimestamp();
  Serial.println(timestamp);
  delay(5000);
}
