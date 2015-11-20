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
      delay(10); //Delay estabilizador
      c = (char)_bluetooth->read();
      if (c == '#' || c == '\n') { break; } //termina o loop quando # ou \n é detectado após a palavra
      cmd += c;
    }
  }

  while ( _bluetooth->available() ) { //checa se ha byte disponivel para leitura pelo bluetooth
    delay(10); //Delay estabilizador
    c = (char)_bluetooth->read();
    if (c == '#' || c == '\n') { break; } //termina o loop quando # ou \n é detectado após a palavra
    btcmd += c;
  }

  if (btcmd.length() > 0) {
    if (btcmd.length() > 1) {
      processCommand(btcmd); // Processa a string de comando
    } else {
      processCommand(btcmd[0]); // Processa o caracter de comando
    }

    if (_onDisplay) { 
      _onDisplay(btcmd);
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
      processCommand('w');
    } else if (cmd == CMD_BACKWARD || cmd == CMD_BACKWARD2) {
      processCommand('s');
    } else if (cmd == CMD_LEFT || cmd == CMD_LEFT2) {
      processCommand('a');
    } else if (cmd == CMD_RIGHT || cmd == CMD_RIGHT2) {
      processCommand('d');
    } else if (cmd == CMD_STOP || cmd == CMD_STOP2) {
      processCommand('q');
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
      _head->left(0);
      break;
    case 'l':
      _head->right(0);
      break;
  }
}