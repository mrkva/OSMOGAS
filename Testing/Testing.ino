// OSMOGAS Potato Testing program
// Blinks LED's and shows numbers on display

const int LedA = 5;
const int LedB = 8;
const int LedC = 7;
const int LedD = 6;
int count = 0;
int i;

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
 
  //Display(map(analogRead(0), 600, 1000, 0, 9));
  Display(i);
  if (i<9) { i++; } 
    else { i = 0; };
  digitalWrite(2, HIGH);   
  delay(100);             
  digitalWrite(2, LOW); 
  delay(100);    

  digitalWrite(3, HIGH);   
  delay(100);             
  digitalWrite(3, LOW); 
  delay(100);

  digitalWrite(4, HIGH);   
  delay(100);             
  digitalWrite(4, LOW); 
  delay(100);
  
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
