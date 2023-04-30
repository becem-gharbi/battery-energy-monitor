#include <storage.h>

Storage::Storage(u_int8_t csPin)

{
    _csPin = csPin;
}

void Storage::begin()
{
    if (!SD.begin(_csPin))
    {
        Serial.println("[SD] initialization failed");
        return;
    }

    Serial.println("[SD] initialized");
}