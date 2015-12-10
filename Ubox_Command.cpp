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

  switch (cmd[0]) {
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
      const char* value = root["#"];
      _head->left(0);
      break;
    case HEAD_RIGHT:
      _head->right(0);
      break;
    case CMD_PRINT:
      if (_onDisplay) {
        const char* value = root["#"];
        Serial.println(value);
        _onDisplay(value);
      }
      break;
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