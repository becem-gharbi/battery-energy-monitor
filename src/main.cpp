#include <Arduino.h>
#include <rtc.h>

Rtc rtc(20, 21, 2);
String timestamp;

void setup()
{
  Serial.begin(9600);
  rtc.begin();
}

void loop()
{
  timestamp = rtc.getTimestamp();
  Serial.println(timestamp);
  delay(5000);
}
