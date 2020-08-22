// OLED_I2C_Bitmap
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
// use the Wire library for display communication. The default I2C speed
// is 400KHz.
//

#include <OLED_I2C.h>

OLED  myOLED(18, 19); // Remember to add the RESET pin if your display requires it...

extern uint8_t logo[];
extern uint8_t mice[];

void setup()
{
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...
}

void loop()
{
  myOLED.clrScr();
  myOLED.drawBitmap(7, 0, logo, 114, 32);
  myOLED.update();
  delay(4000);
  for (int i=0; i<2; i++)
  {
    myOLED.invert(true);
    delay(500);
    myOLED.invert(false);
    delay(500);
  }
  delay(4000);

  myOLED.fillScr();
  myOLED.drawBitmap(32, 0, mice, 64, 32);
  myOLED.update();
  delay(4000);
  for (int i=0; i<2; i++)
  {
    myOLED.invert(true);
    delay(500);
    myOLED.invert(false);
    delay(500);
  }
  delay(4000);
}
