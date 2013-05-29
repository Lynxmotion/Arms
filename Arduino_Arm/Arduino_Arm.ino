    #include <Servo.h>
    #include <PS2X_lib.h>

  #define SOUND_PIN    5        // Botboarduino JR pin number
  #define PS2_DAT      6        
  #define PS2_CMD      7
  #define PS2_SEL      8
  #define PS2_CLK      9

    PS2X ps2x;
    int error = 0;
    byte type = 0;

    #define Deadzone 10

    char ArmSize = 'D'; // Must be 'A', 'B', or 'D'  DO NOT REMOVE THE SEMICOLON OR THE ' '
    float A;
    float B;
    float rtod = 57.295779;

    float Speed = 1.0;
    int sps = 3;

    Servo Elb;
    Servo Shldr;
    Servo Wrist;
    Servo Base;
    Servo WristR;
    Servo Gripper;

    float X = 4;
    float Y = 4;
    int Z = 90;
    int G = 90;
    int WR = 90;
    float WA = 0;

    float tmpx = 4;
    float tmpy = 4;
    int tmpz = 90;
    int tmpg = 90;
    int tmpwr = 90;
    float tmpwa = 0;

    void setup()
    {
      Serial.begin(57600);

      error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT);  // Setup gamepad (clock, command, attention, data) pins

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
    Base.attach(2);
    Shldr.attach(3);
    Elb.attach(4);
    Wrist.attach(10);
    Gripper.attach(11);
    WristR.attach(12);

    switch(ArmSize)
    {
      case 'A':
      A = 3.75;
      B = 4.25;
      break;
      case 'B':
      A = 4.75;
      B = 5.00;
      break;
      case 'D':
      A = 5.75;
      B = 7.375;
      break;
    }
    }

    int Arm(float x, float y, float z, int g, float wa, int wr) //Here's all the Inverse Kinematics to control the arm
    {
      float M = sqrt((y*y)+(x*x));
      if(M <= 0)
        return 1;
      float A1 = atan(y/x);
      float A2 = acos((A*A-B*B+M*M)/((A*2)*M));
      float Elbow = acos((A*A+B*B-M*M)/((A*2)*B));
      float Shoulder = A1 + A2;
      Elbow = Elbow * rtod;
      Shoulder = Shoulder * rtod;
      while((int)Elbow <= 0 || (int)Shoulder <= 0)
        return 1;
      float Wris = abs(wa - Elbow - Shoulder) - 90;
      Elb.write(180 - Elbow);
      Shldr.write(Shoulder);
      Wrist.write(180 - Wris);
      Base.write(z);
      WristR.write(wr);
      Gripper.write(g);
      Y = tmpy;
      X = tmpx;
      Z = tmpz;
      WA = tmpwa;
      G = tmpg;
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
        tmpy = Y + RSY/1000.0*Speed;
      if(tmpy < -1)
        tmpy = -1;
     
      if(RSX > Deadzone || RSX < -Deadzone)
        tmpx = X + RSX/1000.0*Speed;
      if(tmpx < -0.5)
        tmpx = -0.5;
       
      if(LSY > Deadzone || LSY < -Deadzone)
        tmpwa = WA + LSY/100.0*Speed;
      if(tmpwa > 180)
        tmpwa = 180;
      else if(tmpwa < 0)
        tmpwa = 0;

      if(LSX > Deadzone || LSX < -Deadzone)
        tmpz = Z + LSX/100.0*Speed;
      if(tmpz > 180)
        tmpz = 180;
      else if(tmpz < 0)
        tmpz = 0;

      if(ps2x.Button(PSB_R1))
        tmpg = G + 5*Speed;
      if(ps2x.Button(PSB_R2))
        tmpg = G - 5*Speed;
      if(tmpg > 180)
        tmpg = 180;
      else if(tmpg < 50)
        tmpg = 50;

      if(ps2x.Button(PSB_L1))
        tmpwr = WR + 2*Speed;
      else if(ps2x.Button(PSB_L2))
        tmpwr = WR - 2*Speed;
      if(tmpwr > 180)
        tmpwr = 180;
      if(tmpwr < 0)
        tmpwr = 0;


      if(ps2x.ButtonPressed(PSB_PAD_UP))
      {
        sps = sps + 1;
        if(sps > 5)
          sps = 5;
        tone(5, sps*500, 200);
      }
      else if(ps2x.ButtonPressed(PSB_PAD_DOWN))
      {
        sps = sps - 1;
        if(sps < 1)
          sps = 1;
        tone(5, sps*500, 200);
      }
     
      Speed = sps*0.20 + 0.60;
         
    if(Arm(tmpx, tmpy, tmpz, tmpg, tmpwa, tmpwr))
       {
         Serial.print("ERROR");
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


