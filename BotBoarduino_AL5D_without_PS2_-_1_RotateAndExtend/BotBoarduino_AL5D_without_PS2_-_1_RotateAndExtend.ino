//#if ARDUINO >= 100
#include "Arduino.h"
//#else
//#include "WProgram.h"
//#end if

#include <Servo.h>
#include <math.h>

//comment to disable the Force Sensitive Resister on the gripper
//#define FSRG

//Select which arm by uncommenting the corresponding line
//#define AL5A
//#define AL5B
#define AL5D

//uncomment for digital servos in the Shoulder and Elbow
//that use a range of 900ms to 2100ms
//#define DIGITAL_RANGE

#ifdef AL5A
const float A = 3.75;
const float B = 4.25;
#elif defined AL5B
const float A = 4.75;
const float B = 5.00;
#elif defined AL5D
const float A = 5.75;
const float B = 7.375;
#endif

//Arm Servo pins
#define Base_pin 2
#define Shoulder_pin 3
#define Elbow_pin 4
#define Wrist_pin 10
#define Gripper_pin 11
#define WristR_pin 12

//Onboard Speaker
#define Speaker_pin 5

//Radians to Degrees constant
const float rtod = 57.295779;

//Arm Speed Variables
float Speed = 1.0;
int sps = 3;

//Servo Objects
Servo Elb;
Servo Shldr;
Servo Wrist;
Servo Base;
Servo Gripper;
Servo WristR;

//Arm Current Pos
float X = 4;
float Y = 4;
int Z = 90;
int G = 90;
float WA = 0;
int WR = 90;

//Arm temp pos
float tmpx = 4;
float tmpy = 4;
int tmpz = 90;
int tmpg = 90;
int tmpwr = 90;
float tmpwa = 0;

//boolean mode = true;

void setup()
{
  Serial.begin(9600);
  Base.attach(Base_pin);
  Shldr.attach(Shoulder_pin);
  Elb.attach(Elbow_pin);
  Wrist.attach(Wrist_pin);
  Gripper.attach(Gripper_pin);
  WristR.attach(WristR_pin);
}

int Arm(float x, float y, float z, int g, float wa, int wr) //Here's all the Inverse Kinematics to control the arm
{
  float M = sqrt((y*y)+(x*x));
  if(M <= 0)
    return 1;
  float A1 = atan(y/x);
  if(x <= 0)
    return 1;
  float A2 = acos((A*A-B*B+M*M)/((A*2)*M));
  float Elbow = acos((A*A+B*B-M*M)/((A*2)*B));
  float Shoulder = A1 + A2;
  Elbow = Elbow * rtod;
  Shoulder = Shoulder * rtod;
  if((int)Elbow <= 0 || (int)Shoulder <= 0)
    return 1;
  float Wris = abs(wa - Elbow - Shoulder) - 90;
#ifdef DIGITAL_RANGE
  Elb.writeMicroseconds(map(180 - Elbow, 0, 180, 900, 2100  ));
  Shldr.writeMicroseconds(map(Shoulder, 0, 180, 900, 2100));
#else
  Elb.write(180 - Elbow);
  Shldr.write(Shoulder);
#endif
  Wrist.write(180 - Wris);
  Base.write(z);
  WristR.write(wr);
#ifndef FSRG
  Gripper.write(g);
#endif
  Y = tmpy;
  X = tmpx;
  Z = tmpz;
  WA = tmpwa;
#ifndef FSRG
  G = tmpg;
#endif
  return 0; 
}

float x1 = 0;
float x2 = 180;
float xs = 5.4;

void loop()
{
  // Example of rotating arm
  for(float i = x1; i <= x2; i += xs)
  {
    if(Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr))
    {
       Serial.println("NONREAL Answer");
    }
//    tmpx = i;
    tmpx = (i/30)+2;
//    tmpy = i;
    tmpz = i;
//    tmpg = i;
//    tmpwa = i;
//    tmpwr = i;
    Serial.print("tmpx = "); Serial.print(tmpx, DEC); Serial.print("\ttmpy = "); Serial.print(tmpy, DEC); Serial.print("\ttmpz = "); Serial.print(tmpz, DEC); Serial.print("\ttmpg = "); Serial.print(tmpg, DEC); Serial.print("\ttmpwa = "); Serial.print(tmpwa, DEC); Serial.print("\ttmpwr = "); Serial.println(tmpwr, DEC);
    if(tmpx < 2 && tmpy < 2)
    {
      tmpy = tmpy + 0.05;
      Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
    }
    else if(tmpx < 1 && tmpy < 2 )
    {
      tmpx = tmpx + 0.05;
      Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
    }
    delay(30);
  }
  for(float i = x2; i >= x1; i -= xs)
  {
    if(Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr))
    {
       Serial.println("NONREAL Answer");
    }
//    tmpx = i;
    tmpx = (i/30)+2;
//    tmpy = i;
    tmpz = i;
//    tmpg = i;
//    tmpwa = i;
//    tmpwr = i;
     Serial.print("tmpx = "); Serial.print(tmpx, DEC); Serial.print("\ttmpy = "); Serial.print(tmpy, DEC); Serial.print("\ttmpz = "); Serial.print(tmpz, DEC); Serial.print("\ttmpg = "); Serial.print(tmpg, DEC); Serial.print("\ttmpwa = "); Serial.print(tmpwa, DEC); Serial.print("\ttmpwr = "); Serial.println(tmpwr, DEC);
    if(tmpx < 2 && tmpy < 2)
    {
      tmpy = tmpy + 0.05;
      Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
    }
    else if(tmpx < 1 && tmpy < 2 )
    {
      tmpx = tmpx + 0.05;
      Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
    }
    delay(30);
  }
}
