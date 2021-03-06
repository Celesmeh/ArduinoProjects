
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
    for (int i = 0; i <= 60; i++) {
      if (count < 255) {
        count++;
        g--;
        b--;
        setColor(count, g, b); // blue
        delay(50);
      }
      else {
        setColor(255 , 0 , 0);
      }
    }
    Serial.println("cup");
  }
  else {
    count = 0;
    g = 255;
    b = 255;
    setColor(0, 255, 255); // red
    Serial.println("no cup");
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
