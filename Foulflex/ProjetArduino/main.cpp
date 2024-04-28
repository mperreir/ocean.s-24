#include <Arduino.h>


#define dirPin 2
#define stepPin 3
#define enablePin 4 // low to active
#define stepsPerRevolution 200

char buffer[16];
int len = 0;


// This function make the stepper motor rotate
// @param nb: number of rotations
void rotate(int nb=1, int delayTime=500) {
	for (int i = 0; i < stepsPerRevolution*nb; i++) {
		digitalWrite(stepPin, HIGH);
		delayMicroseconds(delayTime);
		digitalWrite(stepPin, LOW);
		delayMicroseconds(delayTime);
	}
}

// This function make one cycle for the blade
// @param dir: direction of rotation
void oneCycle(bool dir){
	digitalWrite(dirPin, dir);
	rotate(850);

	digitalWrite(dirPin, !dir);
	rotate(850);
}

void setup() {
	pinMode(stepPin, OUTPUT);
	pinMode(dirPin, OUTPUT);
	pinMode(enablePin, OUTPUT);

	digitalWrite(enablePin, HIGH);

	Serial.begin(9600);
}


void loop() {
	if(Serial.available() > 0){
		len = Serial.readBytes(buffer, 16);
		buffer[len] = 0;
		if(buffer[0] == '1') oneCycle(HIGH);
	}
}