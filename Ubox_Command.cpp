#include "Ubox_Command.h"

Ubox_Command::Ubox_Command(SoftwareSerial *bluetooth, Ubox_Head *head, Ubox_Engines *engines, unsigned long interval) {
  Ubox_Base::setInterval(interval);

  _bluetooth = bluetooth;
  _head = head;
  _engines = engines;
  _onDisplay = 0;

  Serial.begin(9600); // Serial for PC communication
  _bluetooth->begin(9600);
}

void Ubox_Command::run() {
  String cmd = "";
  String btcmd = "";
  char c;

  // Processa comandos enviados via USB
  if (Serial) {
    while (Serial.available()) {

    }
  }

  while ( _bluetooth->available() ) { //checa se ha byte disponivel para leitura pelo bluetooth
    delay(10); //Delay estabilizador 
    c = (char)_bluetooth->read();
    if (c == '#' || c == '\n') { break; } //termina o loop quando # ou \n é detectado após a palavra
    cmd += c;
  }

  if (cmd.length() > 0) {
    if (cmd.length() > 1) {
      processCommand(cmd); // Processa a string de comando
    } else {
      processCommand(cmd[0]); // Processa o caracter de comando
    }

    if (_onDisplay) { 
      _onDisplay(cmd);
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
    if (cmd == CMD_FORWARD) {
      processCommand('w');
    } else if (cmd == CMD_FORWARD2) {
      processCommand('w');
    } else if (cmd == CMD_BACKWARD) {
      processCommand('s');
    } else if (cmd == CMD_BACKWARD2) {
      processCommand('s');
    } else if (cmd == CMD_LEFT) {
      processCommand('a');
    } else if (cmd == CMD_LEFT2) {
      processCommand('a');
    } else if (cmd == CMD_RIGHT) {
      processCommand('d');
    } else if (cmd == CMD_RIGHT2) {
      processCommand('d');
    } else if (cmd == CMD_STOP) {
      processCommand('q');
    } else if (cmd == CMD_STOP2) {
      processCommand('q');
    }
  }
}

/*
 * Commands:
 * w,s,a,d,q = Engines control
 * i,k,j,l   = Head control
 */
void Ubox_Command::processCommand(char cmd) {
  switch (cmd) {
    case 'w':
      _engines->forward();
      break;
    case 's':
      _engines->backward();
      break;
    case 'a':
      _engines->left();
      break;
    case 'd':
      _engines->right();
      break;
    case 'q':
      _engines->stop();
      break;
    case 'i':
      _head->center();
      break;
    case 'j':
      _head->left();
      break;
    case 'l':
      _head->right();
      break;
    case 'k':
      _head->quiet();
      break;
  }
}