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

// Default values
#define MAX_SENSOR_DISTANCE 150
#define INTERVAL_HEAD 100
#define INTERVAL_ENGINES 100
#define INTERVAL_COMMAND 100
#define INTERVAL_SENSORS 500

// Type for callback function display
typedef void (*displayHandler)(const char*, const char*);
typedef void (*displayHandlerLine)(const char*);

class Ubox_Base {
public:
  /* Class constructor. */
  Ubox_Base();
  void setInterval(unsigned long interval);

  /* Checks if the time elapsed */
  bool timeElapsed(unsigned long interval);
  
  /* Event Display */
  void eventDisplay(displayHandler handler);
  /* Event Display in one line only*/
  void eventDisplayLine(displayHandlerLine handler);

  /* Process function*/
  virtual void process();
protected:
  unsigned long _interval = 200;
  unsigned long _currentTime = 0;
  unsigned long _previousTime = 0;

  // Callback pointers for event functions
  displayHandler _onDisplay; // Callback for display function
  displayHandlerLine _onDisplayLine; // Callback for display function line

  virtual void run() {};
};

#endif
