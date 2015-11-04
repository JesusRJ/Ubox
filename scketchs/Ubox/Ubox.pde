#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <Ubox_Command.h>
#include <Ubox_Sensors.h>
#include <Ubox_Engines.h>

// Motors pins
#define m1_pin1 4
#define m1_pin2 5
#define m2_pin1 6
#define m2_pin2 7
#define m1_pin_enable 9
#define m2_pin_enable 10
// Ultrasonic pins
#define pin_trigger 3
#define pin_echo 4
#define pin_ldr A0 // Analog pin
// Servos pins
#define pin_servo_head 8 // Head Control Servo Horizontal

// Define os pinos de controle dos motores
uint8_t motor1[3] = { m1_pin1, m1_pin2, m1_pin_enable };
uint8_t motor2[3] = { m2_pin1, m2_pin2, m2_pin_enable };
uint8_t ultrasonic[2] = { pin_trigger, pin_echo };

// Inicializa o display no endereco 0x27
//LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
LiquidCrystal_I2C lcd(0x27);

// Inicializa o bluetooth
SoftwareSerial bluetooth(11, 12); // RX  TX

// Inicializa o controlador de motores
Ubox_Engines engines(motor1, motor2);

// Inicializa o controle por voz ou teclado
Ubox_Command command(&bluetooth, &engines);

// Inicializa os sensores
Ubox_Sensors sensors(ultrasonic, pin_ldr, pin_servo_head);

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
  command.eventDisplay(onDisplayLine2);
  // end - System setup

  delay(500);
  lcd.clear();
  lcd.print("      uBox      ");
}

void loop() {
  command.process();
  sensors.process();
  engines.process();
}

void onDisplayLine2(String& value) {
  Serial.println("onDisplay Line2");
  lcd.setCursor(0, 1);
  lcd.print(value);
}
