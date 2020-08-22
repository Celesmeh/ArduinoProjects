// OLED_I2C_Graph_Demo
// Copyright (C)2018 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// **********************************************
// *** This demo is for 128x32 pixel displays ***
// **********************************************
//
// A quick demo of how to use my OLED_I2C library.
//
// To use the hardware I2C (TWI) interface of the chipKit you must connect
// the pins as follows:
//
// chipKit Uno32/uC32:
// ----------------------
// Display:  SDA pin   -> Analog 4
//           SCL pin   -> Analog 5
// *** Please note that JP6 and JP8 must be in the I2C position (closest to the analog pins)
//
// chipKit Max32:
// ----------------------
// Display:  SDA pin   -> Digital 20 (the pin labeled SDA)
//           SCL pin   -> Digital 21 (the pin labeled SCL)
//
// The chipKit boards does not have pull-up resistors on the hardware I2C interface
// so external pull-up resistors on the data and clock signals are required.
//
// You can connect the OLED display to any available pin but if you use any
// other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used.
//

#include <OLED_I2C.h>

OLED  myOLED(SDA, SCL); // Remember to add the RESET pin if your display requires it...

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];
extern uint8_t logo[];
extern uint8_t The_End[];
extern uint8_t pacman1[];
extern uint8_t pacman2[];
extern uint8_t pacman3[];
extern uint8_t pill[];

float y;
uint8_t* bm;
int pacy;

void setup()
{
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

  randomSeed(analogRead(7));
}

void loop()
{
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.drawBitmap(7, 0, logo, 114, 32);
  myOLED.update();
  delay(3000);
  
  myOLED.clrScr();
  myOLED.print("OLED_I2C", CENTER, 0);
  myOLED.print("DEMO", CENTER, 12);
  myOLED.drawRect(50, 10, 78, 22);
  for (int i=0; i<7; i++)
  {
    myOLED.drawLine(79, 10+(i*2), 105-(i*3), 10+(i*2));
    myOLED.drawLine(22+(i*3), 22-(i*2), 50, 22-(i*2));
  }
  myOLED.setFont(TinyFont);
  myOLED.print("(C)2018 by Henning Karlsen", CENTER, 26);
  myOLED.setFont(SmallFont);
  myOLED.update();
  delay(3000);
  
  myOLED.clrScr();
  for (int i=0; i<32; i+=2)
  {
    myOLED.drawLine(0, i, 127, 31-i);
    myOLED.update();
  }
  for (int i=127; i>=0; i-=2)
  {
    myOLED.drawLine(i, 0, 127-i, 31);
    myOLED.update();
  }
  delay(2000);
  
  myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 31);
  for (int i=0; i<32; i+=4)
  {
    myOLED.drawLine(0, i, i*4, 31);
    myOLED.update();
  }
  for (int i=0; i<32; i+=4)
  {
    myOLED.drawLine(127, 31-i, 127-(i*4), 0);
    myOLED.update();
  }
  delay(2000);
  
  myOLED.clrScr();
  for (int i=0; i<5; i++)
  {
    myOLED.drawRoundRect(i*3, i*3, 127-(i*3), 31-(i*3));
    myOLED.update();
  }
  delay(2000);
  
  myOLED.clrScr();
  for (int i=0; i<25; i++)
  {
    myOLED.drawCircle(64, 16, i*3);
    myOLED.update();
  }
  delay(2000);
  
  myOLED.clrScr();
  myOLED.drawRect(0, 0, 127, 31);
  myOLED.drawLine(0, 15, 127, 15);
  myOLED.drawLine(63, 0, 63, 31);
  for (int c=0; c<4; c++)
  {
    for (int i=0; i<128; i++)
    {
      y=i*0.04974188368183839294232518690191;
      myOLED.invPixel(i, (sin(y)*14)+15);
      myOLED.update();
      delay(10);
    }
  }
  delay(1000);

  for (int pc=0; pc<3; pc++)
  {
    pacy=random(0, 12);
  
    for (int i=-20; i<132; i++)
    {
      myOLED.clrScr();
      for (int p=6; p>((i+20)/20); p--)
        myOLED.drawBitmap(p*20-8, pacy+7, pill, 5, 5);
      switch(((i+20)/3) % 4)
      {
        case 0: bm=pacman1;
                break;
        case 1: bm=pacman2;
                break;
        case 2: bm=pacman3;
                break;
        case 3: bm=pacman2;
                break;
      }
      myOLED.drawBitmap(i, pacy, bm, 20, 20);
      myOLED.update();
      delay(10);
    }
  }

  for (int i=0; i<24; i++)
  {
    myOLED.clrScr();
    myOLED.drawBitmap(22, i-24, The_End, 84, 24);
    myOLED.update();
    delay(50);
  }
  myOLED.print("Runtime (ms):", LEFT, 24);
  myOLED.printNumI(millis(), RIGHT, 24);
  myOLED.update();
  for (int i=0; i<5; i++)
  {
    myOLED.invert(true);
    delay(1000);
    myOLED.invert(false);
    delay(1000);
  }
}


