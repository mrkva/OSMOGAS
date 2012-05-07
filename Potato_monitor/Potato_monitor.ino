/*     o-o   o-o  o   o  o-o   o-o    O   o-o     */
/*    o   o |     |\ /| o   o o      / \ |        */
/*    |   |  o-o  | O | |   | |  -o o---o o-o     */
/*    o   o     | |   | o   o o   | |   |    |    */
/*     o-o  o--o  o   o  o-o   o-o  o   oo--o     */

/*    OSMOGAS Potato v1.0                         */
/*    Jonas Gruska (CC) 2012                      */

/*    OSMOGAS Potato standard pin definitions     */

#include <math.h>

const int LedA = 5;
const int LedB = 8;
const int LedC = 7;
const int LedD = 6;

const int GreenLED = 2;
const int YellowLED = 3;
const int RedLED = 4;

long int resistor = 27000;

int a0[120];

int count, time_count, total, average;
float sensorVoltage, thermoResistance, temperature;

// Waiting time between showing values in milliseconds
int waitTime = 2000;

void setup()
{
  // Configure 2-8 pins as output
  DDRD = DDRD | B11111100;
  DDRB = B11111;

  delay(1000);
  // Start sequence
  Disp_Break();
}

void loop()
{
 
  // Temperature calculation for TOC310 thermistor

  int sensorValue = analogRead(A0);
  sensorVoltage = map(sensorValue, 0, 1024, 0, 5000);
  thermoResistance = ((5 * resistor) - ((sensorVoltage/1000.0) * resistor)) / (sensorVoltage/1000.0);
  temperature = (4100 / log(thermoResistance / 0.0106613843)) - 273.15;

  digitalWrite(GreenLED, HIGH);
  Display(temperature);
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(GreenLED, LOW);
 
  /**************************************************/
  /* Averaged ouptut of sensor A0 for last 10 hours */
  /**************************************************/ 
  
  // First value displayed will be average light for last 10 hours
  // Every 25th cycle we write the values down for averaging
  // One cycle take 12 seconds, therefore, 25th cycle means 5 minutes

  if (count % 25 == 0) {
    // Write down the last value (scaled to 0-9) 
    a0[time_count] = int(temperature);

    // When at the end of the array of values - start writing from beginning.
    // Position in array doesn't affect the average output, obviously
    if (time_count < 120) 
      time_count++;
    else
      time_count = 0;
  }

  // Raise count every (waitTime * 6) milliseconds (in this case, 12 000 ms => 12s)
  count++;
  // Reseting values for calculating average
  total = 0;
  average = 0;

  // Counting average (populating all the values from a0 array 
  // and dividing by amount of written values
  for (int i = 0; i < time_count; i++) {     
    total += a0[i];
    average = int(total / time_count);
  }

  digitalWrite(YellowLED, HIGH);
  Display(average);
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(YellowLED, LOW); 

  /***************************************************/
  /* Basic reading of the sensors, one after another */
  /***************************************************/

   // Turn on LED
   digitalWrite(RedLED, HIGH);
  // Read second sensor (HUMIDITY)
   Display(map(analogRead(1), 0, 800, 0, 9));
   // Wait two seconds
   delay(waitTime);
   // Turn off LED
   digitalWrite(RedLED, LOW); 
  
   /* 
   // Read third sensor
   Display(map(analogRead(2), 0, 1000, 0, 9));
   // Turn on LED
   digitalWrite(RedLED, HIGH);
   // Wait two seconds
   delay(waitTime);
   // Turn off LED
   digitalWrite(RedLED, LOW); 
   
   // Read fourth sensor
   Display(map(analogRead(3), 0, 1000, 0, 9));
   // Turn on LED
   digitalWrite(GreenLED, HIGH);
   digitalWrite(YellowLED, HIGH);
   // Wait two seconds
   delay(waitTime);
   // Turn off LED
   digitalWrite(GreenLED, LOW);
   digitalWrite(YellowLED, LOW);
   
   // Read fifth sensor
   Display(map(analogRead(4), 0, 1000, 0, 9));
   // Turn on LED
   digitalWrite(RedLED, HIGH);
   digitalWrite(YellowLED, HIGH);
   // Wait two seconds
   delay(waitTime);
   // Turn off LED
   digitalWrite(RedLED, LOW);
   digitalWrite(YellowLED, LOW);
   
   // Read sixth sensor
   Display(map(analogRead(5), 0, 1000, 0, 9));
   // Turn on LED
   digitalWrite(RedLED, HIGH);
   digitalWrite(GreenLED, HIGH);
   // Wait two seconds
   delay(waitTime);
   // Turn off LED
   digitalWrite(RedLED, LOW);
   digitalWrite(GreenLED, LOW);

  */

}

// This function outputs the supplied value to the display.
void Display(int n)
{
  int x = int(n / 10);
  int y = int(n % 10);
  if (n <= 9) {
    digitalWrite(LedD, ((n >> 3) & 1) ? HIGH : LOW);
    digitalWrite(LedC, ((n >> 2) & 1) ? HIGH : LOW);
    digitalWrite(LedB, ((n >> 1) & 1) ? HIGH : LOW);
    digitalWrite(LedA, (n & 1) ? HIGH : LOW);
  } 
  else { 
    digitalWrite(LedD, ((x >> 3) & 1) ? HIGH : LOW);
    digitalWrite(LedC, ((x >> 2) & 1) ? HIGH : LOW);
    digitalWrite(LedB, ((x >> 1) & 1) ? HIGH : LOW);
    digitalWrite(LedA, (x & 1) ? HIGH : LOW);

    delay(1000);

    digitalWrite(LedD, ((y >> 3) & 1) ? HIGH : LOW);
    digitalWrite(LedC, ((y >> 2) & 1) ? HIGH : LOW);
    digitalWrite(LedB, ((y >> 1) & 1) ? HIGH : LOW);
    digitalWrite(LedA, (y & 1) ? HIGH : LOW);

  }
}

void Disp_Break()
{
  for (int i = 0; i<5; i++ ) {
    Display(0);
    digitalWrite(i+2, HIGH);
    delay(50);
    digitalWrite(i+2, LOW);
    delay(50);
    Blank(); 
    delay(50);

  }
}

void Blank()
{
  digitalWrite(LedD, HIGH);
  digitalWrite(LedC, HIGH);
  digitalWrite(LedB, HIGH);
  digitalWrite(LedA, HIGH); 
}


