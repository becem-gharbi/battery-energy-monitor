#ifndef RTC_H
#define RTC_

#include <RtcDS1302.h>

class Rtc
{
public:
    Rtc(byte ioPin, byte sclkPin, byte cePin);
    bool begin();
    String getTimeStr();
    RtcDateTime getTime();

private:
    ThreeWire _wire;
    RtcDS1302<ThreeWire> _ds1302;
    String _timeToStr(RtcDateTime time);
};

#endif
