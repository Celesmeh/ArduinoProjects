
int r = 0, g = 0, b = 255, count = 0;

void setup()
{
  // Debug console
  Serial.begin(9600);

  //Blynk.begin(auth, ssid, pass);
  pinMode(4, INPUT);
  pinMode(2, INPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);


}

void loop()
{
  if (digitalRead(4))
  {
    setColor(255, 0, 0); // red
    Serial.println("The red led is on now");
  }

  else
  {
    setColor(00, 255, 255); // red
    Serial.println("The blue led is on now");
  }
  delay(100);
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
