#include <adc_mux.h>

AdcMux::AdcMux(byte cmdPin)
{
     _cmdPin = cmdPin;
}

void AdcMux::begin()
{
     pinMode(_cmdPin, OUTPUT);

     _timeDiff = millis();
     time = 0;

     for (byte i = 0; i < NBR_OF_CHANNELS; i++)
     {
          _control(i);

          values[i] = _read();
     }
}

void AdcMux::_control(byte cmd)
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

     delay(2);
}

void AdcMux::update()
{
     time = millis() - _timeDiff;

     for (byte i = 0; i < NBR_OF_CHANNELS; i++)
     {
          _control(i);

          values[i] = (values[i] * 9 + _read()) / 10;
     }
}

int AdcMux::_read()
{
     return analogRead(ANALOG_PIN);
}