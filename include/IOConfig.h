#include <Arduino.h>

// Pins fuer Endlagenabfrage

#define PIN_ENDLAGE_OBEN 4
#define PIN_ENDLAGE_UNTEN 5

// Motor driver Pins
// A HIGH - B LOW: oeffnen
#define ENABLE_MOTOR_1 16
#define INPUT_MOTOR_A   7  
#define INPUT_MOTOR_B   8

// Sensor DHT22 - Temperatur + Feuchtigkeit
#define INPUT_SENSOR 3

void setPinStatus();