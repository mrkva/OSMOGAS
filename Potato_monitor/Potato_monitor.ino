// OSMOGAS Potato Testing program
// Blinks LED's and shows numbers on display

const int LedA = 5;
const int LedB = 8;
const int LedC = 7;
const int LedD = 6;

const int GreenLED = 2;
const int YellowLED = 3;
const int RedLED = 4;

int count = 0;

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
  // Read first sensor
  Display(map(analogRead(0), 0, 1000, 0, 9));
  // Turn on LED
  digitalWrite(GreenLED, HIGH);
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(GreenLED, LOW);  
  
  // Read second sensor
  Display(map(analogRead(1), 0, 1000, 0, 9));
  // Turn on LED
  digitalWrite(YellowLED, HIGH);
  // Wait two seconds
  delay(waitTime);
  // Turn off LED
  digitalWrite(YellowLED, LOW); 
  
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
  
}

// This function outputs the supplied value to the display.
void Display(int n)
{
  digitalWrite(LedD, ((n >> 3) & 1) ? HIGH : LOW);
  digitalWrite(LedC, ((n >> 2) & 1) ? HIGH : LOW);
  digitalWrite(LedB, ((n >> 1) & 1) ? HIGH : LOW);
  digitalWrite(LedA, (n & 1) ? HIGH : LOW);
}

void Disp_Break()
{
  for (int i = 0; i<3; i++ ) {
    Display(0);
    digitalWrite(i+2, HIGH);
    delay(50);
    digitalWrite(i+2, LOW);
    delay(100);
    Blank(); 
    delay(100);
    
  }
}

void Blank()
{
  digitalWrite(LedD, HIGH);
  digitalWrite(LedC, HIGH);
  digitalWrite(LedB, HIGH);
  digitalWrite(LedA, HIGH); 
}
