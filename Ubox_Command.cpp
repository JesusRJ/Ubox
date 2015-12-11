#include <ArduinoJson.h>
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
  // Serial USB command processor
  parser(&Serial);
  // Bluetooth command processor
  parser(_bluetooth);
}

void Ubox_Command::processCommand(JsonObject& root) {
  const char* cmd = root["@"];

  if (cmd[0] == ENGINES_FORWARD) {
    _engines->forward();
  }
  else if (cmd[0] == ENGINES_BACKWARD) {
    _engines->backward();
  }
  else if (cmd[0] == ENGINES_LEFT) {
    _engines->left();
  }
  else if (cmd[0] == ENGINES_RIGHT) {
    _engines->right();
  }
  else if (cmd[0] == ENGINES_STOP) {
    _engines->stop();
  }
  else if (cmd[0] == HEAD_CENTER) {
    _head->center();
  }
  else if (cmd[0] == HEAD_LEFT) {
    if (root.containsKey("#")) {
      _head->left(root["#"]);
    } else {
      _head->left(0);
    }
  }
  else if (cmd[0] == HEAD_RIGHT) {
    if (root.containsKey("#")) {
      _head->right(root["#"]);
    } else {
      _head->right(0);
    }
  }
  else if (cmd[0] == CMD_PRINT) {
    if (_onDisplay) {
      _onDisplay(root["#"]);
    }
  }
}

/* Parser commands on format:
 *   {"@":"p","#":["192.168.110.112","192.168.110.112"]}
 *   {"@":"p","#":"192.168.110.112"}
 * Where:
 *   @ = Command Key
 *   # = Value Key
 */
void Ubox_Command::parser(Stream *in) {
  StaticJsonBuffer<60> jsonBuffer;

  char json[60];
  char c;
  int idx = 0;
  
  while ( in->available() ) {
    delay(10); // Delay stabilizing
    c = (char)in->read();
    json[idx++] = c;
  }

  // String finalize
  json[idx] = (char)0;

  if (idx > 0) {
    Serial.print("Received JSON: ");
    Serial.println(json);

    JsonObject& root = jsonBuffer.parseObject(json);

    if (!root.success()) {
      Serial.println("Json parseObject() failed!");
      return;
    }

    if (root.containsKey("@")) {
      processCommand(root);
    }

  }
}