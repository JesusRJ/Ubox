#include "Ubox_Head.h"

// -----
// PUBLIC METHODS
// -----

Ubox_Head::Ubox_Head(uint8_t pin_servo_head, uint8_t interval) {
  Ubox_Time::setInterval(interval);
  _servoHead.attach(pin_servo_head);
}

void Ubox_Head::setSensors(Ubox_Sensors *sensors) {
  _sensors = sensors;
}

void Ubox_Head::run() {
if (_action != _last_action) {
    switch (_action) {
      case CENTER:
        _servoHead.write(90);
      break;
      case RIGHT:
        _servoHead.write(179);
      break;
      case LEFT:
        _servoHead.write(0);
      break;
      case QUIET:
      break;
    }
  }

  _last_action = _action;
}

void Ubox_Head::center() {
  setAction(CENTER);
}

void Ubox_Head::right() {
  setAction(RIGHT);
}

void Ubox_Head::left() {
  setAction(LEFT);
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
