/*
 *  LED Matrix Rainbow
 *  
 *  Demo sketch for 48 x 36 LED tile
 *
 *  Displays scrolling rainbow
 *
 *  This program relies on the fact that the shift register is not cleared after latching
 *  so we only need to write a few pixels each frame to keep the refresh rate high.
 *
 *  2016-08-02  John Johnson
 */

// define pins - in this case for Arduino Mega
#define pinR1 30
#define pinG1 31
#define pinB1 32
#define pinA  33
#define pinB  34
#define pinC  35
#define pinCK 37
#define pinLT 38
#define pinEN 39

// define any globals
long step = 0;      // count cycles
long lastStep = 0;  // time count last incremented


void setup() {
  Serial.begin(115200);
  Serial.println("LED Matrix rainbow");

  // set pin modes
  pinMode(pinR1, OUTPUT);
  pinMode(pinG1, OUTPUT);
  pinMode(pinB1, OUTPUT);
  pinMode(pinA, OUTPUT);
  pinMode(pinB, OUTPUT);
  pinMode(pinC, OUTPUT);
  pinMode(pinCK, OUTPUT);
  pinMode(pinLT, OUTPUT);
  pinMode(pinEN, OUTPUT);

  // set initial pin states
  Serial.println("Setting EN");
  writeData(pinEN, LOW);      // this one is active low
  Serial.println("Setting LT");
  writeData(pinLT, LOW);
  Serial.println("Setting CK");
  writeData(pinCK, LOW);
}


void loop() {
  for(int row=0; row<6; row++)    // loop for each row group
  {
    selectRow(row);
    chaseRainbow();
  }
  if(millis() > lastStep+100) { step ++; lastStep = millis(); };  // if it's been more than 100mS since the pattern last shifted then shift
}


void chaseRainbow() // output a rainbow
{
  // NB: in fact it would be sufficient to output one pixel each time the pattern steps, but this is more adaptable
  for(int i=0; i<8; i++)  // output each colour once
  {
    setPixel(step+i);     // cycle through them
  }
  writeData(pinLT, HIGH); // latch them once done
  writeData(pinLT, LOW);
}


void selectRow(int row)   // set the address lines from the row group number
{
  writeData(pinA, (row & 1) );
  writeData(pinB, ((row >> 1) & 1) );
  writeData(pinC, ((row >> 2) & 1) );
}


void setPixel(int colour)   // set the next pixel to a given colour
{
  switch (colour % 8) {
    case 0: {
      setPixel(HIGH, LOW, LOW);   // red
      break;
      }
    case 1: {
      setPixel(HIGH, HIGH, LOW);  // yellow
      break;
      }
    case 2: {
      setPixel(LOW, HIGH, LOW);   // green
      break;
      }
    case 3: {
      setPixel(LOW, HIGH, HIGH);  // cyan
      break;
      }
    case 4: {
      setPixel(LOW, LOW, HIGH);   // blue
      break;
      }
    case 5: {
      setPixel(HIGH, LOW, HIGH);  // violet
      break;
      }  
    case 6: {
      setPixel(HIGH, HIGH, HIGH); // white
      break;
      }
    case 7: {
      setPixel(LOW, LOW, LOW);    // black
      break;
      }
    default: {
      Serial.println(colour);     // debug if invalid value given
      break;
      }
    }
}


void setPixel(bool R, bool G, bool B) // output the pixel to the panel
{
  digitalWrite(30, R);    // set the colour pins
  digitalWrite(pinG1, G);
  digitalWrite(pinB1, B);

  digitalWrite(pinCK, HIGH);  // and clock it
  digitalWrite(pinCK, LOW);
}


void writeData(int pin, bool val) // generic output function
{
  digitalWrite(pin, val);
}

