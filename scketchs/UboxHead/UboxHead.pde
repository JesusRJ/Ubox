#include <NewPing.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Ubox_Sensors.h>

#define pin_trigger 3
#define pin_echo 4
#define pin_ldr 5 // A5 - Analog pin

NewPing ultrasonic(pin_trigger, pin_echo, 200);

Ubox_Sensors sensors(&ultrasonic, pin_ldr);

void setup() {
  Serial.begin(9600);
}

void loop() {
  sensors.process();
  delay(500);
}
