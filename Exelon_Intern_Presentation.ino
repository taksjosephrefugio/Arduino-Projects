/*
Input: ultrasonic sensor and giant pushbuttons
Output: 5V Relay connected to Christmas Lights

Code Written by: TAK'S JOSEPH REFUGIO
Code Written for: Exelon Corporation - Internship Presentation 2018
Code Written on: August 2018
*/


int trigPin = 9;
int echoPin = 10;
int trigger_distance = 5;

int pushbutton_pin = 2;
int pushbutton_power_pin = 3;
int pushbutton_led_pin = 4;

int relay_pin = 6;
int relay_power_pin = 7;
 
typedef enum STATUS {ON, OFF};
STATUS US_SENSOR_STATUS = OFF;
STATUS LIGHT_STATUS = OFF;
STATUS RELAY_STATUS = OFF;


void updateArmStatus() {
	long duration, distance;

  	digitalWrite(trigPin,HIGH);
  	delayMicroseconds(1000);

  	digitalWrite(trigPin, LOW);
  	duration=pulseIn(echoPin, HIGH);
	distance =(duration/2)/29.1;
  	
  	printDistance(distance);	
  	delay(10);
 
 	if(distance <= trigger_distance) {
    	US_SENSOR_STATUS = ON;
    	digitalWrite(pushbutton_led_pin, HIGH);
	}
   	else if(distance > trigger_distance) {
     	US_SENSOR_STATUS = OFF;
     	LIGHT_STATUS = OFF;
     	digitalWrite(pushbutton_led_pin, LOW);
   	}
}

void updateLightStatus() {
	int buttonstate = digitalRead(pushbutton_pin);

	if (US_SENSOR_STATUS == ON) {
		if (buttonstate == HIGH) {
			if (LIGHT_STATUS == OFF) { 
				LIGHT_STATUS = ON; 
				delay(500);
			}
			else if (LIGHT_STATUS == ON) { 
				LIGHT_STATUS = OFF; 
				delay(500);
			}
		}
	}
}

void updateRelay() {
	if (LIGHT_STATUS == ON) {
		digitalWrite(relay_pin, HIGH);
	}
	else if (LIGHT_STATUS == OFF) {
		digitalWrite(relay_pin, LOW);
	}
}

void printDistance(int distance) {
 	Serial.print(distance);
  	Serial.print("CM");
  	Serial.print("\t");
}

void setup() {
 	Serial.begin(9600); 
  	pinMode(trigPin, OUTPUT);
 	pinMode(echoPin, INPUT); 

 	pinMode(pushbutton_pin, INPUT);
 	pinMode(pushbutton_power_pin, OUTPUT);
 	pinMode(pushbutton_led_pin, OUTPUT);
 	digitalWrite(pushbutton_power_pin, HIGH);
 	digitalWrite(pushbutton_led_pin, LOW);

 	pinMode(relay_pin, OUTPUT);
 	pinMode(relay_power_pin, OUTPUT);
 	digitalWrite(relay_pin, LOW); 	
 	digitalWrite(relay_power_pin, HIGH);
}
 
void loop() {
	updateArmStatus();
	updateLightStatus();
	updateRelay();

	if (US_SENSOR_STATUS == ON) { Serial.print("US: ON\t"); }
	else if (US_SENSOR_STATUS == OFF) { Serial.print("US: OFF\t"); }

	if (LIGHT_STATUS == ON) { Serial.println("Lights: ON"); }
	else if (LIGHT_STATUS == OFF) { Serial.println("Lights: OFF"); }

	// int button = digitalRead(pushbutton_pin);
	// if (button == HIGH) {
	// 	Serial.println("Button is pressed.");
	// 	delay(2000);
	// }
	// else if (button == LOW) {
	// 	Serial.println("Button is NOT pressed.");
	// 	delay(2000);
	// }

	
}