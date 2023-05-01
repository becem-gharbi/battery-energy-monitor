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
    settings.data.savingRateMs = settingsDoc["data"]["savingRateMs"] | SAVING_RATE_MS;

    Serial.println("[storage] settings loaded");
    settingsFile.close();
}

void Storage::createSession(String timestamp)
{
    _sessionFilename = SESSION_FILE_PATH(timestamp);

    File sessionFile = SD.open(_sessionFilename, FILE_WRITE);

    if (!sessionFile)
    {
        Serial.println("[storage] failed to create session file");
        return;
    }

    String headers = "Timestamp,Current,Voltage";

    sessionFile.println(headers);

    sessionFile.close();
}

void Storage::keepMeasurement(Measurement measurement)
{
    String newMeasurementStr = String(measurement.timestamp) + "," + String(measurement.current) + "," + String(measurement.voltage) + "\n";

    _measurementsStr += newMeasurementStr;
}

/*
Don't forget to find the time taken by this function to return
*/
void Storage::saveMeasurements()
{
    unsigned long start = millis();

    File sessionFile = SD.open(_sessionFilename, FILE_WRITE);

    if (!sessionFile)
    {
        Serial.println("[storage] failed to open session file");
        return;
    }

    sessionFile.print(_measurementsStr);

    sessionFile.close();

    // A workaround to ensure data is saved
    SD.open(_sessionFilename);

    _measurementsStr = "";

    unsigned long stop = millis();

    Serial.print("[storage] measurements saved in ");
    Serial.print(stop - start);
    Serial.println(" ms");
}
