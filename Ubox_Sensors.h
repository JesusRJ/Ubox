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
#include "Ubox_Base.h"

typedef enum SensorState { ON = true, OFF = false };

class Ubox_Sensors : public Ubox_Base {
public:
  /* Class constructor.
    Parameters:
    ultrasonic: pointer to referenced NewPing object
    pin_ldr: LDR pin
    interval: interval to check sensors between process
  */
  Ubox_Sensors(NewPing *ultrasonic, uint8_t pin_ldr, unsigned long interval);
  void setUltrasonicState(SensorState state); // Turn On/Off process of ultrasonic sensor
  void setLDRState(SensorState state); // Turn On/Off process of ldr sensor
  long distance(); // Get last distance read value
  int lightness(); // Get last lightness read value
  void run(); // Process read sensors
  void readUltrasonic(); // Read a Ultrasonic value
  void readLDR(); // Read actual LDR value
private:
  uint8_t _pin_ldr;
  int _lightness = -1;
  long _distance = -1;

  NewPing *_ultrasonic;

  SensorState _ultrasonic_state = OFF; // Ultrasonic process state
  SensorState _ldr_state = OFF; // LDR process state
};

#endif
