// -----
// Ubox_Sensors.h - Library to control the sensors from uBox.
// -----

#ifndef Ubox_Sensors_h
#define Ubox_Sensors_h

#if defined (ARDUINO) && ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
  #include <pins_arduino.h>
#endif

#if defined (__AVR__)
  #include <avr/io.h>
  #include <avr/interrupt.h>
#endif

#include <NewPing.h>
#include "Ubox_Time.h"

typedef enum SensorState { ON = true, OFF = false };

class Ubox_Sensors : public Ubox_Time {
public:
  /* Class constructor.
    Parameters:
    ultrasonic: pointer to referenced NewPing object
    pin_ldr: LDR pin
    interval: interval to check sensors between process
  */
  Ubox_Sensors(NewPing *ultrasonic, uint8_t pin_ldr, uint8_t interval);
  void run(); // Process read sensors
  void setUltrasonicState(SensorState state); // Turn On/Off process of ultrasonic sensor
  void setLDRState(SensorState state); // Turn On/Off process of ldr sensor
  int lightness(); // Get last lightness read value
  long distance(); // Get last distance read value
private:
  uint8_t _pin_ldr;
  int _lightness = -1;
  long _distance = -1;

  NewPing *_ultrasonic;

  SensorState _ultrasonic_state = OFF; // Ultrasonic process state
  SensorState _ldr_state = OFF; // LDR process state
};

#endif
