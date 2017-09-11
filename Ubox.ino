#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
#include <NewPing.h>
#include <Servo.h>
#include <ArduinoJson.h> //https://bblanchon.github.io/ArduinoJson/
#include "Ubox_Base.h"
#include "Ubox_Command.h"
#include "Ubox_Sensors.h"
#include "Ubox_Engines.h"
#include "Ubox_Head.h"

// Motors pins
#define pin_m11 4
#define pin_m12 5
#define pin_m21 6
#define pin_m22 7
#define pin_m1_enable 9
#define pin_m2_enable 10
// Bluetooth pins
#define pin_ble_rx 11
#define pin_ble_tx 12
// Ultrasonic pins
#define pin_trigger 2
#define pin_echo 3
#define pin_ldr A0 // Analog pin
// Servos pins
#define pin_servo_head 8 // Head Control Servo Horizontal

// Engines control pins
uint8_t motor1[3] = { pin_m11, pin_m12, pin_m1_enable };
uint8_t motor2[3] = { pin_m21, pin_m22, pin_m2_enable };

// LCD Display initialize on address 0x27
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
//LiquidCrystal_I2C lcd(0x27);

// Bluetooth initialize
SoftwareSerial bluetooth(pin_ble_rx, pin_ble_tx);

// Ultrasonic sensor initialize
NewPing ultrasonic(pin_trigger, pin_echo, MAX_SENSOR_DISTANCE);

// Initialize order:
//   head controller
//   engines controller
//   commands interpreter (by voice/bluetooth and USB serial)
//   sensor controller
Ubox_Head head(pin_servo_head, INTERVAL_HEAD);
Ubox_Engines engines(motor1, motor2, INTERVAL_ENGINES);
Ubox_Sensors sensors(&ultrasonic, pin_ldr, INTERVAL_SENSORS);
Ubox_Command command(&bluetooth, &head, &engines, &sensors, &lcd, INTERVAL_COMMAND);

// LCD Characters
uint8_t upChar[8]    = {B00000,B00100,B01110,B10101,B00100,B00100,B00100,B00000};
uint8_t downChar[8]  = {B00000,B00100,B00100,B00100,B10101,B01110,B00100,B00000};
uint8_t leftChar[8]  = {B00000,B00100,B00010,B11111,B00010,B00100,B00000,B00000};
uint8_t rightChar[8] = {B00000,B00100,B01000,B11111,B01000,B00100,B00000,B00000};
uint8_t stopChar[8]  = {B00000,B00000,B01110,B01110,B01110,B00000,B00000,B00000};
uint8_t heart[8]     = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t clock[8] = {0x0,0xe,0x15,0x17,0x11,0xe,0x0};
uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
// uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
// uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
// uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
// uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
// uint8_t retarrow[8] = {0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

void setup() {
  // LCD Setup
  lcd.begin (16, 2);
  // lcd.backlight();

  // LCD Display configuration
  lcd.createChar(1, upChar);
  lcd.createChar(2, downChar);
  lcd.createChar(3, leftChar);
  lcd.createChar(4, rightChar);
  lcd.createChar(5, stopChar);
  lcd.createChar(6, heart);
  lcd.createChar(7, clock);
  lcd.createChar(8, bell);

  lcd.home();

  lcd.print("Miguel Robot");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");

  // System setup
  /* Serial for PC communication Initialization */
  Serial.begin(9600);
  while (!Serial) {
    // wait serial port initialization
  }

  /* uBox objects initialization **********************/
  engines.setSpeed(MIN_SPEED);

  // Associate callbacks events to classes
  command.eventDisplay(onDisplay);
  command.eventDisplayLine(onDisplayLine1);
  engines.eventDisplayLine(onDisplayLine1);
  sensors.eventDisplayLine(onDisplayLine2);

  sensors.setLDRState(OFF);
  sensors.setUltrasonicState(OFF);

  /****************************************************/
  // end - System setup

  delay(500);
  lcd.clear();
  lcd.print("      mBox      ");
  lcd.setCursor(11, 0);
  lcd.write(6);

  // Set to automactic mode
  // command.setMode(AUTO);
}

void loop() {
  command.process();
  sensors.process();
  head.process();
  engines.process();
}

// Print information on LCD Display
void onDisplay(const char *line1, const char *line2) {
  onDisplayLine1(line1);
  onDisplayLine2(line2);
}

// Print information on first line of LCD Display
void onDisplayLine1(const char *value) {
  lcd.setCursor(0, 0);
  lcd.print("                ");
  lcd.setCursor(0, 0);
  lcd.print(value);
  Serial.print("Display Line1: ");
  Serial.println(value);
}

// Print information on second line of LCD Display
void onDisplayLine2(const char *value) {
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  lcd.print(value);
  Serial.print("Display Line2: ");
  Serial.println(value);
}
