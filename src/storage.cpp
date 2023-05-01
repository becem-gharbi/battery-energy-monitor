#include <storage.h>

Storage::Storage(u_int8_t csPin)
{
    _csPin = csPin;
}

void Storage::begin(void (*cb)(uint16_t *, uint16_t *))
{
    if (!SD.begin(_csPin))
    {
        Serial.println("[storage] failed to initialize sd");
        return;
    }

    delay(1000);

    SD.dateTimeCallback(cb);

    Serial.println("[storage] sd initialized");

    _loadSettings();
}

void Storage::_loadSettings()
{
    File settingsFile = SD.open(SETTINGS_FILE_PATH, FILE_READ);

    StaticJsonDocument<SETTINGS_DOC_SIZE> settingsDoc;
    DeserializationError error = deserializeJson(settingsDoc, settingsFile);

    if (error)
    {
        Serial.println("[storage] file <settings.json> not found, using default settings");
    }

    settings.data.adcMuxCtrlDelayMs = settingsDoc["data"]["adcMuxCtrlDelayMs"] | ADC_MUX_CTRL_DELAY_MS;
    settings.data.sampleRateMs = settingsDoc["data"]["sampleRateMs"] | SAMPLE_RATE_MS;

    Serial.println("[storage] settings loaded");
    settingsFile.close();
}

void Storage::createSession(String timestamp)
{
    String filename = SESSION_FILE_PATH(timestamp);

    _sessionFile = SD.open(filename, FILE_WRITE);

    if (!_sessionFile)
    {
        Serial.println("Failed to create session file");
        return;
    }

    String headers = "Timestamp,Current,Voltage";

    _sessionFile.println(headers);

    _sessionFile.close();

    _sessionFile = SD.open(filename, FILE_WRITE);
}

void Storage::saveMeasurements(Measurement measurements[], u_int8_t length)
{
    Serial.println(length);

    for (u_int8_t i = 0; i < length; i++)
    {
        Measurement measurement = measurements[i];

        String measurementStr = String(measurement.timestamp) + "," + String(measurement.current) + "," + String(measurement.voltage);

        _sessionFile.println(measurementStr);

        _sessionFile.flush();
    }
}