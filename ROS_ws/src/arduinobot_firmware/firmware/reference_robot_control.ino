// NOTE: NOT GOING TO BE USED BECAUSE BRACCIO HAS OWN LIBRARY.
// this is just made for reference

#include <Servo.h>

#define SERVO_BASE_PIN 8
#define SERVO_SHOULDER_PIN 9
#define SERVO_ELBOW_PIN 10
#define SERVO_WRISTPITCH_PIN 11
#define SERVO_WRISTROLL_PIN 12
#define SERVO_GRIPPER_PIN 7

#define BASE_START 90
#define SHOULDER_START 90
#define ELBOW_START 90
#define WRISTPITCH_START 90
#define WRISTROLL_START 90
#define GRIPPER_START 10

Servo base;
Servo shoulder;
Servo elbow;
Servo wristpitch;
Servo wristroll;
Servo gripper;

uint8_t idx = 0;
uint8_t value_idx = 0;
char value[4] = "000";

void reach_goal( Servo& motor, int goal ){
  if( goal >= motor.read() ){
    for( int pos = motor.read(); pos <= goal; pos++ ){
      motor.write(pos);
      delay(5);
    }
  }
  else{
    for( int pos = motor.read(); pos >= goal; pos-- ){
      motor.write(pos);
      delay(5);
    }
  }
}

void setup() {

  base.attach(SERVO_BASE_PIN);
  shoulder.attach(SERVO_SHOULDER_PIN);
  elbow.attach(SERVO_ELBOW_PIN);
  wristpitch.attach(SERVO_WRISTPITCH_PIN);
  wristroll.attach(SERVO_WRISTROLL_PIN);
  gripper.attach(SERVO_GRIPPER_PIN);

  base.write(BASE_START);
  shoulder.write(SHOULDER_START);
  elbow.write(ELBOW_START);
  wristpitch.write(WRISTPITCH_START);
  wristroll.write(WRISTROLL_START);
  gripper.write(GRIPPER_START);

  Serial.begin(115200);
  Serial.setTimeout(1);
}

void loop() {

  if(Serial.available()){
    char chr = Serial.read();

    if(chr == 'b'){
      idx = 0;
      value_idx = 0;
    }
    else if( chr == 's'){
      idx = 1;
      value_idx = 0;
    }
    else if( chr == 'e'){
      idx = 2;
      value_idx = 0;
    }
    else if( chr == 'p'){
      idx = 3;
      value_idx = 0;
    }
    else if( chr == 'r'){
      idx = 4;
      value_idx = 0;
    }
    else if( chr == 'g'){
      idx = 5;
      value_idx = 0;
    }
    else if( chr == ','){
      int val = atoi( value );
      if(idx == 0 ){
        reach_goal(base, val);
      }
      else if(idx == 1){
        reach_goal(shoulder, val);
      }
      else if(idx == 2){
        reach_goal(elbow, val);
      }
      else if(idx == 3){
        reach_goal(wristpitch, val);
      }
      else if(idx == 4){
        reach_goal(wristroll, val);
      }
      else if(idx == 5){
        reach_goal(gripper, val);
      }

      value[0] = '0';
      value[1] = '0';
      value[2] = '0';
      value[3] = '\0';
    }
    else{
      value[value_idx] = chr;
      value_idx++;
    }
  }
}
