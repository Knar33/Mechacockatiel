#include <Herkulex.h>

int motor0=0x00;
int motor1=0x01;
int motor2=0x02;

void setup()
{
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.begin(115200,10,11); //open serial with rx=10 and tx=11
  Herkulex.reboot(motor0); //reboot first motor
  delay(500);
  Herkulex.initialize(); //initialize motors
  delay(2000);
}

void loop(){
  float pot0 = (float)analogRead(A0);
  float pot1 = (float)analogRead(A1);
  float pot2 = (float)analogRead(A2);
  
  float rotation0 = (pot0 / 3.2) - 160;
  float rotation1 = (pot1 / 3.2) - 160;
  float rotation2 = (pot2 / 3.2) - 160;

  Herkulex.moveOneAngle(motor0, (float)rotation0, 0, LED_BLUE);
  Herkulex.moveOneAngle(motor1, (float)rotation1, 0, LED_BLUE);
  Herkulex.moveOneAngle(motor2, (float)rotation2, 0, LED_BLUE);
  
  delay(33);
}
