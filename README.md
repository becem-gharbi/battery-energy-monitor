# Battery Energy monitor

![manual](https://raw.githubusercontent.com/becem-gharbi/battery-energy-monitor/main/Documents/manual.jpg)  

An embedded device that periodically reads a battery voltage and current through shunt resistor. Then saves the measurement to a Micro SD card. The output files can further be uploaded to a web app which displays the current, voltage and power graphs interactively.

## Hardware

- Microcontroller ESP8266 E12 module
- Analog multiplexing using CD4053
- Voltage sensing up to 84V
- Bidirectional current sensing up to 27A
- Analog filtering & buffering using LM348 opamp
- RTC using DS1302
- Designed with Proteus v8.12

## Firmware

- Platform espressif8266
- Framework arduino
- IDE Platform IO

## Web app

- Built with Nuxt 3
- Interactive charts via Highcharts library
- UI components based on NaiveUI library
- UI utilities via Tailwindcss

## Settings

The device can be setup via `settings.json` file, which should be placed and read from SD card.

| Field         | Value                                              | Notes                                  |
| ------------- | -------------------------------------------------- | -------------------------------------- |
| debug         | Enable firmware debugging                          | Should be set to 0 on production       |
| sampleRate    | The rate of analog reading in ms                   | Should be larger than 300ms            |
| savingRate    | The rate of writing to SD card in ms               | Should be larger than sampleRate       |
| currentGain   | The gain by which the analog reading is multiplied | Emperical or by calibration calculator |
| currentOffset | The offset by which the analog reading is biased   | Emperical or by calibration calculator |
| voltageGain   | The gain by which the analog reading is multiplied | Emperical or by calibration calculator |
| voltageOffset | The offset by which the analog reading is biased   | Emperical or by calibration calculator |

## Notes

- The design of analog circuits is based on TI notes located under `/documents`.
- For components dimensioning refer to `Calibration.xlsx` sheet.
- The functioning of the circuit is supposed to be linear. Saturation should be taken into consideration, e.g LM358 output is saturated around 3.6V on 5V supply voltage.
- ESP8266's ADC transfer function should be defined empirically for precise measurement.
- The folder `battery_energy_monitor` located under `Place content inside in SD` should be placed at the root directory of the SD card. Then should be uploaded to the web app.