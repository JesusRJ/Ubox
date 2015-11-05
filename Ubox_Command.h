// -----
// Ubox_Command.h - Library to control uBox by Serial Commands
// -----

#ifndef Ubox_Command_h
#define Ubox_Command_h

#if (ARDUINO <  100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

// Comandos = pt-BR
#define CMD_VOICE_ENABLE "*ativar"
#define CMD_VOICE_DISABLE "*desativar"
#define CMD_FORWARD "*para frente"
#define CMD_FORWARD2 "*pra frente"
#define CMD_BACKWARD "*para trás"
#define CMD_BACKWARD2 "*pra trás"
#define CMD_LEFT "*esquerda"
#define CMD_LEFT2 "*pra esquerda"
#define CMD_RIGHT "*direita"
#define CMD_RIGHT2 "*pra direita"
#define CMD_STOP "*parar"
#define CMD_STOP2 "*parado"

#include <SoftwareSerial.h>
#include <Ubox_Engines.h>

// class Ubox_Command;
typedef void (*commandEventHandler)(String&);

class Ubox_Command {
public:
  /* Class constructor. */
  Ubox_Command(SoftwareSerial *serial, Ubox_Engines *engines);
  void process();
  void eventDisplay(commandEventHandler handler);

private:
  void processCommand(String cmd);
  void processCommand(char cmd);

  SoftwareSerial *_serial;
  Ubox_Engines *_engines;
  commandEventHandler _onDisplay; // Callback for display
  bool _voice_active = false;
};

#endif