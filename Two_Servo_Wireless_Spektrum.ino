/*
Input: PWM Inputs from Orange RC Receiver 
by controlling joysticks from Spektrum RC Radio
Output: 2 Servo Motors

Code Written by: TAK'S JOSEPH REFUGIO
Code Written on: Fall 2017
Code Written for: Chicago Engineering Design Team - EDT.Stella
*/
#include<Servo.h>

Servo myServo;
Servo myServo_2;

int const potPin = 11;
int potVal;
int angle;
int servoPin = 6;
int arduinoDelay = 1;

int const potPin_2 = 11;
int potVal_2;
int angle_2;
int servoPin_2 = 6;

void setup() {

  /* Recognizing attached servo */
  myServo.attach(servoPin); 
  myServo_2.attach(servoPin_2);
  

  /* Taking in data from analogRead at 9600 bits per second */
  Serial.begin(9600); 
}

void loop() {
  /* Reading in voltage value for potentionmeter pin */
  /* Range is from 0-1023 */
  potVal = pulseIn(potPin,HIGH);

  /* Printing PotVal Value */
  Serial.print("potVal: ");
  Serial.print(potVal);

  /* Scales values of potVal from 0-1023 to 0-179 */
  if ((potVal>1450)&&(potVal<1482)) {angle == 90;}      // For fixing servo jitter when equilibrium
  else angle = map(potVal, 1886, 1068, 0, 180);

  /* Printing angle of servo */
  Serial.print("\tangle: ");
  Serial.print(myServo.read());
  //Serial.print(angle);
  Serial.print("\n");

  /* Write the angle value to the Servo */
  /* Tells how much the Servo should rotate */
  myServo.write(angle);


  potVal_2 = pulseIn(potPin_2, HIGH);
  if ((potVal_2>1450)&&(potVal_2<1482)) {angle_2 == 90;}      // For fixing servo jitter when equilibrium
  else angle_2 = map(potVal_2, 1886, 1068, 0, 180);
  myServo_2.write(angle_2);



  
  delay(arduinoDelay);  


}
