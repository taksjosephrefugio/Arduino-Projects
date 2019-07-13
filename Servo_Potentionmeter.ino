/*
Using a breadboard potentiometer as 
control input for a 5V servo

Code Written by: TAK'S JOSEPH REFUGIO
Code Written on: Fall  2017
Code Written for: Chicago Engineering Design Team - EDT.Stella
*/

#include<Servo.h>

Servo myServo;

int const potPin = A0;
int potVal;
int angle;
int servoPin = 9;
int arduinoDelay = 1;

void setup() {
  /* Recognizing attached servo */
  myServo.attach(servoPin); 

  /* Taking in data from analogRead at 9600 bits per second */
  Serial.begin(9600); 
}

void loop() {
  /* Reading in voltage value for potentionmeter pin */
  /* Range is from 0-1023 */
  potVal = analogRead(potPin);

  /* Printing PotVal Value */
  Serial.print("potVal: ");
  Serial.print(potVal);

  /* Scales values of potVal from 0-1023 to 0-179 */
  angle = map(potVal, 0, 1023, 0, 179);

  /* Printing angle of servo */
  Serial.print("\tangle: ");
  Serial.print(myServo.read());
  //Serial.print(angle);
  Serial.print("\n");

  /* Write the angle value to the Servo */
  /* Tells how much the Servo should rotate */
  myServo.write(angle);
  delay(arduinoDelay);  
}
