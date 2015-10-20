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
float Z = 90;
int G = 90;
float WA = 0;
int WR = 90;

//Arm temp pos
float tmpx = 4;
float tmpy = 4;
float tmpz = 90;
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

// Number of positions to cycle through
const int numPos = 10;

// XYZ position of the gripper in relation to the base & wrist angle
float posListXYZWa[][4] =
{
  {5,8,90,0},
  {8,3,90,0},
  {5,5,120,0},
  {5,5,90,0},
  {5,5,60,0},
  {5,10,90,0},
  {5,10,90,0},
  {5,10,90,0},
  {5,10,90,0},
  {5,3,90,0}
};

// Gripper closing and wrist rotation
int posListGWr[][2] =
{
  {90,90},
  {90,90},
  {90,90},
  {90,90},
  {90,90},
  {90,90},
  {0,0},
  {120,180},
  {0,0},
  {90,90}
};

// Delay between moves
long posListDelay[] =
{
  3000,
  2000,
  1000,
  1000,
  3000,
  1000,
  500,
  500,
  500,
  3000
};
long lastReferenceTime;

void loop()
{
  // Example - Follow set of positions
  for(int i=0; i<numPos; i++)
  {
    // Set positions from array
    tmpx = posListXYZWa[i][0];
    tmpy = posListXYZWa[i][1];
    tmpz = posListXYZWa[i][2];
    tmpg = posListGWr[i][0];
    tmpwa = posListXYZWa[i][3];
    tmpwr = posListGWr[i][1];
    
    // Display position
    Serial.print("tmpx = "); Serial.print(tmpx, DEC); Serial.print("\ttmpy = "); Serial.print(tmpy, DEC); Serial.print("\ttmpz = "); Serial.print(tmpz, DEC); Serial.print("\ttmpg = "); Serial.print(tmpg, DEC); Serial.print("\ttmpwa = "); Serial.print(tmpwa, DEC); Serial.print("\ttmpwr = "); Serial.println(tmpwr, DEC);
    Serial.print("Delay = "); Serial.println(posListDelay[i], DEC); Serial.println("");
    
    // Move arm
    Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
    
    // Pause for the required delay
    lastReferenceTime = millis();
    while(millis() <= (posListDelay[i] + lastReferenceTime)){};
  }
}
