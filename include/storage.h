#ifndef STORAGE_H
#define STORAGE_H

#include <SPI.h>
#include <SD.h>

class Storage
{
public:
    Storage(u_int8_t csPin);
    void begin();
    File file;

private:
    u_int8_t _csPin;
};

#endif