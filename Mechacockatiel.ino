#include <Herkulex.h>

int hip = 0x00;
int face = 0x01;
int head = 0x02;

void setup()
{
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin");
  Herkulex.begin(115200,10,11); //open serial with rx=10 and tx=11
  Herkulex.reboot(hip); //reboot first motor
  delay(500);
  Herkulex.initialize(); //initialize motors
  delay(2000);
}

void loop(){
  float hipRotation = ((float)analogRead(A0) / 3.2) - 160;
  float faceRotation = ((float)analogRead(A1) / 3.2) - 160;
  float headRotation = ((float)analogRead(A2) / 3.2) - 160;

  rotateHipMotor(hipRotation, 0);
  rotateFaceMotor(faceRotation, 0);
  rotateHeadMotor(headRotation, 0);

  errorCheck();
  
  delay(33);
}

void rotateHipMotor(float position, int time) {
  rotateMotor(hip, position, time, 100, 10);
}

void rotateFaceMotor(float position, int time) {
  rotateMotor(face, position, time, 150, -150);
}

void rotateHeadMotor(float position, int time) {
  rotateMotor(head, position, time, 150, -150);
}

void rotateMotor(int motorId, float position, int time, float upperBound, float lowerBound) {
  if (position > upperBound) {
    position = upperBound;
  }
  if (position < lowerBound) {
    position = lowerBound;
  }
  
  Herkulex.moveOneAngle(motorId, position, time, LED_BLUE);
}

void errorCheck() {
  byte hipStat = Herkulex.stat(hip);
  byte faceStat = Herkulex.stat(face);
  byte headStat = Herkulex.stat(head);

  String hipError = "Hip: ";
  hipError += hipStat;
  String faceError = "Face: ";
  faceError += faceStat;
  String headError = "Head: ";
  headError += headStat;
  
  Serial.println(hipError);
  Serial.println(faceError);
  Serial.println(headError);
}
