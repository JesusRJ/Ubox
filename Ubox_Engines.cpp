#include "Ubox_Engines.h"

// -----
// PUBLIC METHODS
// -----

Ubox_Engines::Ubox_Engines(uint8_t *motor1, uint8_t *motor2, uint8_t interval) {
  Ubox_Time::setInterval(interval);

  // set mapped motor poles to Arduino pins (via L293D)
  _motor1 = motor1;
  _motor2 = motor2;

  for (uint8_t x = 0; x < 3; x++) {
    pinMode(_motor1[x], OUTPUT);
    pinMode(_motor2[x], OUTPUT);
  }
}

void Ubox_Engines::setSpeed(uint8_t speed) {
  if (speed > MAX_SPEED)
    _speed = MAX_SPEED; // limit top speed
  else if (speed < MIN_SPEED)
    _speed = MIN_SPEED; // keep motor above 0
  else
    _speed = speed;
}

void Ubox_Engines::run() {
  if (_action != _last_action) {
    // Turn off engines
    motorStop(_motor1);
    motorStop(_motor2);

    switch (_action) {
      case STOP:
        motorStop(_motor1);
        motorStop(_motor2);
      break;
      case GO_FORWARD:
        motorForward(_motor1);
        motorForward(_motor2);
      break;
      case GO_BACKWARD:
        motorBackward(_motor1);
        motorBackward(_motor2);
      break;
      case GO_RIGHT:
        motorForward(_motor1);
        motorBackward(_motor2);
      break;
      case GO_LEFT:
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
  setAction(GO_FORWARD);
}

void Ubox_Engines::backward() {
  setAction(GO_BACKWARD);
}

void Ubox_Engines::right() {
  setAction(GO_RIGHT);
}

void Ubox_Engines::left() {
  setAction(GO_LEFT);
}

ActionEngine Ubox_Engines::action() {
  return _action;
}

// -----
// PRIVATE METHODS
// -----

void Ubox_Engines::setAction(ActionEngine action) {
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