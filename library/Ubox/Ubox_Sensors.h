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

class Ubox_Sensors {
public:
  /* Class constructor.
    Parameters:
    sonar: pointer to array referenced pins from sonar
  */
  Ubox_Sensors(uint8_t *sonar);
  void process(); // Process the action of engines
  unsigned long distance(); // Return the distance value read from sonar
private:
  unsigned long calcDistance();
};

#endif