#include "IOConfig.h"
#include <Arduino.h>
#include "DHT.h"     
#define DHTTYPE DHT22


DHT dht(INPUT_SENSOR, DHTTYPE);

// TODO: Erweiterung um Helligkeitssensor fuer Check beim Oeffnen
void setupSensor();
void readTempAndHumidity();