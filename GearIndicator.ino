/*
 * Gear indicator for Subaru sportshift.
 * The TCU tells us what gear the transmission is in over 4 pins.
 *    1st gear - pin 1 low
 *    2nd gear - pin 2 low
 *    3rd gear - pin 1 + 2 low
 *    4th gear - pin 3 low
 *    
 *    Pin 4 is for shift down indicator
 *    
 */
const int IND_1 = 0;
const int IND_2 = 1;
const int IND_3 = 2;
const int IND_4 = 3;
const int A = 16;
const int B = 15;
const int C = 14;
const int D = 13;
const int E = 12;
const int F = 11;
const int G = 10;
const int RPD = 9;

// LED Pinout
// 11  16  
// 10  15
// GND  
// 12  9
// 13  14

// A, B, C, D, E, F, G
const byte gears[5][7] = {{1, 1, 1, 0, 1, 1, 1},  // A
  {0, 1, 1, 0, 0, 0, 0},  // 1
  {1, 1, 0, 1, 1, 0, 1},  // 2
  {1, 1, 1, 1, 0, 0, 1},  // 3
  {0, 1, 1, 0, 0, 1, 1}   // 4
};

void setup() {
  // put your setup code here, to run once:
  pinMode(IND_1, INPUT);
  pinMode(IND_2, INPUT);
  pinMode(IND_3, INPUT);
  pinMode(IND_4, INPUT);
//  pinMode(BUZZ, INPUT);
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
}

void writeDigit(byte digit)
{
  byte pin = 16;
  for (byte segCount = 0; segCount < 7; ++segCount)
  {
    digitalWrite(pin, gears[digit][segCount]);
    --pin;
  }
}

void loop() {
  int _ind1 = digitalRead(IND_1);
  int _ind2 = digitalRead(IND_2);
  int _ind3 = digitalRead(IND_3);
  int _ind4 = digitalRead(IND_4);

  if (_ind1 == 0 && _ind2 == 0)
  {
    writeDigit(3);
  }
  else if (_ind1 == 0)
  {
    writeDigit(1);
  }
  else if (_ind2 == 0)
  {
    writeDigit(2);
  }
  else if (_ind3 == 0)
  {
    writeDigit(4);
  }
  else
  {
    writeDigit(0);
  }

  if (_ind4 == 0)
  {
    analogWrite(RPD, 255);
  }
  else
  {
    analogWrite(RPD, 0);
  }

  delay(250);
}
