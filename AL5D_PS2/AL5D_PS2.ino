#include <SoftwareSerial.h>
#include <PS2X_lib.h>

#define DEBUG

#define DBGSerial Serial
SoftwareSerial SSCSerial(13, 12);


//comment to disable the Force Sensitive Resister on the gripper
//#define FSRG

//FSRG pin Must be analog!!
#define FSRG_pin A1

//uncomment for digital servos in the Shoulder and Elbow
//that use a range of 900ms to 2100ms
//#define DIGITAL_RANGE

//Select which arm by uncommenting the corresponding line
//#define AL5A
//#define AL5B
#define AL5D

#ifdef AL5A
const float A = 3.75;
const float B = 4.25;
#elif defined AL5B
const float A = 4.75;
const float B = 5.00;
#elif defined AL5D
const float A = 5.75; // distance between shoulder axis and elbow axis in inches
const float B = 7.375;// distance between elbow axis and wrist axis in inches
#endif

//PS2 pins connected to BotBoarduino
#define DAT 6
#define CMD 7
#define ATT 8
#define CLK 9

//PS2 analog joystick Deadzone
#define Deadzone 10

//Math constants
const float rtod = 57.295779;
const float atop = 11.111;

//Arm Speed Variables
float Arm_Speed = 1.0;
int Arm_sps = 3;

//Arm Current Pos
float X = 4;
float Y = 4;
int Z = 1500;
int G = 1500;
int WR = 1500; // wrist rotate default position
float WA = 0;

//Arm temp pos
float tmpx = 4;
float tmpy = 4;
int tmpz = 1500;
int tmpg = 1500;
int tmpwr = 1500;
float tmpwa = 0;

PS2X ps2x;

boolean mode = true;

