// -----
// Ubox_Head.h - Library to control uBox engines.
// -----

#ifndef Ubox_Head_h
#define Ubox_Head_h

#include <Servo.h>
#include "Ubox_Base.h"

typedef enum ActionHead { CENTER, RIGHT, LEFT, NONE };

class Ubox_Head : public Ubox_Base {
public:
  /* Class constructor
    Parameters:
    pin_servo_head: Pin to head attach servo
    interval: interval to check sensors between process*/
  Ubox_Head(uint8_t pin_servo_head, unsigned long interval); 

  void run(); // Process the action of head
  void center(); // Set CENTER action
  void right(uint8_t position, bool force=false); // Set RIGHT action
  void left(uint8_t position, bool force=false); // Set LEFT action
  ActionHead action(); // Return the action value
private:
  uint8_t _pin_servo_head = 8;
  uint8_t _pos_servo_head = 0; // x% for position servo head

  ActionHead _action = CENTER; // Current action
  ActionHead _last_action = NONE; // Last action control
  Servo _servoHead; // Servo horizontal head control

  void setAction(ActionHead action); // Set current action
  void setPosition(uint8_t position);
};

#endif
