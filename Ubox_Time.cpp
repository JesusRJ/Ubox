#include "Ubox_Time.h"

Ubox_Time::Ubox_Time() {
}

void Ubox_Time::setInterval(unsigned long interval) {
  _interval = interval;
}

void Ubox_Time::process() {
  unsigned long currentTime = millis();
 
  if(currentTime - _previousTime > _interval) {
    _previousTime = currentTime;   
    run();
  }
}