void setup()
{
  DBGSerial.begin(57600);
  SSCSerial.begin(38400);
  pinMode(7, INPUT);
  pinMode(5, OUTPUT);
  if(!digitalRead(7))
  {
    tone(5, 1000, 500);
    SSCForwarder();
  }
  
// SSC-32 debugging
  int error = 0;
  error = ps2x.config_gamepad(CLK,CMD,ATT,DAT, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  
#ifdef DEBUG
  if(error == 0)
    DBGSerial.println("Found Controller, configured successful");
   
  else if(error == 1)
    DBGSerial.println("No controller found");
   
  else if(error == 2)
    DBGSerial.println("not accepting commands");
   
  else if(error == 3)
    DBGSerial.println("refusing Pressures mode");
    
  byte type = 0;
  type = ps2x.readType(); 
    switch(type) 
    {
      case 0:
       DBGSerial.println("Unknown");
       break;
      case 1:
       DBGSerial.println("DualShock");
       break;
      case 2:
       DBGSerial.println("GuitarHero");
       break;
    }
#endif 
  
}

void SSCForwarder() 
{
    delay(2000);
    int sChar;
    int sPrevChar;
    
    while(digitalRead(7)) {
        if ((sChar = DBGSerial.read()) != -1) {
            SSCSerial.write(sChar & 0xff);
            if (((sChar == '\n') || (sChar == '\r')) && (sPrevChar == '$'))
                break;    // exit out of the loop
            sPrevChar = sChar;
        }     
        if ((sChar = SSCSerial.read()) != -1) {
            DBGSerial.write(sChar & 0xff);
        }
    }
}

int Arm(float x, float y, float z, int g, float wa, int wr) //Here's all the Inverse Kinematics to control the arm
{
  float M = sqrt((y*y)+(x*x)); // radial length between the base axis and the gripper axis
  if(M <= 0) // if the angle is less than 0, do not attempt to move there
    return 1;
  float A1 = atan(y/x); // The calculation above determines the angle between the horizontal and the angle formed between the shoulder axis and the wrist axis. 
  if(x <= 0) // if the angle is less than 0, do not attempt to move there
    return 1;
  float A2 = acos((A*A-B*B+M*M)/((A*2)*M)); // This is the angle between the line formed between the shoulder axis and the wrist axis and the line formed between the shoulder and elbow
  float Elbow = acos((A*A+B*B-M*M)/((A*2)*B)); // This is the angle between the line formed between the elbow axis and the shoulder axis and the line formed between the elbow axis and the wrist axis
  float Shoulder = A1 + A2; // This is the angle between the horizontal and the line formed between the shoulder axis and the elbow axis
  Elbow = Elbow * rtod;
  Shoulder = Shoulder * rtod;  
  while((int)Elbow <= 0 || (int)Shoulder <= 0) // if the angle is less than 0, do not attempt to move there
    return 1;
  float Wrist = abs(wa - Elbow - Shoulder) + 7.50; // the wrist is not included in the above calculations and is set at a predetermined angle w.r.t. the horizontal.
#ifdef DIGITAL_RANGE
  Elbow = map((180 - Elbow) * atop, 500, 2500, 900, 2100); // convert the angle to pulse for the elbow
  Shoulder = map(Shoulder*atop + 500, 500, 2500, 900, 2100); //convert the angle to pulse for the shoulder
#else
  Elbow = (180 - Elbow) * atop;
  Shoulder = Shoulder * atop + 500;
#endif
  Wrist = (180 - Wrist) * atop + 500;
  SSCSerial.print("#10 P");
  SSCSerial.println(z);
  SSCSerial.print(" #11 P");
  SSCSerial.print(Shoulder);
  SSCSerial.print(" #12 P");
  SSCSerial.print(Elbow);
  SSCSerial.print(" #13 P");
  SSCSerial.print(Wrist);
#ifndef FSRG // force sensor
  SSCSerial.print(" #14 P");
  SSCSerial.print(g);
#endif // wrist rotate
  SSCSerial.print(" #15 P");
  SSCSerial.print(wr);
  SSCSerial.println();
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

void Arm_mode()
{
  int LSY = 128 - ps2x.Analog(PSS_LY); // reading analog values from controller
  int LSX = ps2x.Analog(PSS_LX) - 128;
  int RSY = 128 - ps2x.Analog(PSS_RY);
  int RSX = ps2x.Analog(PSS_RX) - 128;
  
  if(RSY > Deadzone || RSY < -Deadzone)
    tmpy = max(Y + RSY/1000.0*Arm_Speed, -1);
  
  if(RSX > Deadzone || RSX < -Deadzone)
    tmpx = max(X + RSX/1000.0*Arm_Speed, -0.5);
    
  if(LSY > Deadzone || LSY < -Deadzone)
    tmpwa = constrain(WA + LSY/100.0*Arm_Speed, 0, 180);
 
  if(LSX > Deadzone || LSX < -Deadzone)
    tmpz = constrain(Z + LSX/10.0*Arm_Speed, 500, 2500);
 
  if(ps2x.Button(PSB_R1))
  {
    #ifdef FSRG // if force sensor is used
    int gPos;
    int reading;
    SSCSerial.println("QP 14");
    while(SSCSerial.available() == 0)
      delay(1);
    gPos = SSCSerial.read() * 10;
    SSCSerial.println("VC");
    while(SSCSerial.available() == 0)
      delay(1);
    reading = SSCSerial.read();
    while(reading < 50 && gPos < 2400)
    {
      gPos += 10;
      SSCSerial.print("#14 P");
      SSCSerial.println(gPos);
      SSCSerial.println("VC");
      while(SSCSerial.available() == 0)
        delay(1);
      reading = SSCSerial.read()
    }
    #else
    tmpg = constrain(G + 20*Arm_Speed, 500, 2500);
    #endif
  }
  if(ps2x.Button(PSB_R2))
  {
    #ifdef FSRG
    int gPos;
    SSCSerial.println("QP 14");
    while(SSCSerial.available() == 0)
      delay(1);
    gPos = SSCSerial.read() * 10;
    while(gPos > 1500)
    {
      SSCSerial.print("#14 P");
      SSCSerial.println(gPos);
      gPos -= 50;
    }
    #else
    tmpg = constrain(G - 20*Arm_Speed, 1500, 2400);
    #endif
  }
 
  if(ps2x.Button(PSB_L1))
    tmpwr = max(WR + 20*Arm_Speed, 500);
  else if(ps2x.Button(PSB_L2))
    tmpwr = min(WR - 20*Arm_Speed, 2500);
 
 
  if(ps2x.ButtonPressed(PSB_PAD_UP))
  {
    Arm_sps = min(Arm_sps + 1, 5);
    tone(5, Arm_sps*200, 200);
  }
  else if(ps2x.ButtonPressed(PSB_PAD_DOWN))
  {
    Arm_sps = max(Arm_sps - 1, 1);
    tone(5, Arm_sps*200, 200);
  }
  
  Arm_Speed = Arm_sps*0.20 + 0.60;
      
 if(Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr))
   {
     #ifdef DEBUG
     DBGSerial.print("NONREAL Answer");
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
 
}


void loop()
{
  ps2x.read_gamepad(); //update the ps2 controller
  Arm_mode();  
  delay(30);
}
