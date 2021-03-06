// -----
// Ubox_Sensors.h - Library to control the sensors from uBox.
// -----

#ifndef Ubox_Sensors_h
#define Ubox_Sensors_h

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
  uint8_t lightness(); // Get last lightness read value
  void run(); // Process read sensors
  long readUltrasonic(); // Read a Ultrasonic value
  uint8_t readLDR(); // Read actual LDR value
private:
  uint8_t _pin_ldr;
  uint8_t _lightness = -1;
  long _distance = -1;

  NewPing *_ultrasonic;

  SensorState _ultrasonic_state = OFF; // Ultrasonic process state
  SensorState _ldr_state = OFF; // LDR process state
};

#endif
