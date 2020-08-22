// OLED_I2C_NumberFonts
// Copyright (C)2019 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// **********************************************
// *** This demo is for 128x64 pixel displays ***
// **********************************************
//
// A quick demo of how to use my OLED_I2C library.
//
// Remember to use external pull-up resistors on the data and clock signals 
// if they are required.
//
// You can connect the OLED display to any available pin. The library will
// use the Wire library for display communication. The default I2C speed
// is 400KHz.
//

#include <OLED_I2C.h>

OLED  myOLED(18, 19); // Remember to add the RESET pin if your display requires it...

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];

void setup()
{
  if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

  myOLED.setFont(SmallFont);
}

void loop()
{
  for (int i=0; i<=1000; i++)
  {
    myOLED.setFont(MediumNumbers);
    myOLED.printNumF(float(i)/3, 2, RIGHT, 0);
    myOLED.setFont(BigNumbers);
    myOLED.printNumI(i, RIGHT, 40);
    myOLED.update();
  }
  
  myOLED.setFont(SmallFont);
  myOLED.print("|", LEFT, 24);
  myOLED.print("|", RIGHT, 24);
  myOLED.update();
  delay(500);
  for (int i=0; i<19; i++)
  {
    myOLED.print("\\", 7+(i*6), 24);
    myOLED.update();
    delay(250);
  }
  myOLED.clrScr();
}
