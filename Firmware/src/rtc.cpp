#include <rtc.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

Rtc::Rtc(byte ioPin, byte sclkPin, byte cePin) : _wire(ioPin, sclkPin, cePin), _ds1302(_wire)
{
}

bool Rtc::begin()
{
    _ds1302.Begin();

    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

    if (!_ds1302.IsDateTimeValid())
    {
        // Common Causes:
        //    1) first time you ran and the device wasn't running yet
        //    2) the battery on the device is low or even missing

        Serial.println("[rtc] lost confidence in the DateTime");
        _ds1302.SetDateTime(compiled);
    }

    if (_ds1302.GetIsWriteProtected())
    {
        Serial.println("[rtc] was write protected, enabling writing now");
        _ds1302.SetIsWriteProtected(false);
    }

    if (!_ds1302.GetIsRunning())
    {
        Serial.println("[rtc] was not actively running, starting now");
        _ds1302.SetIsRunning(true);
    }

    RtcDateTime now = getTime();

    if (now < compiled)
    {
        Serial.println("[rtc] is older than compile time!  (Updating DateTime)");
        _ds1302.SetDateTime(compiled);
    }
    else if (now > compiled)
    {
        Serial.println("[rtc] is newer than compile time. (this is expected)");
    }
    else if (now == compiled)
    {
        Serial.println("[rtc] is the same as compile time! (not expected but all is fine)");
    }

    return now.IsValid();
}

String Rtc::getTimeStr()
{
    RtcDateTime now = getTime();

    char timestamp[20];

    snprintf_P(timestamp,
               countof(timestamp),
               PSTR("%04u-%02u-%02u_%02u-%02u-%02u"), // Format YYYY-MM-DD_HH-MM-SS
               now.Year(),
               now.Month(),
               now.Day(),
               now.Hour(),
               now.Minute(),
               now.Second());

    return timestamp;
}

RtcDateTime Rtc::getTime()
{
    RtcDateTime now = _ds1302.GetDateTime();

    return now;
}