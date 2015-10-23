#include "Ubox_Command.h"

Ubox_Command::Ubox_Command(SoftwareSerial *serial, Ubox_Engines *engines) {
  _serial = serial;
  _engines = engines;

  _onDisplay = 0;
}

void Ubox_Command::process() {
  String cmd = "";
  char c;

  while ( _serial->available() ) { //checa se ha byte disponivel para leitura
    delay(10); //Delay estabilizador 
    c = (char)_serial->read();
    if (c == '#') { break; } //termina o loop quando # é detectado após a palavra
    cmd += c; 
  }

  if (cmd.length() > 0) {
    Serial.println(cmd); // DEBUG

    if (cmd.length() > 1) {
      processCommand(cmd); // Processa a string de comando
    } else {
      processCommand(c); // Processa o caracter de comando
    }
  }
}

void Ubox_Command::eventDisplay(commandEventHandler handler) {
  _onDisplay = handler;
}

void Ubox_Command::processCommand(String cmd) {
  if (cmd == CMD_VOICE_ENABLE) {
    _voice_active = true;
    Serial.println(CMD_VOICE_ENABLE);
  }

  if (cmd == CMD_VOICE_DISABLE) {
    _voice_active = false;
    Serial.println(CMD_VOICE_DISABLE);
  }

  if (cmd == CMD_FORWARD || cmd == CMD_FORWARD2)  { processCommand('w'); Serial.println(CMD_FORWARD); }
  if (cmd == CMD_BACKWARD ||cmd == CMD_BACKWARD2) { processCommand('s'); Serial.println(CMD_BACKWARD); }
  if (cmd == CMD_LEFT || cmd == CMD_LEFT2)     { processCommand('a'); Serial.println(CMD_LEFT); }
  if (cmd == CMD_RIGHT || cmd == CMD_RIGHT2)    { processCommand('d'); Serial.println(CMD_RIGHT); }
  if (cmd == CMD_STOP || cmd == CMD_STOP2)     { processCommand('q'); Serial.println(CMD_STOP); }

  if (_onDisplay) { 
    Serial.print("onDisplay");
    _onDisplay(cmd);
  }
}

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
  }
}