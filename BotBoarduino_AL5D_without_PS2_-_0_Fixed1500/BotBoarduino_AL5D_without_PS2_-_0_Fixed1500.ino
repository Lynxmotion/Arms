#include "Arduino.h"

#include <Servo.h>

// Arm Servo pins
#define Base_pin 2
#define Shoulder_pin 3
#define Elbow_pin 4
#define Wrist_pin 10
#define Gripper_pin 11
#define WristR_pin 12

// Onboard Speaker
#define Speaker_pin 5

// Servo Objects
Servo Elb;
Servo Shldr;
Servo Wrist;
Servo Base;
Servo Gripper;
Servo WristR;

void setup()
{
  // Setup serial
  Serial.begin(9600);
  Base.attach(Base_pin);
  Shldr.attach(Shoulder_pin);
  Elb.attach(Elbow_pin);
  Wrist.attach(Wrist_pin);
  Gripper.attach(Gripper_pin);
  WristR.attach(WristR_pin);
  pinMode(Speaker_pin, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // Tone & wait
  tone(Speaker_pin, 440, 500);
  delay(1500);

  // Tone and move to 1500
  tone(Speaker_pin, 220, 1000);
  delay(1000);
  Base.writeMicroseconds(1500);
  Shldr.writeMicroseconds(1500);
  Elb.writeMicroseconds(1500);
  Wrist.writeMicroseconds(1500);
  Gripper.writeMicroseconds(1500);
  WristR.writeMicroseconds(1500);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
}

