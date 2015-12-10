// -----
// Ubox_Command.h - Library to control uBox by Serial Commands
// -----

#ifndef Ubox_Command_h
#define Ubox_Command_h

// Engines commands
#define ENGINES_FORWARD  'w'
#define ENGINES_BACKWARD 's'
#define ENGINES_LEFT     'a'
#define ENGINES_RIGHT    'd'
#define ENGINES_STOP     'q'
// Head commands
#define HEAD_CENTER 'i'
#define HEAD_LEFT   'j'
#define HEAD_RIGHT  'l'
// Other commands
#define CMD_PRINT 'p'

// Voice commands (pt-BR)
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
#include "Ubox_Base.h"
#include "Ubox_Head.h"
#include "Ubox_Engines.h"

typedef enum OperationMode { RC, AUTO };

class Ubox_Command : public Ubox_Base {
public:
  /* Class constructor.
    Parameters:
    serial: pointer to bluethoot
    head: pointer to head control
    engines: pointer to engines control
    interval: interval to check sensors between process
  */
  Ubox_Command(SoftwareSerial *bluetooth, Ubox_Head *head, Ubox_Engines *engines, unsigned long interval);
  void run();
private:
  SoftwareSerial *_bluetooth;
  Ubox_Head *_head;
  Ubox_Engines *_engines;
  OperationMode _mode = RC;

  void processCommand(JsonObject& root);
  void parser(Stream *in);
};

#endif
