#include <Ubox_Engines.h>

#define m1_pin1 4 
#define m1_pin2 5
#define m2_pin1 6
#define m2_pin2 7
#define m1_pin_enable 9
#define m2_pin_enable 10

uint8_t motor1[3] = { m1_pin1, m1_pin2, m1_pin_enable };
uint8_t motor2[3] = { m1_pin1, m1_pin2, m2_pin_enable };

Ubox_Engines engines(motor1, motor2);

void setup() {
  engines.setSpeed(255);
}

void loop() {

}
