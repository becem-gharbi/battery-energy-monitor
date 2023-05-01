#ifndef RTC_H
#define RTC_

#include <RtcDS1302.h>

class Rtc
{
public:
    Rtc(int8_t ioPin, int8_t sclkPin, int8_t cePin);
    bool begin();
    String getTimeStr();
    RtcDateTime getTime();

private:
    ThreeWire _wire;
    RtcDS1302<ThreeWire> _ds1302;
};

#endif
