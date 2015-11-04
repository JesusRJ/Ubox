// -----
// Ubox_Sensors.h - Library to control the sensors from uBox.
// -----

#ifndef Ubox_Sensors_h
#define Ubox_Sensors_h

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <SoftwareSerial.h>
#include <Servo.h>
#include <UboxPing.h>

class Ubox_Sensors {
public:
  /* Class constructor.
    Parameters:
    ultrasonic: pointer to array referenced pins from sonar
    pin_ldr: LDR pin
    pin_servo_head: Pin servo head horizontal move
  */
  Ubox_Sensors(uint8_t *ultrasonic, uint8_t pin_ldr, uint8_t pin_servo_head);
  void process(); // Process read sensors
  void ultrasonicOn(); // Turn On read of ultrasonic sensor
  void ultrasonicOff(); // Turn Off read of ultrasonic sensor
  void ldrOn(); // Turn On read of ldr sensor
  void ldrOff(); // Turn Off read of ldr sensor
private:
  bool _ultrasonic_on = false;
  bool _ldr_on = false;
  uint8_t _pin_ldr;
  UboxPing _ultrasonic;
  Servo _servo_head;
};

#endif