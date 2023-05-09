#ifndef MODELS_H
#define MODELS_H

#include <Arduino.h>

typedef struct Settings
{
    byte debug;
    unsigned int sampleRateMs;
    unsigned int savingRateMs;
    float currentGain;
    float currentOffset;
    float voltageGain;
    float voltageOffset;
} Settings;

typedef struct Measurement
{
    unsigned long time;
    float current;
    float voltage;
} Measurement;

#endif