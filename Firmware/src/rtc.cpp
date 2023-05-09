#include <rtc.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

Rtc::Rtc(byte ioPin, byte sclkPin, byte cePin) : _wire(ioPin, sclkPin, cePin), _ds1302(_wire)
{
}

bool Rtc::begin()
{
    _ds1302.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    Serial.printf("[rtc] compiled time %s \n", _timeToStr(compiled).c_str());

    if (!_ds1302.IsDateTimeValid())
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.printf("[rtc] lost confidence in the DateTime \n");
        _ds1302.SetDateTime(compiled);
    }

    if (_ds1302.GetIsWriteProtected())
    {
        Serial.printf("[rtc] was write protected, enabling writing now \n");
        _ds1302.SetIsWriteProtected(false);
    }

    if (!_ds1302.GetIsRunning())
    {
        Serial.printf("[rtc] was not actively running, starting now \n");
        _ds1302.SetIsRunning(true);
    }

    RtcDateTime now = getTime();

    if (now < compiled)
    {
        Serial.printf("[rtc] is older than compile time!  (Updating DateTime) \n");
        _ds1302.SetDateTime(compiled);
    }
    else if (now > compiled)
    {
        Serial.printf("[rtc] is newer than compile time. (this is expected) \n");
    }
    else if (now == compiled)
    {
        Serial.printf("[rtc] is the same as compile time! (not expected but all is fine) \n");
    }

    return now.IsValid();
}

String Rtc::getTimeStr()
{
    RtcDateTime now = getTime();

    return _timeToStr(now);
}

String Rtc::_timeToStr(RtcDateTime time)
{
    char timestamp[20];

    snprintf_P(timestamp,
               countof(timestamp),
               PSTR("%04u-%02u-%02u_%02u-%02u-%02u"), // Format YYYY-MM-DD_HH-MM-SS
               time.Year(),
               time.Month(),
               time.Day(),
               time.Hour(),
               time.Minute(),
               time.Second());

    return timestamp;
}

RtcDateTime Rtc::getTime()
{
    RtcDateTime now = _ds1302.GetDateTime();

    return now;
}