#include <storage.h>

Storage::Storage(u_int8_t csPin)

{
    _csPin = csPin;
}

void Storage::begin()
{
    if (!SD.begin(_csPin))
    {
        Serial.println("[storage] failed to initialize sd");
        return;
    }

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
    _sessionFile = SD.open(SESSION_FILE_PATH(timestamp), FILE_WRITE);
}