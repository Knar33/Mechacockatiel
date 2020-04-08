#include <Herkulex.h>

int hip = 0x00;
float hipUpperBound = 100;
float hipLowerBound = 10;

int face = 0x01;
float faceUpperBound = 150;
float faceLowerBound = -150;

int head = 0x02;
float headUpperBound = 150;
float headLowerBound = -150;

long baudRate = 57600;

void setup()
{
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(baudRate);    // Open serial communications
  Serial.println("Begin");
  Herkulex.begin(baudRate,10,11); //open serial with rx=10 and tx=11
  Herkulex.reboot(hip); //reboot first motor
  delay(500);
  Herkulex.initialize(); //initialize motors
  delay(2000);

  //Change the baud rate of a single motor: 0x10=115200, 0x22=57600
  //Herkulex.writeRegistryEEP(head, 0x04, 0x22);
  //delay(2000);
}

void loop(){
  potentiometerControl();
}

void potentiometerControl() {
  float hipRotation = ((float)analogRead(A0) / 3.2) - 160;
  float faceRotation = ((float)analogRead(A1) / 3.2) - 160;
  float headRotation = ((float)analogRead(A2) / 3.2) - 160;

  rotateMotor(hip, hipRotation, 0, hipUpperBound, hipLowerBound);
  rotateMotor(face, faceRotation, 0, faceUpperBound, faceLowerBound);
  rotateMotor(head, headRotation, 0, headUpperBound, headLowerBound);

  errorCheck(hip);
  errorCheck(face);
  errorCheck(head);
  
  delay(33);
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

void errorCheck(int motorId) {
  int status = Herkulex.stat(motorId);
  if (status != 0) {
    String errorMessage = "Motor error on motor ID ";
    errorMessage += motorId;
    errorMessage += ": ";
    errorMessage += status;
    Serial.println(errorMessage);
  }
}
