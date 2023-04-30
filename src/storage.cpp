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

    StaticJsonDocument<METADATA_DOC_SIZE> metadataDoc;
    JsonObject metadata = metadataDoc.createNestedObject("metadata");

    metadata["createdAt"] = timestamp;
    metadata["updatedAt"] = timestamp;

    if (serializeJson(metadataDoc, _sessionFile) == 0)
    {
        Serial.println("Failed to write to session file");
    }

    _sessionFile.close();

    _sessionFile = SD.open(filename, FILE_WRITE);
}