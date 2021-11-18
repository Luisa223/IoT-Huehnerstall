#include "IOConfig.h"


void setPinStatus()
{
    // Motor driver pins
    pinMode(INPUT_MOTOR_A, OUTPUT);
    pinMode(INPUT_MOTOR_B, OUTPUT);
    pinMode(ENABLE_MOTOR_1, OUTPUT);

    // Endlage
    pinMode(PIN_ENDLAGE_UNTEN, INPUT);
    pinMode(PIN_ENDLAGE_OBEN, INPUT);

    // Sensor
    pinMode(INPUT_SENSOR, INPUT);
}