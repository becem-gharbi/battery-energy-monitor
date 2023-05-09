#include <storage.h>

Storage::Storage(byte csPin)
{
    _csPin = csPin;
}

bool Storage::begin(void (*cb)(uint16_t *, uint16_t *))
{
    if (!SD.begin(_csPin))
    {
        Serial.println("[storage] failed to initialize sd");
        return false;
    }

    delay(1000);

    SD.dateTimeCallback(cb);

    Serial.println("[storage] sd initialized");

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
        Serial.println("[storage] file <settings.json> not found, using default settings");
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

    Serial.println("[storage] settings loaded");
    settingsFile.close();

    return true;
}

bool Storage::createSession(String timestamp)
{
    _sessionFilename = SESSION_FILE_PATH(timestamp);

    File sessionFile = SD.open(_sessionFilename, FILE_WRITE);

    if (!sessionFile)
    {
        Serial.println("[storage] failed to create session file");
        return false;
    }

    String headers = "Timestamp,Current,Voltage";

    if (sessionFile.println(headers) == 0)
    {
        Serial.println("[storage] failed to write to session file");
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
    unsigned long start = millis();

    File sessionFile = SD.open(_sessionFilename, FILE_WRITE);

    if (!sessionFile)
    {
        Serial.println("[storage] failed to open session file");
        return false;
    }

    if (sessionFile.print(_measurementsStr) == 0)
    {
        Serial.println("[storage] failed to write to session file");
        return false;
    }

    sessionFile.close();

    // A workaround to ensure data is saved
    SD.open(_sessionFilename);

    _measurementsStr = "";

    unsigned long stop = millis();

    Serial.print("[storage] measurements saved in ");
    Serial.print(stop - start);
    Serial.println(" ms");

    return true;
}
