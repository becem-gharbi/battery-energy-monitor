#ifndef ADC_MUX_H
#define ADC_MUX_H

#include <Arduino.h>

#define NBR_OF_CHANNELS 2

class AdcMux
{
public:
    AdcMux(u_int8_t cmdPin);
    void begin();
    u_int16_t values[NBR_OF_CHANNELS];
    void update();

private:
    u_int8_t _cmdPin;
    void _control(u_int8_t);
};

#endif