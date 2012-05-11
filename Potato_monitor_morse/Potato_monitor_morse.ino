/*     o-o   o-o  o   o  o-o   o-o    O   o-o     */
/*    o   o |     |\ /| o   o o      / \ |        */
/*    |   |  o-o  | O | |   | |  -o o---o o-o     */
/*    o   o     | |   | o   o o   | |   |    |    */
/*     o-o  o--o  o   o  o-o   o-o  o   oo--o     */

/*    OSMOGAS Potato v1.0                         */
/*    Jonas Gruska (CC) 2012                      */

/*    OSMOGAS Potato standard pin definitions     */

#include <Math.h>
#include <LowPower.h>


const int LedA = 5;
const int LedB = 8;
const int LedC = 7;
const int LedD = 6;

const int GreenLED = 2;
const int YellowLED = 3;
const int RedLED = 4;

long int resistor = 22000;

int gamel[] = {792, 873, 966, 1191, 1302, 1056, 1164, 1288, 1588, 1736, 1320, 1455, 1610, 1985, 2170};

int a0[120];
int a1[120];
int a2[120];

int count, time_count, total, average, total1, average1, total2, average2;
float sensorVoltage, thermoResistance, temperature, temperature1;

// Waiting time between showing values in milliseconds
int waitTime = 2000;

void setup()
{
  // Configure 2-8 pins as output
  DDRD = DDRD | B11111100;
  DDRB = B11111;
  PORTD = B11100000;
  PORTB = B00000001;

  delay(1000);
  // Start sequence
  // melody(1);
}

void loop()
{
   
  // Temperature calculation for TDC310 thermistor

  int sensorValue = analogRead(A0);
  sensorVoltage = map(sensorValue, 0, 1024, 0, 5000);
  thermoResistance = ((5 * resistor) - ((sensorVoltage/1000.0) * resistor)) / (sensorVoltage/1000.0);
  temperature = (4380 / log(thermoResistance / 0.0416828078)) - 273.15;
/*
  sensorValue = analogRead(A1);
  sensorVoltage = map(sensorValue, 0, 1024, 0, 5000);
  thermoResistance = ((5 * resistor) - ((sensorVoltage/1000.0) * resistor)) / (sensorVoltage/1000.0);
  temperature1 = (3700 / log(thermoResistance / 0.00407817567)) - 273.15;
*/
  digitalWrite(GreenLED, HIGH);
  delay(80);
  digitalWrite(GreenLED, LOW);
  Display(temperature);
  morse(temperature);
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(GreenLED, HIGH);
  delay(80);
  digitalWrite(GreenLED, LOW);

  /**************************************************/
  /* Averaged ouptut of sensor A0 for last 10 hours */
  /**************************************************/

  // First value morseed will be average light for last 10 hours
  // Every 25th cycle we write the values down for averaging
  // One cycle take 12 seconds, therefore, 25th cycle means 5 minutes

  if (count % 25 == 0) {
    // Write down the last value (scaled to 0-9) 
    a0[time_count] = int(temperature);
    a1[time_count] = int(temperature1);

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
  total1 = 0;
  average1 = 0;

  // Counting average (populating all the values from a0 array 
  // and dividing by amount of written values
  for (int i = 0; i < time_count; i++) {     
    total += a0[i];
    total1 += a1[i];

    average = int(total / time_count);
    average1 = int(total1 / time_count);
  }

  digitalWrite(GreenLED, HIGH);
  delay(80);
  digitalWrite(GreenLED, LOW);
  delay(80);
  digitalWrite(GreenLED, HIGH);
  delay(80);
  digitalWrite(GreenLED, LOW);
  Display(average);
  morse(average);
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(GreenLED, LOW); 
  delay(80);
  digitalWrite(GreenLED, HIGH);
  delay(80);
  digitalWrite(GreenLED, HIGH);
  delay(80);
  digitalWrite(GreenLED, LOW);
  
  digitalWrite(YellowLED, HIGH);
  Display(map(analogRead(0), 0, 700, 0, 9));
  morse(map(analogRead(0), 0, 700, 0, 9));
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(YellowLED, HIGH);

  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}

// This function outputs the supplied value to the morse.
void morse(int n)
{
  if (n <= 9) {
    morse(n);
  } 
  else { 
    int x = int(n / 10);
    int y = int(n % 10);
    morseNumber(x);
    delay(500);
    morseNumber(y);
  }
}

void morseNumber(int number) {
  switch (number) {
  case 0: 
    dash(); 
    dash(); 
    dash(); 
    dash(); 
    dash();
    break;
  case 1:
    dot(); 
    dash(); 
    dash(); 
    dash(); 
    dash();
    break;
  case 2:
    dot(); 
    dot(); 
    dash(); 
    dash(); 
    dash();
    break;
  case 3:
    dot();   
    dot();   
    dot();   
    dash();  
    dash(); 
    break;
  case 4:
    dot();   
    dot();   
    dot();   
    dot();   
    dash(); 
    break;
  case 5:
    dot();  
    break;
  case 6:
    dash();  
    dot();   
    dot();   
    dot();   
    dot(); 
    break; 
  case 7:  
    dash();  
    dash();  
    dot();   
    dot();   
    dot();  
    break;
  case 8:
    dash();  
    dash();  
    dash();  
    dot();   
    dot();  
    break;
  case 9:
    dash();  
    dash();  
    dash();  
    dash();  
    dot();  
    break;
  }
}


void melody(int n) {
  switch (n) {
  case 1:
    for(int i = 0; i<15; i++) {
      tone(10, gamel[random(15)]);
      digitalWrite(GreenLED, HIGH);
      delay(250);
      digitalWrite(GreenLED, LOW);      
      noTone(10);
      delay(10);
    }
    break;
  case 2:
    for(int i = 0; i<5; i++) {
      tone(10, gamel[random(15)]);
      delay(300);    
      noTone(10);
      delay(10);
    }
    break;
  }
}
  
void dash() {
  tone(10, 2100);
  delay(400);
  noTone(10);
  delay(30);
}

void dot() {
  tone(10, 3100);
  delay(100);
  noTone(10);
  delay(30);
}

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
