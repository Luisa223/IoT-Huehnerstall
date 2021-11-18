#include "sensor.h"

void setupSensor()
{
    dht.begin();
}

// TODO: Log auf Website
void readTempAndHumidity()
{
    float Luftfeuchtigkeit = dht.readHumidity(); 
  float Temperatur = dht.readTemperature();
  Serial.print("Luftfeuchtigkeit: "); 
  Serial.print(Luftfeuchtigkeit); 
  Serial.println(" %");
  Serial.print("Temperatur: ");
  Serial.print(Temperatur);
  Serial.println(" Grad Celsius");

}

