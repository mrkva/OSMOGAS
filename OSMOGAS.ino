/*
OSMOGAS temperature measurement
*/

#include <math.h>
// Resistor value 
long int resistor = 9820;

float thermoResistance;
float sensorVoltage;
float temperature;

void setup() {
  Serial.begin(1200);
}

void loop() {
  int sensorValue = analogRead(A0);
  sensorVoltage = map(sensorValue, 0, 1024, 0, 5000);
  thermoResistance = ((5 * resistor) - ((sensorVoltage/1000.0) * resistor)) / (sensorVoltage/1000.0);
  temperature = (4100 / log(thermoResistance / 0.0106613843)) - 273.15;
  Serial.println(temperature);
}
