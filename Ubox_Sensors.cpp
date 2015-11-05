#include "Ubox_Sensors.h"

// -----
// PUBLIC METHODS
// -----

Ubox_Sensors::Ubox_Sensors(NewPing *ultrasonic, uint8_t pin_ldr, uint8_t interval) {
  Ubox_Time::setInterval(interval);
  
  _ultrasonic = ultrasonic;
  _pin_ldr = pin_ldr;

  pinMode(_pin_ldr, INPUT);
}

void Ubox_Sensors::setUltrasonicState(SensorState state) { _ultrasonic_state = state; }
void Ubox_Sensors::setLDRState(SensorState state) { _ldr_state = state; }

void Ubox_Sensors::run() {
  _distance = -1;
  _lightness = -1;

  if (_ultrasonic_state) {
    _distance = _ultrasonic->ping_cm();
  }
  if (_ldr_state) {
    _lightness = analogRead(_pin_ldr);
  }
}
