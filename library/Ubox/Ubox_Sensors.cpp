#include "Ubox_Sensors.h"

// -----
// PUBLIC METHODS
// -----
Ubox_Sensors::Ubox_Sensors(UboxPing *ultrasonic, uint8_t pin_ldr) {
  _ultrasonic = ultrasonic;
  _pin_ldr = pin_ldr;
}

void Ubox_Sensors::process() {
  if (_ultrasonic_on) {
    unsigned long distance = _ultrasonic->ping_cm();
    Serial.write(distance);
  }
  if (_ldr_on) {
    int lightness = analogRead(_pin_ldr);
    Serial.write(lightness);
  }
}

void Ubox_Sensors::ultrasonicOn() { _ultrasonic_on = true; }
void Ubox_Sensors::ultrasonicOff() { _ultrasonic_on = false; }
void Ubox_Sensors::ldrOn() { _ldr_on = true; }
void Ubox_Sensors::ldrOff() { _ldr_on = false; }