// -----
// Ubox_Engines.h - Library to control uBox engines.
// -----

#ifndef Ubox_Engines_h
#define Ubox_Engines_h

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

#include <inttypes.h>

#define MIN_SPEED 115 // Min speed to move uBox
#define MAX_SPEED 255 // Max speed from uBox
#define MOTOR_DELAY 30 // Time to wait action motor
#define DEBUG_MOTOR 3000 // Time to debug motor

typedef enum Action { STOP, FORWARD, BACKWARD, RIGHT, LEFT };

class Ubox_Engines {
public:
  /* Class constructor.
    Receive two pointers to array referenced pins.
  */
  Ubox_Engines(uint8_t *motor1, uint8_t *motor2); 

  void setSpeed(int speed); // Set the speed
  void process(); // Process the action of engines
  void stop(); // Set STOP action
  void forward(); // Set FORWARD action
  void backward(); // Set BACKWARD action
  void right(); // Set RIGHT action
  void left(); // Set LEFT action
  Action action(); // Return the action value
private:
  uint8_t *_motor1; // Pointer to motor1 pin definitions
  uint8_t *_motor2; // Pointer to motor2 pin definitions
  int _speed = MIN_SPEED; // Current speed 
  Action _action = STOP; // Current action

  void setAction(Action action); // Set current action
  void motorStop(uint8_t *motor); // Put motor to forward action
  void motorForward(uint8_t *motor); // Put motor to forward action
  void motorBackward(uint8_t *motor); // Put motor to backward action
};

#endif