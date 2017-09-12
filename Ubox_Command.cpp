#include <ArduinoJson.h>
#include "Ubox_Command.h"

Ubox_Command::Ubox_Command(SoftwareSerial *bluetooth, Ubox_Head *head, Ubox_Engines *engines,
                           Ubox_Sensors *sensors, LiquidCrystal_I2C *lcd, unsigned long interval) {

  Ubox_Base::setInterval(interval);

  _bluetooth = bluetooth;
  _head = head;
  _engines = engines;
  _sensors = sensors;
  _lcd = lcd;
  _onDisplay = 0;
  _onDisplayLine = 0;

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
  _lcd->clear();

  _onDisplay(String("Dist.: " + String(_sensors->distance())).c_str(),
             String("Ligh.: " + String(_sensors->lightness())).c_str());

  _lcd->setCursor(15, 0);
  switch (_engines->action()) {
      case STOP:
      _lcd->write(5);
    break;
    case GO_FORWARD:
      _lcd->write(1);
    break;
    case GO_BACKWARD:
      _lcd->write(2);
    break;
    case GO_RIGHT:
      _lcd->write(4);
    break;
    case GO_LEFT:
      _lcd->write(3);
    break;
  }

  if (_sensors->distance() > 0 && _sensors->distance() <= 20) {
    _engines->stop(false);
    _engines->run();

    long left = 0, left50 = 0, right = 0, right50 = 0;

    // Read left full
    _head->left(0);
    _head->run();
    left = _sensors->readUltrasonic();
    delay(10);
    
    // Read left 50%
    _head->left(50, true);
    _head->run();
    left50 = _sensors->readUltrasonic();
    delay(10);

    // Read right full
    _head->right(0);
    _head->run();
    right = _sensors->readUltrasonic();
    delay(10);

    // Read right 50%
    _head->right(50, true);
    _head->run();
    right50 = _sensors->readUltrasonic();
    delay(10);

    // Go back
    if ((left50 > 0 && left50 <= 20) && (right50 > 0 && right50 <= 20)) {
      _engines->backward(3000, false);
      _engines->stop(false);
    }

    // Turn to any direction
    if (left >= right) {
      _engines->left(2000, false);
    } else {
      _engines->right(2000, false);
    }
    
    _head->center();
    _head->run();
    _engines->run();
  } else {
    delay(300);
  }

  if (_engines->action() == STOP) {
    _engines->forward();
  }

  // {"@":"m","#":1}
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
  } else if (cmd[0] == HEAD_LEFT) {
    if (root["#"].success()) {
      _head->left(root["#"], true);
    } else {
      _head->left(0);
    }
  } else if (cmd[0] == HEAD_RIGHT) {
    if (root["#"].success()) {
      _head->right(root["#"], true);
    } else {
      _head->right(0);
    }
  } else if (cmd[0] == CMD_PRINT) {
    if (_onDisplayLine) {
      _onDisplayLine(root["#"]);
    }
  } else if (cmd[0] == CMD_GETINFO) {
    _sensors->readUltrasonic();
    _sensors->readLDR();

    StaticJsonBuffer<60> jsonBuffer;

    JsonObject& root = jsonBuffer.createObject();
    JsonArray& data = root.createNestedArray("sensors");
    
    data.add(_sensors->distance());
    data.add(_sensors->lightness());
    
    _onDisplay(String("Dist.: " + String(_sensors->distance())).c_str(),
               String("Ligh.: " + String(_sensors->lightness())).c_str());

    root.printTo(Serial);
  } else if (cmd[0] == CMD_MODE) {
    if (root["#"] == 0) {
      setMode(RC);
    } else {
      setMode(AUTO);
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

  char data[60];
  char c;
  int idx = 0;
  
  while ( in->available() ) {
    delay(10); // Delay stabilizing
    c = (char)in->read();
    data[idx++] = c;
  }

  // String finalize
  data[idx] = (char)0;

  if (idx > 0) {
    // Voice parser
    if (data[0] == '*') {
      Serial.print("Received Voice: ");
      Serial.println(data);

      StaticJsonBuffer<60> jsonBuffer;

      JsonObject& root = jsonBuffer.createObject();

      if (data == CMD_FORWARD || data == CMD_FORWARD2)  { root["@"] = String(ENGINES_FORWARD); }
      if (data == CMD_BACKWARD ||data == CMD_BACKWARD2) { root["@"] = String(ENGINES_BACKWARD); }
      if (data == CMD_LEFT || data == CMD_LEFT2)        { root["@"] = String(ENGINES_LEFT); }
      if (data == CMD_RIGHT || data == CMD_RIGHT2)      { root["@"] = String(ENGINES_RIGHT); }
      if (data == CMD_STOP || data == CMD_STOP2)        { root["@"] = String(ENGINES_STOP); }

      root.printTo(Serial);

      processCommand(root);

    } else {
      // Json parser
      Serial.print("Received JSON: ");
      Serial.println(data);

      StaticJsonBuffer<60> jsonBuffer;
      JsonObject& root = jsonBuffer.parseObject(data);

      if (!root.success()) {
        Serial.println("Json parseObject() failed!");
        _onDisplayLine(data);
        return;
      }

      if (root["@"].success()) {
        processCommand(root);
      }
    }
  }
}