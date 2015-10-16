#define motor1pole1 4 
#define motor1pole2 5
#define motor2pole1 6
#define motor2pole2 7

// map L293d motor enable pins to Arduino pins
#define enablePin1 9
#define enablePin2 10

#define M1_MAX_SPEED 255
#define M2_MAX_SPEED 255

#define motordelay 30
#define debugmotorsec 3000

int mspeed = 115;  // pick a starting speed up to 255

void setup() {
  Serial.begin(9600);

  // set mapped L293D motor1 and motor 2 enable pins on Arduino to output (to turn on/off motor1 and motor2 via L293D)
  pinMode(enablePin1, OUTPUT);
  pinMode(enablePin2, OUTPUT);

  // set mapped motor poles to Arduino pins (via L293D)
  pinMode( motor1pole1, OUTPUT);
  pinMode( motor1pole2, OUTPUT);
  pinMode( motor2pole1, OUTPUT);
  pinMode( motor2pole2, OUTPUT);
  motorspeed(0, 0);
}

void loop() {
  // set speed of motor 1 and 2 to same speed
  motorspeed(mspeed, mspeed);

  // spin motor 1 only in one direction
  Serial.print("MOTOR 1 FORWARD @ SPEED: ");  
  Serial.println(mspeed);
  motorforward(1);
  delay(debugmotorsec);
  motorstop(1);

  // spin motor 2 only in one direction
  Serial.print("MOTOR 2 FORWARD @ SPEED: ");  
  Serial.println(mspeed);
  motorforward(2);
  delay(debugmotorsec);
  motorstop(2);

  // spin motor 1 only in opposite direction
  Serial.print("MOTOR 1 BACK @ SPEED: ");  
  Serial.println(mspeed);
  motorback(1);
  delay(3000);
  motorstop(1);

  // spin motor 2 only in opposite direction
  Serial.print("MOTOR 2 BACK @ SPEED: ");   
  Serial.println(mspeed);
  motorback(2);
  delay(debugmotorsec);
  motorstop(2);

  // stop both motors 1 and 2
  Serial.println("BOTH MOTORS STOP FOR 2 SEC.");
  motorstop(1);
  motorstop(2);
  delay(2000);

  // spin both motors in one direction
  Serial.print("BOTH MOTORS FORWARD @ SPEED: ");
  Serial.println(mspeed);
  motorforward(1);
  motorforward(2);
  delay(debugmotorsec);

  // stop both motors
  Serial.println("BOTH MOTORS STOP FOR 2 SEC."); 
  motorstop(1);
  motorstop(2);

  delay(2000);
  // spin both motors in opposite direction
  Serial.print("BOTH MOTORS BACK @ SPEED: ");
  Serial.println(mspeed);
  motorback(1);
  motorback(2);
  delay(debugmotorsec);

  // stop both motors
  Serial.println("BOTH MOTORS STOP FOR 2 SEC.");
  motorstop(1);
  motorstop(2);
  delay(2000);

  // spin both motors but in opposite directions
  Serial.print("MOTOR1 FORWARD | MOTOR2 BACK @ SPEED: "); 
  Serial.println(mspeed);
  motorforward(1);
  motorback(2);
  delay(debugmotorsec);

  // stop both motors
  Serial.println("BOTH MOTORS STOP FOR 2 SEC.");
  motorstop(1);
  motorstop(2);
  delay(2000);

  // spin both motors in the other opposite direction
  Serial.print("MOTOR1 BACK | MOTOR2 FORWARD @ SPEED: ");
  Serial.println(mspeed);
  motorback(1);
  motorforward(2);
  delay(debugmotorsec);

  // stop both motors
  Serial.println("BOTH MOTORS STOP FOR 2 SEC.");
  motorstop(1);
  motorstop(2);
  delay(2000);

  mspeed += 50;  // add 50 to speed of motor spin. Max speed 255

  // set speed of motor 1 and 2 to same new speed
  motorspeed(mspeed,mspeed);
}

// MOTOR FUNCTIONS

void motorstop(int motornum){
  delay(motordelay);
  if (motornum == 1) {
    digitalWrite(motor1pole1, LOW);
    digitalWrite(motor1pole2, LOW);
  }
  else if (motornum == 2) {

    digitalWrite(motor2pole1, LOW);
    digitalWrite(motor2pole2, LOW);
  }
  delay(motordelay);
}

void motorforward(int motornum){
  if (motornum == 1) {
    digitalWrite(motor1pole1, HIGH);
    digitalWrite(motor1pole2, LOW);
  }
  else if (motornum == 2) {

    digitalWrite(motor2pole1, LOW);
    digitalWrite(motor2pole2, HIGH);
  }
  delay(motordelay);
}

void motorback(int motornum){
  if (motornum == 1) {
    digitalWrite(motor1pole1, LOW);
    digitalWrite(motor1pole2, HIGH);
  } 
  else if (motornum == 2) {
    digitalWrite(motor2pole1, HIGH);
    digitalWrite(motor2pole2, LOW);
  }
  delay(motordelay);
}

void motorspeed(int motor1speed, int motor2speed) {
  if (motor1speed > M1_MAX_SPEED ) motor1speed = M1_MAX_SPEED; // limit top speed
  if (motor2speed > M2_MAX_SPEED ) motor2speed = M2_MAX_SPEED; // limit top speed
  if (motor1speed < 0) motor1speed = 0; // keep motor above 0
  if (motor2speed < 0) motor2speed = 0; // keep motor speed above 0
  
  //analogWrite(enablePin1, motor1speed);
  //analogWrite(enablePin2, motor2speed);
  
  analogWrite(enablePin1, 255);
  analogWrite(enablePin2, 255);
}