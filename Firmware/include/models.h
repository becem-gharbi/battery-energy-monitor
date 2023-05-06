#ifndef MODELS_H
#define MODELS_H

#include <Arduino.h>

typedef struct SettingsData
{
    u_int16_t sampleRateMs;
    u_int8_t adcMuxCtrlDelayMs;
    u_int16_t savingRateMs;
    float currentFactor;
    float voltageFactor;
} SettingsData;

typedef struct Metadata
{
    String createdAt;
    String updatedAt;
} Metadata;

typedef struct Settings
{
    Metadata metadata;
    SettingsData data;
} Settings;

typedef struct Measurement
{
    float current;
    float voltage;
    u_int16_t timestamp;
} Measurement;

typedef struct Session
{
    Metadata metadata;
    Measurement data[];
} Session;

#endif