# Battery Energy monitor

An embedded device that periodically reads a battery voltage and current through shunt resistor. Then saves the measurement to a Micro SD card. The output files can further be uploaded to a web app which displays the current, voltage and power graphs interactively.

## Hardware
- Microcontroller ESP8266 E12 module
- Analog multiplexing with CD4053 
- Voltage sensing up to 84V
- Bidirectional current sensing up to 27A
- Analog filtering & buffering with LM348 opamp

## Firmware
- Platform espressif8266
- Framework arduino
- IDE Platform IO

## Web app
- Built with Nuxt 3
- Interactive charts via Highcharts library
- UI components based on NaiveUI library
- UI utilities via Tailwindcss
