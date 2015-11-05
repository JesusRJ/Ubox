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

void Ubox_Command::eventDisplay(commandEventHandler handler) {
  _onDisplay = handler;
}

void Ubox_Command::processCommand(String cmd) {
  Serial.println("Processa String");
  if (cmd == CMD_VOICE_ENABLE) {
    _voice_active = true;
    Serial.println(CMD_VOICE_ENABLE);
  }

  if (cmd == CMD_VOICE_DISABLE) {
    _voice_active = false;
    Serial.println(CMD_VOICE_DISABLE);
  }

  if (_voice_active) {
    if (cmd == CMD_FORWARD) {
      processCommand('w'); Serial.println(CMD_FORWARD);
    } else if (cmd == CMD_FORWARD2) {
      processCommand('w'); Serial.println(CMD_FORWARD2);
    } else if (cmd == CMD_BACKWARD) {
      processCommand('s'); Serial.println(CMD_BACKWARD);
    } else if (cmd == CMD_BACKWARD2) {
      processCommand('s'); Serial.println(CMD_BACKWARD2);
    } else if (cmd == CMD_LEFT) {
      processCommand('a'); Serial.println(CMD_LEFT);
    } else if (cmd == CMD_LEFT2) {
      processCommand('a'); Serial.println(CMD_LEFT2);
    } else if (cmd == CMD_RIGHT) {
      processCommand('d'); Serial.println(CMD_RIGHT);
    } else if (cmd == CMD_RIGHT2) {
      processCommand('d'); Serial.println(CMD_RIGHT2);
    } else if (cmd == CMD_STOP) {
      processCommand('q'); Serial.println(CMD_STOP);
    } else if (cmd == CMD_STOP2) {
      processCommand('q'); Serial.println(CMD_STOP2);
    }
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