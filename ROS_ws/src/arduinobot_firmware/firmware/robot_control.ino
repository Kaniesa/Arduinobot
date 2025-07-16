#include <Braccio.h>
#include <Servo.h>

Servo base; //0
Servo shoulder; //1
Servo elbow; //2
Servo wrist_rot; //3 --> wristpitch
Servo wrist_ver; //4 --> wristroll
Servo gripper; //5

uint8_t idx = 0;
uint8_t value_idx = 0;
char value[4] = "000";

// Braccio Current Positions (safety pos)
uint8_t base_curPos = 90;
uint8_t shoulder_curPos = 45;
uint8_t elbow_curPos = 180;
uint8_t wristpitch_curPos = 180;
uint8_t wristroll_curPos = 90;
uint8_t gripper_curPos = 10;

void reach_goal( int motor, int goal ){
  if( motor == 0){
    Braccio.ServoMovement(20, goal, shoulder_curPos, elbow_curPos, wristpitch_curPos, wristroll_curPos, gripper_curPos);
    base_curPos = goal;
  }
  else if( motor == 1){
    Braccio.ServoMovement(20, base_curPos, goal, elbow_curPos, wristpitch_curPos, wristroll_curPos, gripper_curPos);
    shoulder_curPos = goal;
  }
  else if( motor == 2){
    Braccio.ServoMovement(20, base_curPos, shoulder_curPos, goal, wristpitch_curPos, wristroll_curPos, gripper_curPos);
    elbow_curPos = goal;
  }
  else if( motor == 3){
    Braccio.ServoMovement(20, base_curPos, shoulder_curPos, elbow_curPos, goal, wristroll_curPos, gripper_curPos);
    wristpitch_curPos = goal;
  }
  else if( motor == 4){
    Braccio.ServoMovement(20, base_curPos, shoulder_curPos, elbow_curPos, wristpitch_curPos, goal, gripper_curPos);
    wristroll_curPos = goal;
  }
  else if( motor == 5){
    Braccio.ServoMovement(20, base_curPos, shoulder_curPos, elbow_curPos, wristpitch_curPos, wristroll_curPos, goal);
    gripper_curPos = goal;
  }
  
}

void setup() {

  Braccio.begin();
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
        reach_goal(idx, val);
      }
      else if(idx == 1){
        reach_goal(idx, val);
      }
      else if(idx == 2){
        reach_goal(idx, val);
      }
      else if(idx == 3){
        reach_goal(idx, val);
      }
      else if(idx == 4){
        reach_goal(idx, val);
      }
      else if(idx == 5){
        reach_goal(idx, val);
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
