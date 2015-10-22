#include <Arduino.h>
#include "Ubox_Engines.h"

// -----
// PUBLIC METHODS
// -----
//Ubox_Engines::Ubox_Engines(uint8_t m1_pin1, uint8_t m1_pin2,
//	uint8_t m2_pin1, uint8_t m2_pin2,
//	uint8_t m1_pin_enable, uint8_t m2_pin_enable)
Ubox_Engines::Ubox_Engines(uint8_t *motor1, uint8_t *motor2) {
  // set mapped motor poles to Arduino pins (via L293D)
	_motor1 = motor1;
	_motor2 = motor2;

  for (int x = 0; x < 3; x++) {
		pinMode(_motor1[x], OUTPUT);
  	pinMode(_motor2[x], OUTPUT);
  }
}

void Ubox_Engines::setSpeed(int speed) {
	if (speed > MAX_SPEED)
		_speed = MAX_SPEED; // limit top speed
	else if (speed < MIN_SPEED)
		_speed = MIN_SPEED; // keep motor above 0
	else
		_speed = speed;
}

void Ubox_Engines::process() {
	if (_action != _last_action) {
		// Turn off engines
		motorStop(_motor1);
		motorStop(_motor2);

		switch (_action) {
			case STOP:
				motorStop(_motor1);
				motorStop(_motor2);
				break;
			case FORWARD:
				motorForward(_motor1);
				motorForward(_motor2);
				break;
			case BACKWARD:
				motorBackward(_motor1);
				motorBackward(_motor2);
				break;
			case RIGHT:
				motorForward(_motor1);
				motorBackward(_motor2);
				break;
			case LEFT:
				motorBackward(_motor1);
				motorForward(_motor2);
				break;
		}
	}

	_last_action = _action;
}

void Ubox_Engines::stop() {
	setAction(STOP);
}

void Ubox_Engines::forward() {
	setAction(FORWARD);
}

void Ubox_Engines::backward() {
	setAction(BACKWARD);
}

void Ubox_Engines::right() {
	setAction(RIGHT);
}

void Ubox_Engines::left() {
	setAction(LEFT);
}

Action Ubox_Engines::action() {
	return _action;
}

// -----
// PRIVATE METHODS
// -----

void Ubox_Engines::setAction(Action action) {
	_action = action;
}

void Ubox_Engines::motorStop(uint8_t *motor) {
	digitalWrite(motor[0], LOW);
	digitalWrite(motor[1], LOW);
	digitalWrite(motor[2], LOW);
}

void Ubox_Engines::motorForward(uint8_t *motor) {
	digitalWrite(motor[0], LOW);
	digitalWrite(motor[1], HIGH);
	digitalWrite(motor[2], _speed);
}

void Ubox_Engines::motorBackward(uint8_t *motor) {
	digitalWrite(motor[0], HIGH);
	digitalWrite(motor[1], LOW);
	digitalWrite(motor[2], _speed);	
}