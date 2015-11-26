#include "Ubox_Command.h"

Ubox_Command::Ubox_Command(SoftwareSerial *bluetooth, Ubox_Head *head, Ubox_Engines *engines, unsigned long interval) {
  Ubox_Base::setInterval(interval);

  _bluetooth = bluetooth;
  _head = head;
  _engines = engines;
  _onDisplay = 0;

  _bluetooth->begin(9600);
}

void Ubox_Command::run() {
  String ucmd = ""; // USB command
  String bcmd = ""; // Bluetooth command
  char c;

  // Serial USB command processor
  if (Serial) {
    while (Serial.available()) {
      delay(10); // Delay stabilizing
      c = (char)_bluetooth->read();
      if (c == '#' || c == '\n') { break; } // end loop when # or \n is detected
      ucmd += c;
    }
  }

  // Bluetooth command processor
  while ( _bluetooth->available() ) {
    delay(10); // Delay stabilizing
    c = (char)_bluetooth->read();
    if (c == '#' || c == '\n') { break; } // end loop when # or \n is detected
    bcmd += c;
  }

  if (bcmd.length() > 0) {
    if (bcmd.length() > 1) {
      processCommand(bcmd); // Processa a string de comando
    } else {
      processCommand(bcmd[0]); // Processa o caracter de comando
    }

    if (_onDisplay) { 
      _onDisplay(bcmd);
    }
  }
}

void Ubox_Command::processCommand(String cmd) {
  if (cmd == CMD_VOICE_ENABLE) {
    _voice_active = true;
  }

  if (cmd == CMD_VOICE_DISABLE) {
    _voice_active = false;
  }

  if (_voice_active) {
    if (cmd == CMD_FORWARD || cmd == CMD_FORWARD2) {
      processCommand(ENGINES_FORWARD);
    } else if (cmd == CMD_BACKWARD || cmd == CMD_BACKWARD2) {
      processCommand(ENGINES_BACKWARD);
    } else if (cmd == CMD_LEFT || cmd == CMD_LEFT2) {
      processCommand(ENGINES_LEFT);
    } else if (cmd == CMD_RIGHT || cmd == CMD_RIGHT2) {
      processCommand(ENGINES_RIGHT);
    } else if (cmd == CMD_STOP || cmd == CMD_STOP2) {
      processCommand(ENGINES_STOP);
    }
  }
}

/*
 * Commands:
 * w,s,a,d,q = Engines control
 * i,j,l   = Head control
 */
void Ubox_Command::processCommand(char cmd) {
  switch (cmd) {
    case ENGINES_FORWARD:
      _engines->forward();
      break;
    case ENGINES_BACKWARD:
      _engines->backward();
      break;
    case ENGINES_LEFT:
      _engines->left();
      break;
    case ENGINES_RIGHT:
      _engines->right();
      break;
    case ENGINES_STOP:
      _engines->stop();
      break;
    case HEAD_CENTER:
      _head->center();
      break;
    case HEAD_LEFT:
      _head->left(0);
      break;
    case HEAD_RIGHT:
      _head->right(0);
      break;
  }
}