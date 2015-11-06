// -----
// Ubox_Head.h - Library to control uBox engines.
// -----

#ifndef Ubox_Head_h
#define Ubox_Head_h

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

#include <Servo.h>
#include "Ubox_Time.h"
#include "Ubox_Sensors.h"

typedef enum ActionHead { CENTER, RIGHT, LEFT, QUIET };

class Ubox_Head : public Ubox_Time {
public:
  /* Class constructor 
    Parameters:
    pin_servo_head: Pin to head attach servo
    interval: interval to check sensors between process*/
  Ubox_Head(uint8_t pin_servo_head, uint8_t interval); 

  void setSensors(Ubox_Sensors *sensors); // Set sensors reference
  void run(); // Process the action of head
  void center(); // Set CENTER action
  void right(); // Set RIGHT action
  void left(); // Set LEFT action
  void quiet(); // Set QUIET action
  ActionHead action(); // Return the action value
private:
  ActionHead _action = CENTER; // Current action
  ActionHead _last_action = CENTER; // Last action control
  Servo _servoHead; // Servo horizontal head control
  Ubox_Sensors *_sensors; // Sensors reference

  void setAction(ActionHead action); // Set current action
};

#endif
