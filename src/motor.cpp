#include "motor.h"

void stallOeffnen()
{
    // Checke, ob wirklich geschlossen
    if(digitalRead(PIN_ENDLAGE_UNTEN))
    {
        analogWrite(ENABLE_MOTOR_1, SPEED);
        digitalWrite(INPUT_MOTOR_A, HIGH);
        digitalWrite(INPUT_MOTOR_B, LOW);
    }
    while (!digitalRead(PIN_ENDLAGE_OBEN))
    {}
    
    digitalWrite(INPUT_MOTOR_A, LOW	);
    digitalWrite(INPUT_MOTOR_B, LOW);
}



void stallSchliessen()
{
    // Checke, ob wirklich geschlossen
    if(digitalRead(PIN_ENDLAGE_OBEN))
    {
        analogWrite(ENABLE_MOTOR_1, SPEED);
        digitalWrite(INPUT_MOTOR_A, LOW);
        digitalWrite(INPUT_MOTOR_B, HIGH);
    }
    while (!digitalRead(PIN_ENDLAGE_UNTEN))
    {}
    
    digitalWrite(INPUT_MOTOR_A, LOW	);
    digitalWrite(INPUT_MOTOR_B, LOW);
}



