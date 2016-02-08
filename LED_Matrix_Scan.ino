/*
 *  LED Matrix Scan
 *  
 *  Demo sketch for 48 x 36 LED tile
 *
 *  Displays short rainbow trail to demonstrate the addressing order of the tile
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

void setup() {
  Serial.begin(115200);
  Serial.println("LED Matrix scan");

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
    scanTile();
  }
}


void scanTile()
{
  for(int i=287; i>=0; i--)   // working backwards (as data is 'pushed' into the shift register
  {
    for(int j=0; j<i; j++)    // first fill all ahead with black
    {
      setPixel(7);      
    }
    for(int j=0; j<8 && j<288-i; j++) // set up to seven pixels to colours
    {
      setPixel(7-j);    // use colours in reverse order
    }
    for(int j=i+7; j<288; j++)  // then fill all behind with black
    {
      setPixel(7);      
    }
    writeData(pinLT, HIGH);   // toggle the latch
    writeData(pinLT, LOW);
    delay(20);    // delay to make the pattern easier to follow
  }
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

