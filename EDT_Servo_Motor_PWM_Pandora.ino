/*
This code takes a PWM input from a radio receiver named Orange DRX 
then converts the PWM signal to discrete angle values for output to 
a  5V servo motor. 

Code Written By:TAK'S JOSEPH REFUGIO
Code Written For: Chicago Engineering Design Team - Pandora Robot
Code Written On: Spring 2017
*/

#include<Servo.h>

int servo1SigPin = 13;           /* Assigns the pin connected to the DRX specifically for Servo 1 */
int servo2SigPin = 11;         /* Assigns the pin connected to the DRX specifically for Servo 2 */

int servo1Pin = 12;              /* Assigns the pin conneted to servo motor 1 */
int servo2Pin = 10;            /* Assigns the pin connected to servo motor 2 */


double drxVal_servo1 = 0;       /* Stores the value read in from the DRX */
double drxVal_servo2 = 0;     /* Stores the value read in from the DRX */

double angle_servo1 = 0;        /* Stores the angle value for servo 1 (Range: 0-150 degrees) depending on the value read in from the DRX */
double angle_servo2 = 0;         /* Stores the angle value for servo 2 (Range: 0-150 degrees) depending on the value read in from the DRX */

Servo servo1;                   /* Variable name for the first servo */  
Servo servo2;                   /* Variable name for the second servo */

double angleThreshold = 1.5;    /* Determines how fast the servo moves */ 
int angleSensitivity = 300;      /* Determines how quickly the servo reacts to human commands */
int maxAngle = 180;             /* Sets the maximum angle that a servo can turn */

int throttlePin = 8;            /* Assigns the pin connected to the throttle */
int ledPin1 = 9;                /* For white LED */
int ledPin2 = 6;                /* For green LED */
int ledPin3 = 5;                /* For red LED */
int ledPin4 = 3;                /* For blue LED */

void setup() {
  servo1.attach(servo1Pin);         /* Assigns the pin attached to servo 1 */
  servo2.attach(servo2Pin);         /* Assigns the pin attached to servo 2 */
  pinMode(servo1SigPin,INPUT);      /* Tells Arduino that the DRX signal pin for servo 1 is an input pin */
  pinMode(servo2SigPin,INPUT);      /* Tells Arduino that the DRX signal pin for servo 2 is an input pin */

  /* Tells Arduino that the LEDs are output devices */
  pinMode(ledPin1,OUTPUT);  
  pinMode(ledPin2,OUTPUT);
  pinMode(ledPin3,OUTPUT);
  pinMode(ledPin4,OUTPUT);
  Serial.begin(9600);               /* For printing to the Serial Monitor */
}

void loop() {
  /* Reading in the pulse HIGH duration from the DRX pin and stores it in drxVal */ 
  /* Maximum value is 1487, that's why we negate it so the normal is 0 */
  drxVal_servo1 = ((double)pulseIn(servo1SigPin,HIGH) - 1487);
  drxVal_servo2 = ((double)pulseIn(servo2SigPin,HIGH) - 1487);
  
  angleReturn(drxVal_servo1,maxAngle,&angle_servo1);
  angleReturn(drxVal_servo2,maxAngle,&angle_servo2);
 
  servo1.write(angle_servo1);      /* Instructing Arduino to turn servo 1 to a certain angle */  
  servo2.write(angle_servo2);      /* Instructing Arduino to turn servo 2 to a certain angle */  

  /* Printing values to the Serial Monitor */
  Serial.println("Servo1_angle:");
  Serial.print(angle_servo1);       
  Serial.print("\t");
  Serial.println("Servo2_angle: ");
  Serial.print(angle_servo2);
  Serial.println("\n");  

  int throttleValue = (double)pulseIn(throttlePin,HIGH);      /* Reads the HIGH time duration of the throttle */
  int ledBrightness = map(throttleValue,1088,1898,0,255);     /* Scales the throttleValues to go from 0 to 255 */
  
  /* Instructs Arduino to send current of a particular value to the LEDs */
  analogWrite(ledPin1,ledBrightness);               
  analogWrite(ledPin2,ledBrightness);
  analogWrite(ledPin3,ledBrightness);
  analogWrite(ledPin4,ledBrightness);
}


/* For figuring out the angle associated with a DRX Value for any servos*/
void angleReturn (double drxVal, int maxAngle, double *angle)
{
  /* 50 is the sensitivity of a servo motor */ 
  if(drxVal > angleSensitivity ){                  /* If we throttle up, position value keeps going up until we hit upper limit (implied) */
      (*angle)= *angle + angleThreshold ;
      }
  else if (drxVal < -angleSensitivity){            /* If we throttle down, position value keeps going down until we hit lower limit (implied) */
      (*angle) = *angle - angleThreshold;
      }
  
  if(*angle < 0 ){                    /* If for some reason servo angle is negative, we correct that to zero. */      
      *angle = 0;
      }
   else if (*angle > maxAngle){        /* If for some reason servo angle is positive, we correct that to max angle */
      *angle = maxAngle;
   }
}

