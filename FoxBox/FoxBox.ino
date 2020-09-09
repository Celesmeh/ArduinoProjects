#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
#include <RTClib.h>

//LCD stuff
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);


// animaiton vars
int eyeStart = 3;
int eyeEnd = 4;

//time shit
unsigned long prevMs = 0;
unsigned long curMs = 0;

//rtc
RTC_DS3231 rtc;

// time vars
int hour = 3600000;
int halfHour = 1800000;
int minute = 60000;
int halfMinute = 30000;
const byte seconds = 0;
const byte minutes = 0;
const byte hours = 16;
const byte day = 15;
const byte month = 6;
const byte year = 15;

// Time Tirggers

int Lunch = 12;
int water = 45;
int quote1 = 10;
int quote2 = 13;
int quote3 = 16;

// sounds
int speakerPin = 9;
int numTones = 4;
int chirp[] = {990, 880};

//debug
int countDisp = 0;

// Custom Characters
byte eyeBR[] = {
  B00100,
  B00100,
  B00100,
  B01000,
  B01000,
  B10000,
  B10000,
  B10000
};

byte eyeBL[] = {
  B00100,
  B00100,
  B00100,
  B00010,
  B00010,
  B00001,
  B00001,
  B00001
};

byte eyeTL[] = {
  B00000,
  B00000,
  B00000,
  B10000,
  B10000,
  B01000,
  B01000,
  B01000
};

byte eyeTR[] = {
  B00000,
  B00000,
  B00000,
  B00001,
  B00001,
  B00010,
  B00010,
  B00010
};

//let set shit up
void setup() {


  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
  lcd.init();
  lcd.backlight();
  lcd.createChar(1, eyeTR);
  lcd.createChar(2, eyeTL);
  lcd.createChar(3, eyeBR);
  lcd.createChar(4, eyeBL);

  // initialize RTC
  if (!rtc.begin()) {
    Serial.println("ERROR");
    return;
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  // Set the time
  DateTime now = rtc.now();
  Serial.begin(9600);
  foxChirp();

}

//loop stuff
void loop() {
  DateTime now = rtc.now();
  
  //EYES
  eyeStatic();
//  if (now.minute() % 3) {
//    eyeIdle();
//  }

  //WATER 
  if (now.minute() == water){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("Hey! You should ");
    lcd.setCursor(2,1);
    lcd.print("Drink water!!");
    foxChirp();
    delay(50000);
    lcd.clear();
    }
  

  if (now.hour() == 1 && now.minute() == 56) {

  }
  timeSerials();

}

// FUNctions
void eye() {
  lcd.setCursor(eyeStart, 0);
  lcd.write(byte(1));
  lcd.setCursor(eyeEnd, 0);
  lcd.write(byte(2));
  lcd.setCursor(eyeStart, 1);
  lcd.write(byte(3));
  lcd.setCursor(eyeEnd, 1);
  lcd.write(byte(4));
}

void eyeStatic() {
  eyeStart = 2;
  eyeEnd = 3;
  eye();
  eyeStart = 10;
  eyeEnd = 11;
  eye();
}


void eyeIdle() {
  for (int i = 0; i < 5; i++) {
    eyeStart = 2;
    eyeEnd = 3;
    eye();
    eyeStart = 10;
    eyeEnd = 11;
    eye();
    delay(1000);
    lcd.clear();
    eyeStart = 3;
    eyeEnd = 4;
    eye();
    eyeStart = 11;
    eyeEnd = 12;
    eye();
    delay(1000);
    lcd.clear();

  }
}

void foxChirp() {

  for (int i = 0; i < numTones; i++)
  {
    tone(speakerPin, chirp[i], 200);
    delay(500);
  }

}

void timeSerials() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(" (");
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(" )");
  Serial.println();

}

void whoah() {
  Serial.print ("whoah");
  delay(1000);
}
