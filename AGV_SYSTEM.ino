//AGV Coding, when the switch is ON, the relay will instruct the DC Motor to move.
//The IR Sensor (Left and right side of AGV) will sense the black tape, to give the instruction to the servo to turn (LEFT/RIGHT).
//When both of the Sensor sense the black tape, it will stop.

#include <Servo.h>

//Pin connection
const int RS = A0;      
const int RS2 = A1;
const int LS = A2;  
const int LS2 = A3;
const int relay = 8;

// value read from the pot
int sensorValueRS = 0;        
int sensorValueLS = 0;        
int sensorValueRS2 = 0;       
int sensorValueLS2 = 0;

// value output to the PWM (analog out)
int outputValueRS;        
int outputValueLS;        
int outputValueRS2;        
int outputValueLS2;        
int servo_position;
volatile byte relaystate=HIGH;

Servo AGVservo; //servo declaration

void setup()
{
  Serial.begin(9600);
  AGVservo.attach(9); // pin that connect with the servo
  pinMode(RS,INPUT);
  pinMode(RS2,INPUT);
  pinMode(LS,INPUT);
  pinMode(LS2,INPUT);
  pinMode(relay, OUTPUT); //Set relay as an output
  digitalWrite(relay,LOW);
}

void loop() 
{
  // read the analog in value:
  sensorValueRS = analogRead(RS);
  // map it to the range of the analog out:
  sensorValueLS = analogRead(LS);
  // read the analog in value:
  sensorValueRS2 = analogRead(RS2);
  // map it to the range of the analog out:
  sensorValueLS2 = analogRead(LS2);
  // map it to the range of the analog out:
  outputValueRS = map(sensorValueRS, 0, 1023, 0, 255);
  // map it to the range of the analog out:
  outputValueLS = map(sensorValueLS, 0, 1023, 0, 255);
   // map it to the range of the analog out:
  outputValueRS2 = map(sensorValueRS2, 0, 1023, 0, 255);
  // map it to the range of the analog out:
  outputValueLS2 = map(sensorValueLS2, 0, 1023, 0, 255);
  

  //Move straight if both detect white
  if (outputValueRS<100&&outputValueLS<100&&outputValueRS2<100)
  {
    delay(10);
    servo_position=90;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;  
  }

  
  //Move LEFT when LS detect black
  else if (outputValueRS<100&&outputValueRS2<100&&outputValueLS>100&&outputValueLS2>100)
  {
    delay(10);
    servo_position=135;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }
  else if (outputValueRS<100&&outputValueRS2<100&&outputValueLS<100&&outputValueLS2>100)
  {
    delay(10);
    servo_position=135;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }
  else if (outputValueRS<100&&outputValueRS2<100&&outputValueLS>100&&outputValueLS2<100)
  {
    delay(10);
    servo_position=135;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }

  
  //Move RIGHT when RS detect black
  else if (outputValueRS<100&&outputValueRS2>100&&outputValueLS<100&&outputValueLS2<100)
  {
    delay(10);
    servo_position=45;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }
  else if (outputValueRS>100&&outputValueRS2<100&&outputValueLS<100&&outputValueLS2<100)
  {
    delay(10);
    servo_position=45;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }
  else if (outputValueRS>100&&outputValueRS2>100&&outputValueLS<100&&outputValueLS2<100)
  {
    delay(10);
    servo_position=45;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }

  
  //If both have error(both over 100),STOP
  else if (outputValueRS>100&&outputValueRS>100&&outputValueLS>100&&outputValueLS2>100)
  {
    delay(10);
    servo_position=90;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,HIGH); //Motor STOP
    relaystate=HIGH;
  }

  //In case any error happen
  else
  {
    delay(10);
    servo_position=90;
    AGVservo.write(servo_position);
    delay(10);
    digitalWrite(relay,LOW); //Motor runs
    relaystate=LOW;
  }

  //print the results to the serial monitor:
  //Above 100 the sensor detect black
  Serial.print("\nsensor Right= ");
  Serial.print(outputValueRS);
  Serial.print("\tsensor Right2= ");
  Serial.print(outputValueRS2);
  Serial.print("\tsensor Left= ");
  Serial.print(outputValueLS);
  Serial.print("\tsensor Left2= ");
  Serial.print(outputValueLS2);
  //RIGHT=45 LEFT=135 STRAIGHT=90
  Serial.print("\tServo Position= "); 
  Serial.print(servo_position);
  //LOW=0=ON HIGH=1=OFF (Due to some problem, the ON OFF switch its value)
  Serial.print("\tMotor= "); 
  Serial.print(relaystate);
  
}

//End of code
//Credit to NUR AZIELA SUHAIMI Rev. 1.0
