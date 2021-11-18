#include <Arduino.h>

#include <WiFi.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>

#include "time.h"
#include "website.h"
#include "motor.h"
#include "IOConfig.h"
#include "sensor.h"


void setup()
{
  Serial.begin(115200);
  setPinStatus();
  void setupWebserver();
  setupSensor();
}

  
void loop() 
{
  checkIfTimeSetHasChanged();
  if(compareTime())
  {
    stallOeffnen();
  }
  readTempAndHumidity();
  //TODO: Deep Sleep + external interrupt zum energiesparen!
  delay(400);
}
