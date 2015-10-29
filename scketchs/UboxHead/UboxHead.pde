#include <UboxPing.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Ubox_Sensors.h>

#define pin_trigger 3
#define pin_echo 4
#define pin_ldr 5 // A5 - Analog pin

UboxPing ultrasonic(pin_trigger, pin_echo, 200);

Ubox_Sensors sensors(&ultrasonic, pin_ldr);

int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}

void loop() {
  //sensors.process();
  digitalWrite(13, HIGH);
  Serial.println(count); 
  delay(2000);
  digitalWrite(13, LOW);
  delay(1000);
  count++;
}
