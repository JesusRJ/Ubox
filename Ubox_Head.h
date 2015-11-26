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
#include "Ubox_Base.h"
#include "Ubox_Sensors.h"

typedef enum ActionHead { CENTER, RIGHT, LEFT };

class Ubox_Head : public Ubox_Base {
public:
  /* Class constructor
    Parameters:
    pin_servo_head: Pin to head attach servo
    interval: interval to check sensors between process*/
  Ubox_Head(uint8_t pin_servo_head, unsigned long interval); 

  void setSensors(Ubox_Sensors *sensors); // Set sensors reference
  void run(); // Process the action of head
  void center(); // Set CENTER action
  void right(uint8_t position); // Set RIGHT action
  void left(uint8_t position); // Set LEFT action
  ActionHead action(); // Return the action value
private:
  uint8_t _pin_servo_head = 8;
  uint8_t _pos_servo_head = 0; // x% for position servo head

  ActionHead _action = CENTER; // Current action
  ActionHead _last_action = CENTER; // Last action control
  Servo _servoHead; // Servo horizontal head control
  Ubox_Sensors *_sensors; // Sensors reference

  void setAction(ActionHead action); // Set current action
  void setPosition(uint8_t position);
};

#endif
