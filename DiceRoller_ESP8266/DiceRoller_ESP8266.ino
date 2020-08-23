
//********************************************************************************************************
// Libs to bring
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266TrueRandom.h>

//********************************************************************************************************
// define OLED info
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET     -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//********************************************************************************************************
//Define Variables
#define menu 6

// Define Menu Size

bool Next = HIGH;
bool Dice = HIGH;
String temp;
char currentPrintOut[10];
const int menuSize = 7;
byte menuItems[menuSize];
int currMenu = 0;
int rolling = currMenu + 1;
int dArray = (menuItems[currMenu]);
int roll = ESP8266TrueRandom.random(1, (menuItems[currMenu] + 1));
int animationDelay = 200; //So that's 5 frames per second
long randNum;


//********************************************************************************************************
// Set it all up pls
void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // setup the OLED
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.drawRect(0, 8, 128, 1, WHITE);
  display.setCursor(18, 1);
  display.println("20 12 10 8 6 4 2"); // write the roll
  drawWel();
  display.display(); // write to display
  Serial.begin(9600);

  pinMode(13, INPUT_PULLUP); // setup button 1
  pinMode(12, INPUT_PULLUP); // setup button 2

  menuItems[0] = 2;
  menuItems[1] = 4;
  menuItems[2] = 6;
  menuItems[3] = 8;
  menuItems[4] = 10;
  menuItems[5] = 12;
  menuItems[6] = 20;
}

//********************************************************************************************************
// Loop dis pls

void loop() {
  //Menu Logic
  if (digitalRead(13) != Next) {
    Next = !Next;
    delay(50);
    if (!Next) {
      //pressed
      if (currMenu > 0) {
        currMenu--;
      }
      else {
        currMenu =
        menuSize - 1;
      }
      MenuChanged();
      Serial.print (currMenu);
    }
  }

  //Dice Logic
  if (digitalRead(12) != Dice) {
    Next = !Next;
    delay(150);
    if (!Next) {
      delay(50);
      diceRoll();
      breakfastSerials();
    }
  }
}


//********************************************************************************************************
//Button testing

void MenuButton() {
  Serial.println("menu state has changed");
  delay(25);
}
void TestButton() {
  Serial.println("button state has changed");
  delay(25);
}

//********************************************************************************************************
//Dice Utils

void FontDice() {
  display.setTextColor(WHITE);
  display.setTextSize(2);
}

void ClearDice() {
  display.fillRect(10, 9, 128, 23,  BLACK);
}

//********************************************************************************************************
//Menu

void MenuChanged() {
  display.clearDisplay();
  display.drawRect(0, 8, 128, 1, WHITE);
  menuBar();
  if (currMenu < 4) {
    display.setCursor(53, 15);
  }
  else {
    display.setCursor(48, 15);
  }
  FontDice();
  temp = String (menuItems[currMenu]);
  temp.toCharArray (currentPrintOut, 10);
  display.print("D");
  display.println(currentPrintOut); // write the roll
  Serial.println(currentPrintOut); // write the roll
  display.display(); // write to display
  delay(25);

}

//********************************************************************************************************
//Dice Rolls

void diceRoll() {
  Serial.println("button state has changed");
  display.fillScreen(BLACK); // erase all
  display.drawRect(0, 8, 128, 1, WHITE);
  menuBar();
  DicePic();
  //Our Roll
  int roll = ESP8266TrueRandom.random(1, (menuItems[currMenu] + 1));

  // OLED make purdy
  if (roll == 1 && menuItems[currMenu] == 20) {
    display.fillScreen(BLACK); // erase all
    menuBar();
    drawSkull();
    FontDice();
    display.setCursor(87, 14);
    display.println(roll); //get rekt
  }
  else if (roll == 20 && menuItems[currMenu] == 20) {
    display.fillScreen(BLACK); // erase all
    menuBar();
    drawStar();
    FontDice();
    display.setCursor(77, 14);
    display.println(roll); // daaamn yuss
  }
  else if (roll < 10) {
    //single character number
    FontDice();
    display.setCursor(87, 14);
    display.println(roll); // write the roll

  }
  else {
    // dual character number
    FontDice();
    display.setCursor(77, 14);
    display.println(roll); // write the roll
  }

  display.display(); // write to display
  delay(100);
}


//********************************************************************************************************
//Menu Bar

