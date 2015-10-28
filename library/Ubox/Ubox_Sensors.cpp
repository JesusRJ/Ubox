#include "Ubox_Sensors.h"

// -----
// PUBLIC METHODS
// -----
Ubox_Sensors::Ubox_Sensors(NewPing *ultrasonic) {
  _ultrasonic = ultrasonic;
}

void Ubox_Sensors::process() {
  unsigned long distance = _ultrasonic->ping_cm();
  Serial.write(distance);
}