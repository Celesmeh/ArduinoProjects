// OLED_I2C_Brightness
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
// use the Wire library for display communication.
//

#include <OLED_I2C.h>

OLED  myOLED(D2, D1); // Remember to add the RESET pin if your display requires it...

void setup()
{
  if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

  myOLED.invert(true);
}

void loop()
{
  for (int i=0; i<256; i++)
  {
    myOLED.setBrightness(i);
    delay(5);
  }
  for (int i=255; i>=0; i--)
  {
    myOLED.setBrightness(i);
    delay(5);
  }
}
