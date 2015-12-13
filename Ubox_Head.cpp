#include "Ubox_Head.h"

// -----
// PUBLIC METHODS
// -----

Ubox_Head::Ubox_Head(uint8_t pin_servo_head, unsigned long interval) {
  Ubox_Base::setInterval(interval);
  _pin_servo_head = pin_servo_head;
}

void Ubox_Head::run() {
  if (_action != _last_action) {
    uint8_t position;
    _last_action = _action;

    switch (_action) {
      case CENTER:
        position = 90;
      break;
      case RIGHT:
        position = map(_pos_servo_head, 0, 100, 1, 90);
      break;
      case LEFT:
        position = map(_pos_servo_head, 0, 100, 178, 90);
      break;
    }

    // Write position to head servo
    _servoHead.attach(_pin_servo_head);
    _servoHead.write(position);
    delay(500);
    _servoHead.detach();
  }
}

void Ubox_Head::center() {
  setAction(CENTER);
}

void Ubox_Head::right(uint8_t position, bool force) {
  setAction(RIGHT);
  setPosition(position);

  if (force) {
    _last_action = NONE;
  }

  Serial.print("Right: ");
  Serial.println(position);
}

void Ubox_Head::left(uint8_t position, bool force) {
  setAction(LEFT);
  setPosition(position);

  if (force) {
    _last_action = NONE;
  }

  Serial.print("Left: ");
  Serial.println(position);
}

ActionHead Ubox_Head::action() {
  return _action;
}

// -----
// PRIVATE METHODS
// -----

void Ubox_Head::setAction(ActionHead action) {
  _action = action;
}

void Ubox_Head::setPosition(uint8_t position) {
  if (position <= 100)
    _pos_servo_head = position;
  else
    _pos_servo_head = 100;
}