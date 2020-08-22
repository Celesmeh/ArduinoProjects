// OLED_I2C_ViewFonts
// Copyright (C)2019 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// **********************************************
// *** This demo is for 128x32 pixel displays ***
// **********************************************
//
// A quick demo of how to use my OLED_I2C library.
//
// Remember to use external pull-up resistors on the data and clock signals 
// if they are required.
//
// You can connect the OLED display to any available pin. The library will
// use the Wire library for display communication.
//

#include <OLED_I2C.h>

OLED  myOLED(D2, D1); // Remember to add the RESET pin if your display requires it...

extern uint8_t SmallFont[];
extern uint8_t TinyFont[];

void setup()
{
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
}

void loop()
{
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.print("Upper case:", LEFT, 0);
  myOLED.print("SmallFont", RIGHT, 0);
  myOLED.print("ABCDEFGHIJKLM", CENTER, 16);
  myOLED.print("NOPQRSTUVWXYZ", CENTER, 24);
  myOLED.update();
  delay (5000);
  
  myOLED.clrScr();
  myOLED.print("Lower case:", LEFT, 0);
  myOLED.print("SmallFont", RIGHT, 0);
  myOLED.print("abcdefghijklm", CENTER, 16);
  myOLED.print("nopqrstuvwxyz", CENTER, 24);
  myOLED.update();
  delay (5000);
  
  myOLED.clrScr();
  myOLED.print("Numbers:", LEFT, 0);
  myOLED.print("SmallFont", RIGHT, 0);
  myOLED.print("0123456789", CENTER, 16);
  myOLED.update();
  delay (5000);
  
  myOLED.clrScr();
  myOLED.print("Special:", LEFT, 0);
  myOLED.print("SmallFont", RIGHT, 0);
  myOLED.print("!\"#$%&'()*+,-./:", CENTER, 16);
  myOLED.print(";<=>?@[\\]^_`{|}~", CENTER, 24);
  myOLED.update();
  delay (5000);

  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.print("Upper case:", LEFT, 0);
  myOLED.print("TinyFont", RIGHT, 0);
  myOLED.setFont(TinyFont);
  myOLED.print("ABCDEFGHIJKLM", CENTER, 16);
  myOLED.print("NOPQRSTUVWXYZ", CENTER, 22);
  myOLED.update();
  delay (5000);
  
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.print("Lower case:", LEFT, 0);
  myOLED.print("TinyFont", RIGHT, 0);
  myOLED.setFont(TinyFont);
  myOLED.print("abcdefghijklm", CENTER, 16);
  myOLED.print("nopqrstuvwxyz", CENTER, 22);
  myOLED.update();
  delay (5000);
  
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.print("Numbers:", LEFT, 0);
  myOLED.print("TinyFont", RIGHT, 0);
  myOLED.setFont(TinyFont);
  myOLED.print("0123456789", CENTER, 16);
  myOLED.update();
  delay (5000);
  
  myOLED.setFont(SmallFont);
  myOLED.clrScr();
  myOLED.print("Special:", LEFT, 0);
  myOLED.print("TinyFont", RIGHT, 0);
  myOLED.setFont(TinyFont);
  myOLED.print("!\"#$%&'()*+,-./:", CENTER, 16);
  myOLED.print(";<=>?@[\\]^_`{|}~", CENTER, 22);
  myOLED.update();
  delay (5000);
}
