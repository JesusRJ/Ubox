/**
 * uBox Head Controller
 * Controla os sensores e motores de posicionamento da cabeça do robô.
 *
 * O motor de passo 28BYJ-48 precisa de 4097 passos pra uma volta completa.
 * 
 * https://github.com/JesusRJ/ubox
 *
 * @author Reginaldo Jesus
 * @version 1.0 09/10/2015
 */
#include <Button.h>

#define MAX_STEPS_V 500
#define MAX_STEPS_H 500
#define LDR_PORT    A5
#define BTNV_PORT   2

Button btnPositions = Button(BTNV_PORT, BUTTON_PULLUP_INTERNAL, true, 5);

unsigned int vMotor[4] = { 5, 6, 7, 8};
unsigned int hMotor[4] = { 9, 10, 11, 12};

int Steps = 0;
boolean Direction = true;
boolean running = true;
unsigned long last_time;
unsigned long currentMillis ;

int steps_default = MAX_STEPS_V;
int steps_left = steps_default;
int ldrSensorReading;
unsigned int led_state = LOW;

void setup() {
  Serial.begin(9600);

  pinMode(vMotor[0], OUTPUT);
  pinMode(vMotor[1], OUTPUT);
  pinMode(vMotor[2], OUTPUT);
  pinMode(vMotor[3], OUTPUT);
  
  // Assign callback function btnPositions
  btnPositions.pressHandler(onPress);
}

void loop() {
  btnPositions.process();
  
  ldrSensorReading = analogRead(LDR_PORT);
  ldrSensorReading = map(ldrSensorReading, 0, 1023, 0, 255);
  
  if (running && steps_left>0) {
    currentMillis = micros();
    
    if(currentMillis-last_time>=1000){
    
      setStep(vMotor);
      setDirection(); 
      
      last_time=micros();
      
      steps_left--;
      
      if (steps_left <= 0) {
        steps_left = steps_default;
        Direction=!Direction;
      }
    }
  }
}

void onPress(Button& b){
  // reverse the LED 
  led_state = !led_state;
  digitalWrite(13, led_state);
  
  Direction=!Direction;
  running=!running;
  
  steps_default = MAX_STEPS_V / 2;
  
  if (!running) {
    delay(5000);
    running = true;
  }
}

void setStep(int motor[]) {
  switch(Steps) {
  case 0:
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], HIGH);
    break; 
  case 1:
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], HIGH);
    digitalWrite(motor[3], HIGH);
    break; 
  case 2:
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], HIGH);
    digitalWrite(motor[3], LOW);
    break; 
  case 3:
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], HIGH);
    digitalWrite(motor[2], HIGH);
    digitalWrite(motor[3], LOW);
    break; 
  case 4:
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], HIGH);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], LOW);
    break; 
  case 5:
    digitalWrite(motor[0], HIGH); 
    digitalWrite(motor[1], HIGH);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], LOW);
    break; 
  case 6:
    digitalWrite(motor[0], HIGH); 
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], LOW);
    break; 
  case 7:
    digitalWrite(motor[0], HIGH); 
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], HIGH);
    break; 
  default:
    digitalWrite(motor[0], LOW); 
    digitalWrite(motor[1], LOW);
    digitalWrite(motor[2], LOW);
    digitalWrite(motor[3], LOW);
    break; 
  }
}

void setDirection(){
  if(Direction==1){ 
    Steps++;
  }
  
  if(Direction==0){ 
    Steps--;
  }
  
  if(Steps>7){
    Steps=0;
  }
  
  if(Steps<0){
    Steps=7;
  }
}