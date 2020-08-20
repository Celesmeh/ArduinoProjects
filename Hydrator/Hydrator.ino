43eAR

7
int r = 0, g = 255, b = 255, count = 0;

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()
{
  if ( digitalRead(4)) {
    count = 0;
    g = 255;
    b = 255;
    setColor(0, 255, 255); // red
    Serial.println("The blue led is on now");
  }
  else {
    for (int i = 0; i <= 60; i++) {
      if (count < 255) {
        count++;
        g--;
        b--;
        setColor(count, g, b); // blue
        delay(12000);
      }
//      else {
//        setColor(255 , 0 , 0);
//      }
    }
  }
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
  red = 255 - red;
  green = 255 - green;
  blue = 255 - blue;
#endif
  analogWrite(11, red);
  analogWrite(10, green);
  analogWrite(9, blue);
}
