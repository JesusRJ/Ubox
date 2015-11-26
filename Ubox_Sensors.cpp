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
long Ubox_Sensors::distance() { return _distance; };
int Ubox_Sensors::lightness() { return _lightness; };

void Ubox_Sensors::run() {
  readUltrasonic();
  readLDR();

  String value;

  if (_ultrasonic_state) {
    value = "D: " + String(_distance) + "  ";
  }
  if (_ldr_state) {
    value += "L: " + String(_lightness);
  }

  _onDisplay(value);
}

void Ubox_Sensors::readUltrasonic() {
  _distance = -1;

  if (_ultrasonic_state) {
    _distance = _ultrasonic->ping_cm();
  }
}

void Ubox_Sensors::readLDR() {
  _lightness = -1;

  if (_ldr_state) {
    _lightness = analogRead(_pin_ldr);
  }
}