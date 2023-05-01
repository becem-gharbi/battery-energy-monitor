#ifndef STORAGE_H
#define STORAGE_H

#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>
#include <models.h>

#define SETTINGS_FILE_PATH "battery_energy_monitor/settings.json"
#define SESSION_FILE_PATH(timestamp) ("battery_energy_monitor/sessions/" + timestamp + ".csv")
#define ADC_MUX_CTRL_DELAY_MS 5
#define SAMPLE_RATE_MS 500
#define SETTINGS_DOC_SIZE 500

class Storage
{
public:
    Storage(u_int8_t csPin);
    void begin(void (*cb)(uint16_t *, uint16_t *));
    Settings settings;
    void createSession(String timestamp);
    void keepMeasurement(Measurement measurement);
    void saveMeasurements();

private:
    u_int8_t _csPin;
    File _sessionFile;
    void _loadSettings();
    String _measurementsStr;
};

#endif