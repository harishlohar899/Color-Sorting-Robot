#include <Wire.h>
#include "Adafruit_TCS34725.h" 
#include <Servo.h>
#include <AFMotor.h> 
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
#define IR1 A3
#define IR2 A2
int var1;
int var2;
Servo myservo1; 
int color=0;
unsigned char intersection = 0;
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
 
 void setup() 
 {
Serial.begin(115200);
myservo1.attach(10);  
pinMode(IR1,INPUT);
pinMode(IR2,INPUT);
myservo1.write(50);
delay(2000);
motor1.setSpeed(255);
motor2.setSpeed(255);
motor3.setSpeed(255);
motor4.setSpeed(255);
if (tcs.begin()) 
{
Serial.println("Found sensor");
} 
else 
{
Serial.println("No TCS34725 found ... check your connections");
while (1);
}

// Now we're ready to get readings!
}

void(* resetFunc) (void) = 0;

void loop() 
{
  //Read_colour();
 mission();
}

void ir()
{
  var1=analogRead(IR1);
  var2=analogRead(IR2);
  Serial.print("IR1=");
  Serial.print(var1);
  Serial.print("  ");
  Serial.print("IR2=");
  Serial.println(var2);
}

void Run()
{
 ir();
if(var1>50 & var2>50)
 {
  Forward(); 
 }
 if(var1>50 & var2<50)
 {
  TurnRight(); 
 }
 if(var1<50 & var2>50)
 {
  TurnLeft(); 
 }
}

int Read_colour()
{
  uint16_t r, g, b, c, colorTemp, lux;
tcs.getRawData(&r, &g, &b, &c);
colorTemp = tcs.calculateColorTemperature(r, g, b);
lux = tcs.calculateLux(r, g, b);
Serial.print("Color Temp: "); 
Serial.print(colorTemp, DEC); 
Serial.print(" K - ");
Serial.print("Lux: "); 
Serial.print(lux, DEC); 
Serial.print(" - ");
Serial.print("R: "); 
Serial.print(r, DEC);
Serial.print(" ");
Serial.print("G: "); 
Serial.print(g, DEC); 
Serial.print(" ");
Serial.print("B: "); 
Serial.print(b, DEC); 
Serial.print(" ");
Serial.print("C: "); 
Serial.print(c, DEC); 
Serial.print(" ");
Serial.println(" ");
 if(r<1900 & r>800 & g<810 & g>400){
    Serial.println(" Red !\n");
    color = 1; //Red
  }
  if(r<600 & r>250 & g<1100 & g>500 ){
    Serial.println(" Green !\n");
    color = 2; //Green
  }
  if(g<3000 & g>1200 & b<4000 & b>1500){
    Serial.println(" Blue !\n");
    color = 3; //Blue
  }  
    return color;  
}

void mission()
{
 Run(); 
if(var1<50 & var2<50)
 {
 Stop();
 color=Read_colour();

  switch(color)
  {
    case 1: //Turn Left 
      red();
      break;
      
    case 2: //Turn Left 
      green();
      break;

     case 3: //Turn Right
      blue();
      break; 

    case 0:
      Stop();
      break;  
    }
  }    
}

void red()
{
  intersection++;
  if(intersection == 1)
  { 
   Serial.print("Intersection=");
   Serial.println(intersection);  
   myservo1.write(50);
   delay(2000);
    TurnBack();
  }
     if(intersection == 2)
    {
      Serial.print("Intersection=");
      Serial.println(intersection); 
      Forward(); 
      delay(400);
      TurnRight();
      delay(1600);
      Forward();  
      delay(500); 
      }
    else if(intersection == 3)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
     Stop();
    myservo1.write(90);
   delay(2000);
    myservo1.write(50);// for open the gripper
    delay(1000);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(3000); 
  Forward();
  delay(400);
      }
    else if(intersection == 4)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
      Forward(); 
      delay(400);
      TurnLeft();
      delay(1600);
      Forward(); 
      delay(400); 
      }
    else if(intersection == 5)
    { 
   Serial.print("Intersection=");
   Serial.println(intersection); 
      resetFunc(); 
    }  
}

void green()
{
  intersection++;
  if(intersection == 1)
  { 
   Serial.print("Intersection=");
   Serial.println(intersection); 
   myservo1.write(50);
   delay(2000); 
   TurnBack();
  }
     if(intersection == 2)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
      Forward(); 
      delay(1000);
      }
    else if(intersection == 3)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
     Stop();
     delay(1000);
     myservo1.write(90);
     delay(2000);
     myservo1.write(50);// for open the gripper
     delay(1300);
      TurnBack();
      }
    else if(intersection == 4)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
      Forward();
      delay(1000);    
      }
    else if(intersection == 5)
    { 
   Serial.print("Intersection=");
   Serial.println(intersection); 
      resetFunc(); 
    }  
}

void blue()
{
  intersection++;
  if(intersection == 1)
  { 
   Serial.print("Intersection=");
   Serial.println(intersection);  
   myservo1.write(50);
   delay(2000); 
   TurnBack();
  }
     if(intersection == 2)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
      Forward(); 
      delay(300);
     TurnLeft(); 
      delay(1800);
      Forward(); 
      delay(400);
      }
    else if(intersection == 3)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
     Stop();
     delay(1000);
     myservo1.write(90);
     delay(2000);
     myservo1.write(50);// for open the gripper
     delay(1000);
      TurnBack();
      }
    else if(intersection == 4)
    {
   Serial.print("Intersection=");
   Serial.println(intersection); 
      Forward(); 
      delay(400);
      TurnRight();
      delay(1600);
      Forward(); 
      delay(400);    
      }
    else if(intersection == 5)
    { 
   Serial.print("Intersection=");
   Serial.println(intersection); 
      resetFunc(); 
    }  
}


void Forward() 
{ 
  Serial.println("Farward");
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void Backward() 
{
  Serial.println("Backward");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}  

void TurnRight() 
{
  Serial.println("Turn right");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
} 
 
void TurnLeft() 
{
 Serial.println("Turn left");
 motor1.run(FORWARD);
 motor2.run(FORWARD);
 motor3.run(BACKWARD);
 motor4.run(BACKWARD);
}  
void TurnLeft_back()
{
 Serial.println("Turn left");
 motor1.run(FORWARD);
 motor2.run(FORWARD);
 motor3.run(BACKWARD);
 motor4.run(BACKWARD);
}  
void TurnBack()
{
  Serial.println("TurnBack");
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  delay(3000); 
  Forward();
  delay(300);
}
void Stop()
{
 Serial.println("Stop");
 motor1.run(RELEASE);
 motor2.run(RELEASE);
 motor3.run(RELEASE);
 motor4.run(RELEASE);
}
