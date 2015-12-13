// -----
// Ubox_Base.h - Library to control time to process routine
// -----

#ifndef Ubox_Base_h
#define Ubox_Base_h

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

// Type for callback function
typedef void (*commandEventHandler)(const char*);

class Ubox_Base {
public:
  /* Class constructor. */
  Ubox_Base();
  void setInterval(unsigned long interval);
  
  /* Checks if the time elapsed */
  bool timeElapsed(unsigned long interval);
  
  /* Events */
  void eventDisplay(commandEventHandler handler);

  /* Process function*/
  virtual void process();
protected:
  unsigned long _interval = 200;
  unsigned long _currentTime = 0;
  unsigned long _previousTime = 0;

  // Callback pointers for event functions
  commandEventHandler _onDisplay; // Callback for display function

  virtual void run() {};
};

#endif