void menuBar() {

  display.setTextSize(1);
  display.drawRect(0, 8, 128, 1, WHITE);
  display.setCursor(18, 1);
  display.println("20 12 10 8 6 4 2"); // write the roll


  if (currMenu == 6) {
    display.drawRect(16, 0, 15, 1, WHITE);
    display.fillRect(16, 0, 15, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(18, 1);
    display.println("20"); // write the roll
  }
  if (currMenu == 5) {
    display.drawRect(34, 0, 15, 1, WHITE);
    display.fillRect(34, 0, 15, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(36, 1);
    display.println("12"); // write the roll
  }
  if (currMenu == 4) {
    display.drawRect(53, 0, 15, 1, WHITE);
    display.fillRect(53, 0, 15, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(54, 1);
    display.println("10"); // write the roll
  }
  if (currMenu == 3) {
    display.drawRect(68, 0, 14, 1, WHITE);
    display.fillRect(68, 0, 14, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(72, 1);
    display.println("8"); // write the roll
  }
  if (currMenu == 2) {
    display.drawRect(80, 0, 14, 1, WHITE);
    display.fillRect(80, 0, 14, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(85, 1);
    display.println("6"); // write the roll
  }
  if (currMenu == 1) {
    display.drawRect(92, 0, 12, 1, WHITE);
    display.fillRect(92, 0, 12, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(96, 1);
    display.println("4"); // write the roll
  }
  if (currMenu == 0) {
    display.drawRect(104, 0, 12, 1, WHITE);
    display.fillRect(104, 0, 12, 8, WHITE);
    display.setTextColor(BLACK);
    display.setCursor(108, 1);
    display.println("2"); // write the roll
  }
}

//********************************************************************************************************
//Random Number

void randroll() {
  randNum = random(1,menuItems[currMenu]);
  if (randNum < 10) {
    //single character number
    FontDice();
    display.setCursor(87, 14);
    display.println(randNum ); // write the roll

  }
  else {
    // dual character number
    FontDice();
    display.setCursor(77, 14);
    display.println(randNum ); // write the roll
  }

}

//********************************************************************************************************
//Dice Draws

void DicePic() {
  for (int i = 0; i < 3; i++) {
    int diceDelay = 100;
    diceDraw();
    randroll();
    display.display();
    delay(diceDelay);
    ClearDice();
    randroll();
    display.display();
    diceDrawr();
    display.display();
    delay(diceDelay);
    ClearDice();
    diceDraw();
  }
}
//********************************************************************************************************
//Serial Prints Pls

void breakfastSerials() {
  Serial.println("roll");
  Serial.println(roll);
  Serial.println("currMenu");
  Serial.println(currMenu);
  Serial.println("diceArray");
  Serial.println(dArray);
}


//********************************************************************************************************
//Dice img
void drawStar() {
  // store image in EEPROM
  static const unsigned char PROGMEM imExp[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    , 0x00, 0x00, 0x0f, 0xc0, 0x00, 0x00
    , 0x00, 0x00, 0x7f, 0x80, 0x00, 0x00
    , 0x00, 0x21, 0xff, 0x80, 0x00, 0x00
    , 0x00, 0x07, 0xff, 0x80, 0x00, 0x00
    , 0x00, 0x0f, 0xff, 0x80, 0x10, 0x00
    , 0x00, 0x1f, 0xff, 0x80, 0x00, 0x00
    , 0x00, 0x3f, 0xff, 0x82, 0x00, 0x00
    , 0x18, 0x3f, 0xff, 0xc0, 0x00, 0x00
    , 0x00, 0x3f, 0xff, 0xc0, 0x18, 0x00
    , 0x00, 0x3f, 0xff, 0xe0, 0x1c, 0x00
    , 0x00, 0x04, 0x1f, 0xf8, 0x00, 0x00
    , 0x03, 0xff, 0xf3, 0xfc, 0x00, 0x00
    , 0x07, 0xff, 0xf9, 0xff, 0x80, 0x00
    , 0x7f, 0xff, 0xfc, 0x7f, 0xf8, 0x00
    , 0xff, 0xff, 0xff, 0x9f, 0xff, 0x80
    , 0xff, 0xff, 0xff, 0xdf, 0xff, 0x00
    , 0xff, 0xff, 0xff, 0x9f, 0xfc, 0x00
    , 0x3f, 0xff, 0xff, 0x3f, 0xf0, 0x00
    , 0x00, 0xff, 0xf0, 0xfe, 0x00, 0x00
    , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
  };
  display.drawBitmap(10, 9, imExp, 42, 23, 1); // draw moon
}

void drawSkull() {
  // store image in EEPROM
  static const unsigned char PROGMEM imSku[] = {
    0x00, 0x00, 0xff, 0xc0, 0x00, 0x00
    , 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00
    , 0x00, 0x1f, 0xff, 0xfe, 0x00, 0x00
    , 0x00, 0x3f, 0xff, 0xff, 0x00, 0x00
    , 0x00, 0x78, 0x3f, 0x07, 0x80, 0x00
    , 0x00, 0xf8, 0x3f, 0x07, 0xc0, 0x00
    , 0x00, 0xff, 0xf3, 0xff, 0xc0, 0x00
    , 0x00, 0xff, 0xe1, 0xff, 0xc0, 0x00
    , 0x00, 0x7f, 0xff, 0xff, 0x80, 0x00
    , 0x00, 0x07, 0xff, 0xf8, 0x00, 0x00
    , 0x03, 0x87, 0xff, 0xf8, 0x70, 0x00
    , 0x07, 0xc7, 0xff, 0xf8, 0xfc, 0x00
    , 0x07, 0xc3, 0xff, 0xf0, 0xfc, 0x00
    , 0x1f, 0xf8, 0x00, 0x07, 0xfe, 0x00
    , 0x3f, 0xff, 0x80, 0x7f, 0xff, 0x00
    , 0x1e, 0x1f, 0xff, 0xfe, 0x1e, 0x00
    , 0x00, 0x01, 0xff, 0xe0, 0x00, 0x00
    , 0x0e, 0x07, 0xff, 0xfc, 0x1c, 0x00
    , 0x1f, 0xff, 0xc0, 0xff, 0xff, 0x00
    , 0x1f, 0xfc, 0x00, 0x0f, 0xfe, 0x00
    , 0x0f, 0xc0, 0x00, 0x00, 0xfc, 0x00
    , 0x0f, 0xc0, 0x00, 0x00, 0xfc, 0x00
    , 0x07, 0x80, 0x00, 0x00, 0x78, 0x00
  };
  display.drawBitmap(10, 9, imSku, 42, 23, 1); // draw skull
}


//********************************************************************************************************
//Welcome Img

void drawWel() {
  // store image in EEPROM
  static const unsigned char PROGMEM imDice[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    , 0x00, 0x38, 0x00, 0x01, 0xc0, 0x00, 0x3f, 0xc0, 0x00, 0xd6, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00
    , 0x01, 0x86, 0x00, 0x02, 0xa0, 0x00, 0xf0, 0xf0, 0x03, 0x31, 0x80, 0x01, 0x60, 0x00, 0x06, 0x00
    , 0x06, 0x00, 0x80, 0x04, 0x90, 0x01, 0x06, 0x08, 0x1f, 0xff, 0xe0, 0x06, 0x30, 0x00, 0x0f, 0x00
    , 0x18, 0x00, 0x60, 0x18, 0x84, 0x01, 0x04, 0x08, 0x10, 0x68, 0x30, 0x0e, 0x38, 0x00, 0x14, 0x80
    , 0x16, 0x01, 0xa0, 0x20, 0x82, 0x02, 0x04, 0x04, 0x18, 0xc4, 0x30, 0x1c, 0x14, 0x00, 0x24, 0x40
    , 0x11, 0x86, 0x20, 0x40, 0x81, 0x86, 0x04, 0x04, 0x18, 0x82, 0x70, 0x28, 0x0b, 0x00, 0x44, 0x20
    , 0x10, 0x38, 0x20, 0xc0, 0x81, 0x87, 0x0f, 0x1c, 0x15, 0x01, 0x70, 0xfe, 0x3f, 0x80, 0x84, 0x10
    , 0x10, 0x10, 0x20, 0x78, 0x8f, 0x02, 0xe0, 0xf4, 0x16, 0x01, 0xd0, 0xc1, 0xc1, 0x83, 0x04, 0x08
    , 0x10, 0x10, 0x20, 0x17, 0xf6, 0x02, 0x40, 0x28, 0x1f, 0xff, 0xf0, 0x20, 0x82, 0x02, 0x04, 0x04
    , 0x10, 0x10, 0x20, 0x08, 0x88, 0x01, 0x20, 0x48, 0x19, 0x03, 0x60, 0x10, 0x84, 0x01, 0x84, 0x18
    , 0x06, 0x10, 0xc0, 0x06, 0x90, 0x00, 0xa0, 0x50, 0x07, 0x87, 0x80, 0x04, 0x90, 0x00, 0x44, 0x60
    , 0x01, 0x92, 0x00, 0x01, 0xc0, 0x00, 0x3f, 0xc1, 0x80, 0xee, 0x00, 0x02, 0xa0, 0x00, 0x14, 0x80
    , 0x00, 0x38, 0x00, 0x00, 0x80, 0x00, 0x00, 0x07, 0xe0, 0x30, 0x00, 0x00, 0x80, 0x00, 0x0e, 0x00
    , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    , 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00
    , 0x00, 0x01, 0x8c, 0x30, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x02, 0x18, 0x40, 0x00
    , 0x00, 0x00, 0x4f, 0xd0, 0x00, 0x00, 0x00, 0x0f, 0xf0, 0x00, 0x00, 0x00, 0x02, 0xf9, 0x80, 0x00
    , 0x00, 0x00, 0x37, 0xa0, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x02, 0xf3, 0x00, 0x00
    , 0x00, 0x00, 0x0f, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xfc, 0x00, 0x00
    , 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00

  };
  display.drawBitmap(0, 10, imDice, 128, 21, 1);
}

//********************************************************************************************************
//Dice Draw

void diceDraw(){
  switch (currMenu) {
    case 0:
    static const unsigned char PROGMEM imd2[] = {
      0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x0f, 0xff, 0xf0, 0x00
      , 0x00, 0xe0, 0x00, 0x07, 0x00
      , 0x07, 0x00, 0x00, 0x00, 0xe0
      , 0x0c, 0x00, 0x00, 0x00, 0x30
      , 0x30, 0x00, 0x00, 0x00, 0x0c
      , 0x20, 0x00, 0x00, 0x00, 0x04
      , 0x20, 0x00, 0x00, 0x00, 0x04
      , 0x20, 0x00, 0x00, 0x00, 0x04
      , 0x30, 0x00, 0x00, 0x00, 0x0c
      , 0x38, 0x00, 0x00, 0x00, 0x1c
      , 0x36, 0x00, 0x00, 0x00, 0x6c
      , 0x31, 0xc0, 0x00, 0x03, 0x8c
      , 0x1d, 0xff, 0xc3, 0xfd, 0x38
      , 0x07, 0x86, 0x18, 0x61, 0xe0
      , 0x01, 0xf6, 0x18, 0x6f, 0x80
      , 0x00, 0x1f, 0xff, 0xf8, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00

    };
    display.drawBitmap(14, 10, imd2, 40, 22, 1); // draw d20
    break;
    case 1:
    static const unsigned char PROGMEM imd4[] = {
      0x00, 0x00, 0x40, 0x00, 0x00
      , 0x00, 0x00, 0xe0, 0x00, 0x00
      , 0x00, 0x01, 0xd8, 0x00, 0x00
      , 0x00, 0x03, 0x8c, 0x00, 0x00
      , 0x00, 0x06, 0x87, 0x00, 0x00
      , 0x00, 0x0c, 0x81, 0x80, 0x00
      , 0x00, 0x18, 0x80, 0xc0, 0x00
      , 0x00, 0x30, 0x00, 0x70, 0x00
      , 0x00, 0x61, 0x00, 0x18, 0x00
      , 0x00, 0xc1, 0x00, 0x0c, 0x00
      , 0x01, 0x81, 0x00, 0x03, 0x00
      , 0x03, 0x00, 0x00, 0x01, 0x80
      , 0x06, 0x02, 0x00, 0x00, 0xe0
      , 0x0c, 0x02, 0x00, 0x00, 0x30
      , 0x18, 0x02, 0x00, 0x00, 0x18
      , 0x0c, 0x02, 0x00, 0x00, 0x0e
      , 0x06, 0x04, 0x00, 0x00, 0xf8
      , 0x01, 0x84, 0x00, 0x1f, 0x00
      , 0x00, 0xc4, 0x03, 0xf0, 0x00
      , 0x00, 0x74, 0x3e, 0x00, 0x00
      , 0x00, 0x1f, 0xc0, 0x00, 0x00
      , 0x00, 0x08, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd4, 40, 22, 1); // draw d20
    break;
    case 2:
    static const unsigned char PROGMEM imd6[] = {
      0x00, 0x00, 0x38, 0x00, 0x00
      , 0x00, 0x01, 0xcf, 0x00, 0x00
      , 0x00, 0x07, 0x01, 0xc0, 0x00
      , 0x00, 0x3c, 0x00, 0x38, 0x00
      , 0x00, 0xe0, 0x00, 0x07, 0x00
      , 0x03, 0x80, 0x00, 0x00, 0xe0
      , 0x1c, 0x00, 0x00, 0x00, 0x38
      , 0x1c, 0x00, 0x00, 0x00, 0x38
      , 0x19, 0x80, 0x00, 0x01, 0x98
      , 0x18, 0x20, 0x00, 0x06, 0x18
      , 0x18, 0x0c, 0x00, 0x18, 0x18
      , 0x18, 0x01, 0x00, 0x60, 0x18
      , 0x18, 0x00, 0x61, 0x00, 0x18
      , 0x18, 0x00, 0x0c, 0x00, 0x18
      , 0x1c, 0x00, 0x04, 0x00, 0x70
      , 0x07, 0x00, 0x04, 0x01, 0xc0
      , 0x01, 0xe0, 0x04, 0x07, 0x00
      , 0x00, 0x38, 0x04, 0x1c, 0x00
      , 0x00, 0x07, 0x04, 0x30, 0x00
      , 0x00, 0x01, 0xc4, 0xc0, 0x00
      , 0x00, 0x00, 0x3f, 0x00, 0x00
      , 0x00, 0x00, 0x0c, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd6, 40, 22, 1); // draw d20
    break;
    case 3:
    static const unsigned char PROGMEM imd8[] = {
      0x00, 0x60, 0x00, 0x00, 0x00
      , 0x00, 0xff, 0x80, 0x00, 0x00
      , 0x00, 0xe0, 0x7e, 0x00, 0x00
      , 0x01, 0xa0, 0x01, 0xf8, 0x00
      , 0x01, 0x90, 0x00, 0x07, 0xf0
      , 0x03, 0x10, 0x00, 0x00, 0x1e
      , 0x03, 0x10, 0x00, 0x00, 0x1e
      , 0x06, 0x08, 0x00, 0x00, 0x8c
      , 0x04, 0x08, 0x00, 0x0c, 0x0c
      , 0x0c, 0x08, 0x00, 0x60, 0x18
      , 0x18, 0x04, 0x03, 0x00, 0x18
      , 0x18, 0x04, 0x18, 0x00, 0x30
      , 0x30, 0x04, 0xc0, 0x00, 0x30
      , 0x30, 0x0f, 0x00, 0x00, 0x60
      , 0x60, 0xc0, 0x80, 0x00, 0x40
      , 0x78, 0x00, 0x20, 0x00, 0xc0
      , 0x7e, 0x00, 0x08, 0x01, 0x80
      , 0x03, 0xf8, 0x02, 0x01, 0x80
      , 0x00, 0x0f, 0xc0, 0x83, 0x00
      , 0x00, 0x00, 0x3f, 0x33, 0x00
      , 0x00, 0x00, 0x00, 0xfe, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd8, 40, 22, 1); // draw d20
    break;
    case 4:
    static const unsigned char PROGMEM imd10[] = {
      0x00, 0x0c, 0x00, 0x00, 0x00
      , 0x00, 0x1f, 0xe0, 0x00, 0x00
      , 0x00, 0x34, 0x3e, 0x00, 0x00
      , 0x00, 0x64, 0x03, 0xe0, 0x00
      , 0x00, 0xc4, 0x00, 0x1e, 0x00
      , 0x01, 0x84, 0x00, 0x01, 0xf0
      , 0x03, 0x80, 0x00, 0x00, 0x1c
      , 0x03, 0x02, 0x00, 0x00, 0x26
      , 0x06, 0x02, 0x00, 0x00, 0x87
      , 0x0c, 0x02, 0x00, 0x01, 0x06
      , 0x18, 0x03, 0x28, 0x02, 0x0c
      , 0x30, 0x08, 0x00, 0x0c, 0x18
      , 0x60, 0x20, 0x00, 0x08, 0x30
      , 0xc0, 0x80, 0x00, 0x08, 0x60
      , 0x7f, 0x00, 0x00, 0x08, 0xc0
      , 0x38, 0xc0, 0x00, 0x09, 0x80
      , 0x0f, 0x98, 0x00, 0x0b, 0x00
      , 0x00, 0x7f, 0x00, 0x13, 0x00
      , 0x00, 0x07, 0xf0, 0x1e, 0x00
      , 0x00, 0x00, 0x3e, 0x1c, 0x00
      , 0x00, 0x00, 0x03, 0xf8, 0x00
      , 0x00, 0x00, 0x00, 0x10, 0x00
    };
    display.drawBitmap(14, 10, imd10, 40, 22, 1); // draw d20
    break;
    case 5:
    static const unsigned char PROGMEM imd12[] = {
      0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0xf8, 0x00, 0x00
      , 0x00, 0x07, 0x83, 0xc0, 0x00
      , 0x00, 0x18, 0x30, 0x3c, 0x00
      , 0x00, 0x60, 0x03, 0x03, 0x80
      , 0x01, 0x80, 0x00, 0x70, 0xe0
      , 0x0e, 0x00, 0x00, 0x40, 0xf0
      , 0x18, 0x00, 0x00, 0x80, 0x18
      , 0x38, 0x00, 0x00, 0x80, 0x18
      , 0x68, 0x00, 0x01, 0x00, 0x08
      , 0x64, 0x00, 0x02, 0x00, 0x0c
      , 0x24, 0x00, 0x02, 0x00, 0x0c
      , 0x32, 0x00, 0x04, 0x00, 0x0c
      , 0x32, 0x00, 0x38, 0x00, 0x04
      , 0x11, 0xf0, 0x06, 0x00, 0x0c
      , 0x19, 0x00, 0x01, 0x00, 0x18
      , 0x0d, 0x00, 0x00, 0x80, 0x30
      , 0x07, 0x00, 0x00, 0x20, 0xc0
      , 0x03, 0x00, 0x00, 0x11, 0x80
      , 0x01, 0xc0, 0x00, 0x0f, 0x00
      , 0x00, 0x3e, 0x00, 0x78, 0x00
      , 0x00, 0x01, 0xff, 0x80, 0x00
    };
    display.drawBitmap(14, 10, imd12, 40, 22, 1);
    break;
    case 6:
    static const unsigned char PROGMEM imd20[] = {
      0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x7f, 0xff, 0xfc, 0x00
      , 0x00, 0xff, 0x80, 0x0e, 0x00
      , 0x01, 0xe0, 0xf8, 0x0f, 0x00
      , 0x03, 0xa0, 0x0f, 0x99, 0x80
      , 0x07, 0x20, 0x00, 0xf8, 0xc0
      , 0x0e, 0x20, 0x01, 0xfe, 0x70
      , 0x1c, 0x20, 0x1f, 0x13, 0xb8
      , 0x38, 0x20, 0xf0, 0x10, 0xfc
      , 0x70, 0x37, 0x80, 0x10, 0x1e
      , 0xff, 0xfc, 0x00, 0x10, 0x07
      , 0x60, 0x7c, 0x00, 0x10, 0x0e
      , 0x30, 0x37, 0x80, 0x10, 0x1c
      , 0x18, 0x20, 0xf0, 0x10, 0x78
      , 0x0c, 0x20, 0x1c, 0x11, 0xf0
      , 0x06, 0x20, 0x07, 0x9f, 0x60
      , 0x03, 0x20, 0x00, 0xfc, 0xc0
      , 0x01, 0xa0, 0x03, 0xf9, 0x80
      , 0x00, 0xe0, 0x7e, 0x1b, 0x00
      , 0x00, 0x7f, 0xe0, 0x0e, 0x00
      , 0x00, 0x3f, 0xff, 0xfc, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd20, 40, 22, 1); // draw d20
    break;
  }

}

//********************************************************************************************************
//Dice Draw Rotate
void diceDrawr(){
  switch (currMenu) {
    case 0:
    static const unsigned char PROGMEM imd2r[] = {
      0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x0f, 0x80, 0x00
      , 0x00, 0x00, 0x66, 0x60, 0x00
      , 0x00, 0x00, 0x83, 0x30, 0x00
      , 0x00, 0x01, 0x00, 0xb8, 0x00
      , 0x00, 0x02, 0x00, 0xcc, 0x00
      , 0x00, 0x04, 0x00, 0x4c, 0x00
      , 0x00, 0x04, 0x00, 0x6c, 0x00
      , 0x00, 0x08, 0x00, 0x7e, 0x00
      , 0x00, 0x08, 0x00, 0x66, 0x00
      , 0x00, 0x08, 0x00, 0x66, 0x00
      , 0x00, 0x08, 0x00, 0x7e, 0x00
      , 0x00, 0x08, 0x00, 0x66, 0x00
      , 0x00, 0x08, 0x00, 0x44, 0x00
      , 0x00, 0x08, 0x00, 0x7c, 0x00
      , 0x00, 0x04, 0x00, 0x88, 0x00
      , 0x00, 0x04, 0x01, 0x98, 0x00
      , 0x00, 0x02, 0x03, 0xf0, 0x00
      , 0x00, 0x01, 0x06, 0x60, 0x00
      , 0x00, 0x00, 0xcc, 0xc0, 0x00
      , 0x00, 0x00, 0x1f, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd2r, 40, 22, 1); // draw d20
    break;
    case 1:
    static const unsigned char PROGMEM imd4r[] = {
      0x00,0x00,0x00,0x00,0x00
      ,0x00,0x00,0x00,0x00,0x00
      ,0x00,0x0e,0x00,0x00,0x00
      ,0x00,0x3b,0xe0,0x00,0x00
      ,0x00,0xe0,0x1f,0x00,0x00
      ,0x03,0x80,0x01,0xf0,0x00
      ,0x0e,0x00,0x00,0x0f,0x80
      ,0x18,0x00,0x00,0x00,0xf8
      ,0x38,0x03,0xff,0xff,0xff
      ,0x18,0x00,0x00,0x00,0x0e
      ,0x0c,0x00,0x00,0x00,0x38
      ,0x06,0x00,0x00,0x00,0xe0
      ,0x03,0x00,0x00,0x01,0x80
      ,0x01,0x80,0x00,0x06,0x00
      ,0x00,0x80,0x00,0x18,0x00
      ,0x00,0xc0,0x00,0x60,0x00
      ,0x00,0x60,0x01,0x80,0x00
      ,0x00,0x30,0x06,0x00,0x00
      ,0x00,0x18,0x1c,0x00,0x00
      ,0x00,0x0c,0x70,0x00,0x00
      ,0x00,0x07,0xc0,0x00,0x00
      ,0x00,0x03,0x00,0x00,0x00

    };
    display.drawBitmap(14, 10, imd4r, 40, 22, 1); // draw d20
    break;
    case 2:
    static const unsigned char PROGMEM imd6r[] = {
      0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x03, 0xf8, 0x00, 0x00
      , 0x00, 0x0e, 0x8f, 0xf0, 0x00
      , 0x00, 0x38, 0x40, 0x1c, 0x00
      , 0x00, 0x60, 0x20, 0x06, 0x00
      , 0x01, 0x80, 0x10, 0x03, 0x00
      , 0x06, 0x00, 0x08, 0x01, 0x80
      , 0x1c, 0x00, 0x04, 0x00, 0xc0
      , 0x70, 0x00, 0x02, 0x00, 0x60
      , 0x60, 0x00, 0x01, 0x00, 0x30
      , 0x60, 0x00, 0x00, 0x80, 0x1c
      , 0x30, 0x00, 0x01, 0x8f, 0x0e
      , 0x18, 0x00, 0x06, 0x00, 0x0e
      , 0x0c, 0x00, 0x18, 0x00, 0x1c
      , 0x06, 0x00, 0x60, 0x00, 0x70
      , 0x07, 0x01, 0x80, 0x01, 0xc0
      , 0x03, 0x06, 0x00, 0x07, 0x00
      , 0x01, 0x98, 0x00, 0x1c, 0x00
      , 0x00, 0xf0, 0x00, 0x70, 0x00
      , 0x00, 0x1f, 0xf9, 0xc0, 0x00
      , 0x00, 0x00, 0x0f, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd6r, 40, 22, 1); // draw d20
    break;
    case 3:
    static const unsigned char PROGMEM imd8r[] = {
      0x00, 0x00, 0x07, 0xe0, 0x00
      , 0x00, 0x00, 0x3c, 0xb0, 0x00
      , 0x00, 0x01, 0xe0, 0x98, 0x00
      , 0x00, 0x0f, 0x01, 0x0c, 0x00
      , 0x00, 0x78, 0x01, 0x06, 0x00
      , 0x03, 0xc0, 0x00, 0x03, 0x00
      , 0x1c, 0x00, 0x02, 0x01, 0x80
      , 0xe0, 0x00, 0x02, 0x00, 0xc0
      , 0xc0, 0x00, 0x04, 0x00, 0x70
      , 0xf0, 0x00, 0x04, 0x00, 0x38
      , 0x62, 0x00, 0x04, 0x00, 0x0c
      , 0x30, 0xc0, 0x08, 0x00, 0x06
      , 0x18, 0x18, 0x08, 0x00, 0x03
      , 0x0c, 0x03, 0x10, 0x00, 0x03
      , 0x06, 0x00, 0x70, 0xfe, 0x1f
      , 0x03, 0x00, 0x20, 0x00, 0x78
      , 0x01, 0x80, 0x20, 0x03, 0x80
      , 0x00, 0xc0, 0x40, 0x1c, 0x00
      , 0x00, 0x60, 0x81, 0xe0, 0x00
      , 0x00, 0x31, 0x0f, 0x00, 0x00
      , 0x00, 0x1d, 0x78, 0x00, 0x00
      , 0x00, 0x07, 0x80, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd8r, 40, 22, 1); // draw d20
    break;
    case 4:
    static const unsigned char PROGMEM imd10r[] = {
      0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x7f, 0xff, 0x80
      , 0x07, 0xff, 0x80, 0x31, 0x80
      , 0x0c, 0x00, 0x03, 0x01, 0x80
      , 0x1c, 0x00, 0x18, 0x00, 0xc0
      , 0x18, 0x6b, 0x80, 0x00, 0xc0
      , 0x18, 0x00, 0x80, 0x00, 0xc0
      , 0x0c, 0x00, 0x40, 0x00, 0xe0
      , 0x0c, 0x00, 0x20, 0x00, 0xe0
      , 0x0c, 0x00, 0x20, 0x00, 0xe0
      , 0x04, 0x00, 0x10, 0x00, 0xb0
      , 0x06, 0x00, 0x08, 0x00, 0xb0
      , 0x06, 0x00, 0x04, 0x00, 0xb0
      , 0x02, 0x00, 0x18, 0x70, 0x18
      , 0x03, 0x00, 0x60, 0x00, 0xd8
      , 0x03, 0x01, 0x00, 0x00, 0x58
      , 0x03, 0x04, 0x00, 0x00, 0x70
      , 0x01, 0xb0, 0x00, 0xff, 0xe0
      , 0x01, 0xff, 0xff, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd10r, 40, 22, 1); // draw d20
    break;
    case 5:
    static const unsigned char PROGMEM imd12r[] = {
      0x00, 0x01, 0xc0, 0x00, 0x00
      , 0x00, 0x0f, 0x3f, 0xfc, 0x00
      , 0x00, 0x38, 0x00, 0x07, 0x00
      , 0x01, 0xc0, 0x00, 0x03, 0x80
      , 0x03, 0x80, 0x00, 0x02, 0xe0
      , 0x06, 0x30, 0x00, 0x01, 0x30
      , 0x0c, 0x0c, 0x00, 0x01, 0x10
      , 0x18, 0x01, 0x00, 0x38, 0x98
      , 0x30, 0x00, 0x47, 0x00, 0x4c
      , 0x60, 0x00, 0x30, 0x00, 0x26
      , 0x60, 0x00, 0x20, 0x00, 0x16
      , 0x20, 0x00, 0x20, 0x00, 0x1b
      , 0x30, 0x00, 0x40, 0x00, 0x0e
      , 0x18, 0x00, 0x40, 0x00, 0x0e
      , 0x18, 0x00, 0x40, 0x00, 0x18
      , 0x0c, 0x00, 0x80, 0x00, 0x30
      , 0x06, 0x00, 0x80, 0x00, 0xc0
      , 0x07, 0xfd, 0x80, 0x01, 0x80
      , 0x01, 0xc0, 0x0e, 0x07, 0x00
      , 0x00, 0x3f, 0x00, 0x3c, 0x00
      , 0x00, 0x00, 0xff, 0xf0, 0x00
      , 0x00, 0x00, 0x00, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd12r, 40, 22, 1); // draw d20
    break;
    case 6:
    static const unsigned char PROGMEM imd20r[] = {
      0x00, 0x00, 0x1f, 0x80, 0x00
      , 0x00, 0x01, 0xfd, 0xe0, 0x00
      , 0x00, 0x1f, 0x38, 0xfc, 0x00
      , 0x00, 0xf0, 0x60, 0x67, 0x00
      , 0x0f, 0x00, 0xc0, 0x30, 0xe0
      , 0x0f, 0x03, 0x80, 0x18, 0x38
      , 0x09, 0xe6, 0x00, 0x0c, 0x0e
      , 0x18, 0x3f, 0x00, 0x06, 0x3c
      , 0x18, 0x3f, 0xff, 0xff, 0xec
      , 0x18, 0x76, 0x00, 0x07, 0x8c
      , 0x18, 0xc6, 0x00, 0x07, 0x8c
      , 0x31, 0x83, 0x00, 0x1c, 0xcc
      , 0x37, 0x01, 0x80, 0x30, 0x58
      , 0x3c, 0x01, 0x80, 0x60, 0x78
      , 0x38, 0x00, 0xc0, 0xc0, 0x78
      , 0x3c, 0x00, 0x63, 0x80, 0x38
      , 0x0f, 0xf0, 0x66, 0x00, 0x38
      , 0x03, 0xdf, 0xfc, 0xff, 0xf0
      , 0x00, 0x70, 0x7f, 0x3f, 0x00
      , 0x00, 0x1e, 0x31, 0xf0, 0x00
      , 0x00, 0x03, 0xff, 0x00, 0x00
      , 0x00, 0x00, 0xf0, 0x00, 0x00
    };
    display.drawBitmap(14, 10, imd20r, 40, 22, 1); // draw d20
    break;
  }

}
