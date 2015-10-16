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
    /*!
      @method     
      @abstract   Class constructor. 
      @discussion Initializes class variables and defines the pins address of the
      engines.
      
      @param
      */
      Ubox_Engines (uint8_t m1_pin1, uint8_t m1_pin2, uint8_t m2_pin1, uint8_t m2_pin2, uint8_t m1_pin_enable, uint8_t m2_pin_enable);
      void setSpeed();
      void stop ();
      void forward ();
      void backward ();
      void right ();
      void left ();
    private:
      void action (Action action);
};

#endif