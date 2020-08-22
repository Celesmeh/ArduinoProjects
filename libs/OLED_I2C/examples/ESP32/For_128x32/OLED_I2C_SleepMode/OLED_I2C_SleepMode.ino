// OLED_I2C_SleepMode
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

extern uint8_t SmallFont[];

void setup()
{
  if(!myOLED.begin(SSD1306_128X32))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

  myOLED.setFont(SmallFont);
}

void loop()
{
  for (int i = 5; i > 0; i--)
  {
    myOLED.clrScr();
    myOLED.print("Entering sleep mode", CENTER, 6);
    myOLED.printNumI(i, CENTER, 18);
    myOLED.update();
    delay(1000);
  }

  myOLED.sleepMode(SLEEP_ON);
  delay(3000);
  
  myOLED.sleepMode(SLEEP_OFF);
  myOLED.clrScr();
  myOLED.print("Awake again...", CENTER, 12);
  myOLED.update();
  delay(3000);
}
