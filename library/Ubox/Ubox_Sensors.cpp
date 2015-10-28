#include "Ubox_Sensors.h"

// -----
// PUBLIC METHODS
// -----
Ubox_Sensors::Ubox_Sensors(NewPing *ultrasonic, , uint8_t pin_ldr) {
  _ultrasonic = ultrasonic;
  _pin_ldr = pin_ldr;
}

void Ubox_Sensors::process() {
  unsigned long distance = _ultrasonic->ping_cm();
  Serial.write(distance);
}