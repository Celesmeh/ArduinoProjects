int IRSensor = 2; // connect ir sensor to arduino pin 2
int red_light_pin = 11;
int green_light_pin = 10;
int blue_light_pin = 9;


void setup()
{
  pinMode(red_light_pin, OUTPUT);
  pinMode(green_light_pin, OUTPUT);
  pinMode(blue_light_pin, OUTPUT);
  pinMode (IRSensor, INPUT); // sensor pin INPUT
}

void loop()
{
  int statusSensor = digitalRead (IRSensor);

  if (statusSensor == 1) {
    RGB_color(0, 255, 255 ); // Red
  }
  else {
    RGB_color(255, 0 , 0 ); //
  }

}
void RGB_color(int red_light_value, int green_light_value, int blue_light_value)
 {
  analogWrite(red_light_pin, red_light_value);
  analogWrite(green_light_pin, green_light_value);
  analogWrite(blue_light_pin, blue_light_value);
}
