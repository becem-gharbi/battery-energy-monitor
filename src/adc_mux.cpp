#include <adc_mux.h>

AdcMux::AdcMux(u_int8_t cmdPin)
{
     _cmdPin = cmdPin;
}

void AdcMux::begin()
{
     pinMode(_cmdPin, OUTPUT);

     for (u_int8_t i = 0; i < NBR_OF_CHANNELS; i++)
     {
          _control(i);

          values[0] = analogRead(A0);
     }
}

void AdcMux::_control(u_int8_t cmd)
{
     switch (cmd)
     {
     case 0:
          digitalWrite(_cmdPin, LOW);
          break;
     case 1:
          digitalWrite(_cmdPin, HIGH);
          break;
     }

     delay(5);
}

void AdcMux::update()
{
     for (u_int8_t i = 0; i < NBR_OF_CHANNELS; i++)
     {
          _control(i);

          values[i] = (values[i] + analogRead(A0)) / 2;
     }
}