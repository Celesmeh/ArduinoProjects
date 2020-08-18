int redPin = 4;
int greenPin = 5;
int bluePin = 6;

#define COMMON_ANODE
void setup() {
// initialize serial communication at 9600 bits per second:
pinMode(redPin, OUTPUT);
pinMode(greenPin, OUTPUT);
pinMode(bluePin, OUTPUT);
 Serial.begin(9600);
}

void setColor(int red, int green, int blue)
{
#ifdef COMMON_ANODE
red = 255 - red;
green = 255 - green;
blue = 255 - blue;
#endif
analogWrite(redPin, red);
analogWrite(greenPin, green);
analogWrite(bluePin, blue);
} 


String str;

void r(){
  setColor(255, 0, 0); // red
  Serial.println("The red led is on now");
}

void g(){
setColor(0, 255, 0); // green 
  Serial.println("The green led is on now");
}

void b(){
 setColor(0, 0, 255); // blue
   Serial.println("The blue led is on now");
}

void y(){
 setColor(255, 255, 0);// yellow
   Serial.println("The yellow led is on now");
}

void a(){
setColor(0, 255, 255);// aqua 
  Serial.println("The aqua led is on now");
}

void on(){
setColor(255, 255, 255);// on
  Serial.println("The light is on now");
}

void off(){
setColor(0, 0, 0);// off
  Serial.println("The light is off now");
}


void loop() {
 
  if(Serial.available())
{
str = Serial.readStringUntil('\n');

if(str == "g"){
g();
  }

if(str == "r"){
r();
  }

if(str == "b"){
b();
  }

if(str == "y"){
y();
  }

if(str == "a"){
a();
  }

if(str == "off"){
off();
  }

if(str == "on"){
on();
  }
 }
}
