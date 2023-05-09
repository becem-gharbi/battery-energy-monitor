#ifndef ADC_MUX_H
#define ADC_MUX_H

#include <Arduino.h>

#define NBR_OF_CHANNELS 2
#define ANALOG_PIN A0
class AdcMux
{
public:
    AdcMux(byte cmdPin);
    void begin();
    int values[NBR_OF_CHANNELS];
    unsigned long time;
    void update();

private:
    byte _cmdPin;
    void _control(byte cmd);
    unsigned long _timeDiff;
    int _read();
};

#endif