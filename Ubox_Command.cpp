#include <ArduinoJson.h>
#include "Ubox_Command.h"

Ubox_Command::Ubox_Command(SoftwareSerial *bluetooth, Ubox_Head *head, Ubox_Engines *engines,
                           Ubox_Sensors *sensors, unsigned long interval) {

  Ubox_Base::setInterval(interval);

  _bluetooth = bluetooth;
  _head = head;
  _engines = engines;
  _sensors = sensors;
  _onDisplay = 0;

  _bluetooth->begin(9600);
}

void Ubox_Command::run() {
  // Serial USB command processor
  parser(&Serial);
  // Bluetooth command processor
  parser(_bluetooth);

  if (_mode == AUTO) {
    processAutonomousMode();
  }
}

void Ubox_Command::setMode(OperationMode mode) {
  _mode = mode;
  if (_mode == AUTO) {
    _sensors->setLDRState(ON);
    _sensors->setUltrasonicState(ON);
  } else {
    _sensors->setLDRState(OFF);
    _sensors->setUltrasonicState(OFF);
  }
}

/**
 * Autonomous Mode: stop when distance is minor than 20cm
 * and check by another direction to follow
 */
void Ubox_Command::processAutonomousMode() {
  if (_sensors->distance() <= 20) {
    _engines->stop();
    _engines->run();

    long left = 0, right = 0;

    _head->right(0);
    _head->run();
    right = _sensors->readUltrasonic();

    _head->left(0);
    _head->run();
    left = _sensors->readUltrasonic();

    if (left > right) {
      _engines->left(2000);
    } else {
      _engines->right(2000);
    }
    
    _head->center();
    _head->run();
    _engines->run();
  }

  if (_engines->action() == STOP) {
    _engines->forward();
  }
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
      _head->left(root["#"], true);
    } else {
      _head->left(0);
    }
  }
  else if (cmd[0] == HEAD_RIGHT) {
    if (root.containsKey("#")) {
      _head->right(root["#"], true);
    } else {
      _head->right(0);
    }
  }
  else if (cmd[0] == CMD_PRINT) {
    if (_onDisplay) {
      _onDisplay(root["#"]);
    }
  } else if (cmd[0] == CMD_GETINFO) {
    _sensors->readUltrasonic();
    _sensors->readLDR();

    StaticJsonBuffer<60> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    JsonArray& data = root.createNestedArray("sensors");
    
    data.add(_sensors->distance());
    data.add(_sensors->lightness());

    root.printTo(Serial);
  } else if (cmd[0] == CMD_MODE) {
    if (root.containsKey("#")) {
      if (root["#"] == 0) {
        setMode(RC);
      } else {
        setMode(AUTO);
      }
    }
  }
}

/* Parser commands on format:
 *   {"@":"p","#":"192.168.110.112"}
 #   {"@":"p","#":["192.168.110.112","192.168.110.112"]}
 *   {"@":"i"}
 *   {"@":"g"}
 *   {"@":"j","#":50}
 *   {"@":"l","#":50}
 *   {"@":"m","#":1}
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