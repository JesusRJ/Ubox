#include <NewPing.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Ubox_Sensors.h>

#define pin_trigger 3
#define pin_echo 4

NewPing ultrasonic(pin_trigger, pin_echo, 200);

Ubox_Sensors sensors(&ultrasonic);

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensors.process();
  delay(500);
}
