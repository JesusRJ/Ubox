#include "Ubox_Sensors.h"

// -----
// PUBLIC METHODS
// -----
Ubox_Sensors::Ubox_Sensors(uint8_t *ultrasonic, uint8_t pin_ldr, uint8_t pin_servo_head) {
  _pin_ldr = pin_ldr;
  _ultrasonic = new UboxPing(ultrasonic[0], ultrasonic[1]);
  _servo_head = new Servo(pin_servo_head);
}

void Ubox_Sensors::process() {
  if (_ultrasonic_on) {
    unsigned long distance = _ultrasonic.ping_cm();
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