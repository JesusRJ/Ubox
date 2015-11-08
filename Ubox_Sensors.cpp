#include "Ubox_Sensors.h"

// -----
// PUBLIC METHODS
// -----

Ubox_Sensors::Ubox_Sensors(NewPing *ultrasonic, uint8_t pin_ldr, unsigned long interval) {
  Ubox_Base::setInterval(interval);
  
  _ultrasonic = ultrasonic;
  _pin_ldr = pin_ldr;

  pinMode(_pin_ldr, INPUT);
}

void Ubox_Sensors::setUltrasonicState(SensorState state) { _ultrasonic_state = state; }
void Ubox_Sensors::setLDRState(SensorState state) { _ldr_state = state; }
int Ubox_Sensors::lightness() { return _lightness; };
long Ubox_Sensors::distance() { return _distance; };

void Ubox_Sensors::run() {
  _distance = -1;
  _lightness = -1;
  String value;

  if (_ultrasonic_state) {
    _distance = _ultrasonic->ping_cm();
    value = "D: " + String(_distance) + "     ";
  }
  if (_ldr_state) {
    _lightness = analogRead(_pin_ldr);
    value += "L:" + String(_lightness);
  }

  _onDisplay(value);
}
