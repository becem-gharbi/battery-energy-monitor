#include <storage.h>

Storage::Storage(byte csPin)
{
    _csPin = csPin;
}

bool Storage::begin(void (*cb)(uint16_t *, uint16_t *))
{
    if (!SD.begin(_csPin))
    {
        Serial.printf("[storage] failed to initialize sd \n");
        return false;
    }

    delay(1000);

    SD.dateTimeCallback(cb);

    Serial.printf("[storage] sd initialized \n");

    return _loadSettings();
}

bool Storage::_loadSettings()
{
    File settingsFile = SD.open(SETTINGS_FILE_PATH, FILE_READ);

    if (!settingsFile)
    {
        return false;
    }

    StaticJsonDocument<SETTINGS_DOC_SIZE> settingsDoc;
    DeserializationError error = deserializeJson(settingsDoc, settingsFile);

    if (error)
    {
        Serial.printf("[storage] file <settings.json> not found, using default settings \n");
        return false;
    }

    JsonObject data = settingsDoc["data"];

    settings.debug = data["debug"];
    settings.sampleRateMs = data["sampleRateMs"] | SAMPLE_RATE_MS;
    settings.savingRateMs = data["savingRateMs"] | SAVING_RATE_MS;
    settings.currentGain = data["currentGain"];
    settings.currentOffset = data["currentOffset"];
    settings.voltageGain = data["voltageGain"];
    settings.voltageOffset = data["voltageOffset"];

    Serial.printf("[storage] settings loaded \n");
    settingsFile.close();

    return true;
}

bool Storage::createSession(String timestamp)
{
    _sessionFilename = SESSION_FILE_PATH(timestamp);

    File sessionFile = SD.open(_sessionFilename, FILE_WRITE);

    if (!sessionFile)
    {
        Serial.printf("[storage] failed to create session file \n");
        return false;
    }

    String headers = "Timestamp,Current,Voltage";

    if (sessionFile.println(headers) == 0)
    {
        Serial.printf("[storage] failed to write to session file \n");
        return false;
    }

    sessionFile.close();

    return true;
}

void Storage::keepMeasurement(Measurement measurement)
{
    String newMeasurementStr = String(measurement.time) + "," + String(measurement.current) + "," + String(measurement.voltage) + "\n";

    _measurementsStr += newMeasurementStr;
}

bool Storage::saveMeasurements()
{
    File sessionFile = SD.open(_sessionFilename, FILE_WRITE);

    if (!sessionFile)
    {
        Serial.printf("[storage] failed to open session file \n");
        return false;
    }

    if (sessionFile.print(_measurementsStr) == 0)
    {
        Serial.printf("[storage] failed to write to session file \n");
        return false;
    }

    sessionFile.close();

    // A workaround to ensure data is saved
    SD.open(_sessionFilename);

    _measurementsStr = "";

    return true;
}
