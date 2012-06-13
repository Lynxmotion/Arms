#include <Servo.h>
#include <PS2X_lib.h>

//#define DEBUG

//comment to disable the Force Sensitive Resister on the gripper
//#define FSRG

//FSRG pin Must be analog!!
#define FSRG_pin A1

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

//PS2 pins
#define DAT 6
#define CMD 7
#define ATT 8
#define CLK 9

//PS2 analog joystick Deadzone
#define Deadzone 4

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
Servo WristR;
Servo Gripper;

//Arm Current Pos
float X = 4;
float Y = 4;
int Z = 90;
int G = 90;
int WR = 90;
float WA = 0;

//Arm temp pos
float tmpx = 4;
float tmpy = 4;
int tmpz = 90;
int tmpg = 90;
int tmpwr = 90;
float tmpwa = 0;

//PS2X Variables
PS2X ps2x;
int error = 0; 
byte type = 0;

boolean mode = true;

void setup()
{
#ifdef DEBUG
  Serial.begin(115200);
#endif

  error = ps2x.config_gamepad(CLK,CMD,ATT,DAT, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
#ifdef DEBUG
  if(error == 0)
    Serial.println("Found Controller, configured successful");
   
  else if(error == 1)
    Serial.println("No controller found");
   
  else if(error == 2)
    Serial.println("not accepting commands");
   
  else if(error == 3)
    Serial.println("refusing Pressures mode");
   
  type = ps2x.readType(); 
    switch(type) 
    {
      case 0:
       Serial.println("Unknown");
       break;
      case 1:
       Serial.println("DualShock");
       break;
      case 2:
       Serial.println("GuitarHero");
       break;
    }
#endif

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
  WR = tmpwr;
  return 0; 
}


void loop()
{
  ps2x.read_gamepad(); //update the ps2 controller
  
  int LSY = 128 - ps2x.Analog(PSS_LY);
  int LSX = ps2x.Analog(PSS_LX) - 128;
  int RSY = 128 - ps2x.Analog(PSS_RY);
  int RSX = ps2x.Analog(PSS_RX) - 128;

  if(RSY > Deadzone || RSY < -Deadzone)
    tmpy = max(Y + RSY/1000.0*Speed, -1);
  
  if(RSX > Deadzone || RSX < -Deadzone)
    tmpx = max(X + RSX/1000.0*Speed, -0.5);
    
  if(LSY > Deadzone || LSY < -Deadzone)
    tmpwa = constrain(WA + LSY/100.0*Speed, 0, 180);

  if(LSX > Deadzone || LSX < -Deadzone)
    tmpz = constrain(Z + LSX/100.0*Speed, 0, 180);
 
  if(ps2x.Button(PSB_R1))
  {
    #ifdef FSRG
    while(analogRead(FSRG_pin) < 400)
    {
      Gripper.write(min(Gripper.read() + 2, 170));
      if(Gripper.read() == 170)
        break;
      #ifdef DEBUG
      Serial.print(analogRead(FSRG_pin));
      Serial.print(" ");
      Serial.println(Gripper.read());
      #endif
      delay(10);
    }
    #else
    tmpg = min(G + 5*Speed, 170);
    #endif
  }
  if(ps2x.Button(PSB_R2))
  {
    #ifdef FSRG
    while(Gripper.read() > 90)
    {
      
      Gripper.write(max(Gripper.read() - 2, 90));
      #ifdef DEBUG
      Serial.println(Gripper.read());
      #endif
      delay(10);
    }
    #else
    tmpg = max(G - 5*Speed, 10);
    #endif
  }
  
  if(ps2x.ButtonPressed(PSB_BLUE))
  {
    int pos = Gripper.readMicroseconds();
    pos -= pos % 10;
    while(pos != 1500)
    {
      pos += ((pos - 1500 > 0)? -10 : 10);
      Gripper.writeMicroseconds(pos);
      delay(25);
    }
    tmpg = 90;
    G = 90;
  }
  
  if(ps2x.ButtonPressed(PSB_GREEN))
  {
    int pos = WristR.readMicroseconds();
    pos -= pos % 10;
    while(pos != 1500)
    {
      pos += ((pos - 1500 > 0)? -10 : 10);
      WristR.writeMicroseconds(pos);
      delay(25);
    }
    tmpwr = 90;
    WR = 90;
  }
 
  if(ps2x.Button(PSB_L1))
    tmpwr = max(WR + 2*Speed, 0);
  else if(ps2x.Button(PSB_L2))
    tmpwr = min(WR - 2*Speed, 180);
 
 
  if(ps2x.ButtonPressed(PSB_PAD_UP))
  {
    sps = min(sps + 1, 5);
    tone(Speaker_pin, sps*500, 200);
  }
  else if(ps2x.ButtonPressed(PSB_PAD_DOWN))
  {
    sps = max(sps - 1, 1);
    tone(Speaker_pin, sps*500, 200);
  }
  
  Speed = sps*0.20 + 0.60;
      
 if(Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr))
   {
     #ifdef DEBUG
     Serial.print("NONREAL Answer");
     #endif
   }

 if(tmpx < 2 && tmpy < 2 && RSX < 0)
   {
     tmpy = tmpy + 0.05;
     Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
   }
 else if(tmpx < 1 && tmpy < 2 && RSY < 0)
   {
     tmpx = tmpx + 0.05;
     Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr);
   }
 delay(30);
}

