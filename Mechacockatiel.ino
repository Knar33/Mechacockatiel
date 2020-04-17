#include <HerkulexServo.h>

int hip = 0x00;
int face = 0x01;
int head = 0x02;

long baudRate = 57600;

void setup()
{
  delay(2000);
  Serial.begin(baudRate);
  Serial.println("Begin");
}

void loop(){
  something();
}

void something() {
  
}

void nothing() {
  
}
