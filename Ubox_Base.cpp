#include "Ubox_Base.h"

Ubox_Base::Ubox_Base() {
}

void Ubox_Base::setInterval(unsigned long interval) {
  _interval = interval;
}

void Ubox_Base::eventDisplay(commandEventHandler handler) {
  _onDisplay = handler;
}

void Ubox_Base::process() {
  _currentTime = millis();

  if(_currentTime - _previousTime > _interval) {
    _previousTime = _currentTime;
    run();
  }
}