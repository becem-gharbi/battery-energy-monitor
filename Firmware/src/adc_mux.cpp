#include <adc_mux.h>

AdcMux::AdcMux(u_int8_t cmdPin)
{
     _cmdPin = cmdPin;
}

void AdcMux::begin(u_int8_t ctrlDelayMs)
{
     _ctrlDelayMs = ctrlDelayMs;

     pinMode(_cmdPin, OUTPUT);

     _timeDiff = millis();
     timestamp = 0;

     for (u_int8_t i = 0; i < NBR_OF_CHANNELS; i++)
     {
          _control(i);

          values[0] = _read();
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

     delay(_ctrlDelayMs);
}

void AdcMux::update()
{
     timestamp = millis() - _timeDiff;

     for (u_int8_t i = 0; i < NBR_OF_CHANNELS; i++)
     {
          _control(i);

          values[i] = _read();
     }
}

int AdcMux::_read()
{
     return analogRead(ANALOG_PIN);
}