/*
Input: Orange RX Receiver from Wireless Spektrum Radio
Output: Servo Motors
Code Written By: TAK'S JOSEPH REFUGIO
Code Written On: Fall 2017
Code Written for: Chicago Engineering Design Team - EDT.Stella
*/
#include <._PWM.h>
#include <PWM.h>
#define BASE 9
#define ROD 10
#define IN1 A0
#define IN2 A1
#define THRESHOLD 25
#define MIN_RC_MAP 107
#define MAX_RC_MAP 188
#define THROTTLE_MIN 6
#define THROTTLE_MAX 30
#define RESOLUTION 100
#define BITWISE_STEPSIZE 50
#define BITWISE_MAX_ANGLE 4739
#define BITWISE_MIN_ANGLE 1600

int rod_pos = 6;

void setup(){

  InitTimersSafe();
  pinMode(IN1,INPUT);
  pinMode(IN2,INPUT);
  SetPinFrequencySafe(BASE,(int32_t)50);
  // Serial.begin(9600);
}

void loop(){
  int rc_in1 = pulseIn(IN1,HIGH)/10;
  int rc_in2 = pulseIn(IN2,HIGH)/10;

  int base_value = map(rc_in1,MIN_RC_MAP,MAX_RC_MAP,THROTTLE_MIN,THROTTLE_MAX);
  int rod_value = map(rc_in2,MIN_RC_MAP,MAX_RC_MAP,-RESOLUTION,RESOLUTION);
  if(rod_value < -THRESHOLD){
    rod_pos = rod_pos - BITWISE_STEPSIZE;
  }
  if(rod_value > THRESHOLD){
    rod_pos = rod_pos + BITWISE_STEPSIZE;
  }
  if(rod_pos > BITWISE_MAX_ANGLE){
    rod_pos = BITWISE_MAX_ANGLE;
  }
  if(rod_pos < BITWISE_MIN_ANGLE){
    rod_pos = BITWISE_MIN_ANGLE;
  }
  pwmWrite(BASE,base_value);
  pwmWriteHR(ROD,rod_pos);
}

