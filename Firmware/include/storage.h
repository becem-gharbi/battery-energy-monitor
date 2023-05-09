#ifndef STORAGE_H
#define STORAGE_H

#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <models.h>

#define SETTINGS_FILE_PATH "battery_energy_monitor/settings.json"
#define SESSION_FILE_PATH(timestamp) ("battery_energy_monitor/sessions/" + timestamp + ".csv")
#define ADC_MUX_CTRL_DELAY_MS 5
#define SAMPLE_RATE_MS 1000
#define SAVING_RATE_MS 1500
#define SETTINGS_DOC_SIZE 384

class Storage
{
public:
    Storage(byte csPin);
    bool begin(void (*cb)(uint16_t *, uint16_t *));
    Settings settings;
    bool createSession(String timestamp);
    void keepMeasurement(Measurement measurement);
    bool saveMeasurements();

private:
    byte _csPin;
    String _sessionFilename;
    bool _loadSettings();
    String _measurementsStr;
};

#endif