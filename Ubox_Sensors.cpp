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
uint8_t Ubox_Sensors::lightness() { return _lightness; };

void Ubox_Sensors::run() {
  if (_ultrasonic_state) {
    readUltrasonic();
  }

  if (_ldr_state) {
    readLDR();
  }
}

long Ubox_Sensors::readUltrasonic() {
  _distance = _ultrasonic->ping_cm();
  return _distance;
}

uint8_t Ubox_Sensors::readLDR() {
  _lightness = analogRead(_pin_ldr);
  return _lightness;
}