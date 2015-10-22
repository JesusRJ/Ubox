#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Ubox_Engines.h>

#define m1_pin1 4 
#define m1_pin2 5
#define m2_pin1 6
#define m2_pin2 7
#define m1_pin_enable 9
#define m2_pin_enable 10

// Define os pinos de controle dos motores
uint8_t motor1[3] = { m1_pin1, m1_pin2, m1_pin_enable };
uint8_t motor2[3] = { m2_pin1, m2_pin2, m2_pin_enable };

// Inicializa o controlador de motores
Ubox_Engines engines(motor1, motor2);

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// Inicializa o bluetooth
SoftwareSerial bluetooth(11, 12); // RX  TX

char cmd;

void setup() {
  // Configure Display
  lcd.noBacklight();
  lcd.begin (16, 2);

  lcd.home();
  lcd.print("Unisys");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  
  // System setup
  Serial.begin(9600);
  bluetooth.begin(9600);
  engines.setSpeed(MIN_SPEED);
  // end - System setup

  delay(500);
  lcd.clear();
  lcd.print("      uBox      ");
}

void loop() {
  engines.process();

  if (bluetooth.available()) {
    cmd = (char)bluetooth.read();

    Serial.println(cmd);

    switch (cmd) {
      case 'w':
        engines.forward();
        lcd.clear();
        lcd.print("FORWARD");
        bluetooth.println("FORWARD");
        break;
      case 's':
        engines.backward();
        lcd.clear();
        lcd.print("BACKWARD");
        bluetooth.println("BACKWARD");
        break;
      case 'a':
        engines.left();
        lcd.clear();
        lcd.print("LEFT");
        bluetooth.println("LEFT");
        break;
      case 'd':
        engines.right();
        lcd.clear();
        lcd.print("RIGHT");
        bluetooth.println("RIGHT");
        break;
      case 'q':
        engines.stop();
        lcd.clear();
        lcd.print("STOPPED");
        bluetooth.println("STOPPED");
        break;
    }
  }
}
