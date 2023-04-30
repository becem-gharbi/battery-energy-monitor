#include <rtc.h>

#define countof(a) (sizeof(a) / sizeof(a[0]))

Rtc::Rtc(int8_t ioPin, int8_t sclkPin, int8_t cePin) : _wire(ioPin, sclkPin, cePin), _ds1302(_wire)
{
}

void Rtc::begin()
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

    RtcDateTime now = _ds1302.GetDateTime();

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
}

String Rtc::getTimestamp()
{
    RtcDateTime now = _ds1302.GetDateTime();

    if (!now.IsValid())
    {
        // Common Causes:
        //    1) the battery on the device is low or even missing and the power line was disconnected
        Serial.println("[rtc] lost confidence in the DateTime!");
        return "error";
    }
    else
    {

        char timestamp[20];

        snprintf_P(timestamp,
                   countof(timestamp),
                   PSTR("%02u-%02u-%04u-%02u-%02u-%02u"),
                   now.Day(),
                   now.Month(),
                   now.Year(),
                   now.Second(),
                   now.Minute(),
                   now.Hour());

        return timestamp;
    }
}