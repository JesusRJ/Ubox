// -----
// Ubox_Time.h - Library to control time to process routine
// -----

#ifndef Ubox_Time_h
#define Ubox_Time_h

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

class Ubox_Time {
public:
  /* Class constructor. */
  Ubox_Time();
  void setInterval(unsigned long interval);
  virtual void process();
protected:
  unsigned long _interval = 100;
  unsigned long _previousTime = 0;

  virtual void run() {};
};

#endif
