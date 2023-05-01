#ifndef ADC_MUX_H
#define ADC_MUX_H

#include <Arduino.h>

#define NBR_OF_CHANNELS 2
#define ANALOG_PIN A0
class AdcMux
{
public:
    AdcMux(u_int8_t cmdPin);
    void begin(u_int8_t ctrlDelayMs);
    u_int16_t values[NBR_OF_CHANNELS];
    u_int16_t timestamp;
    void update();

private:
    u_int8_t _cmdPin;
    void _control(u_int8_t);
    u_int8_t _ctrlDelayMs;
    u_int16_t _timeDiff;
};

#endif