//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define RIGHT_IRS A0
#define LEFT_IRS A5

//defining motors
AF_DCMotor RIGHT_MOTOR(1, 120); 
AF_DCMotor LEFT_MOTOR (4, 120);

int motor_speed = 60;
int move_for_ms = 100;

bool on_white(int ir_value){
  if (ir_value < 450){
    return true;
  }
  else {
    return false;
  }
}

void start_moving(){
  LEFT_MOTOR.setSpeed(200);
  RIGHT_MOTOR.setSpeed(200);
  LEFT_MOTOR.run(FORWARD);
  RIGHT_MOTOR.run(FORWARD);
  delay(10);
  LEFT_MOTOR.setSpeed(motor_speed);
  RIGHT_MOTOR.setSpeed(motor_speed);
}

void go_forward(){
  start_moving();
  delay(move_for_ms);  
}

void go_left(){
  Serial.println("going left");
  start_moving();
  LEFT_MOTOR.run(RELEASE);
  delay(move_for_ms);
}
void go_right(){
  Serial.println("going right");
  start_moving();
  LEFT_MOTOR.run(RELEASE);
  delay(move_for_ms);
}

void setup() {
  LEFT_MOTOR.setSpeed(motor_speed);
  RIGHT_MOTOR.setSpeed(motor_speed);
  pinMode(LEFT_IRS, INPUT);
  pinMode(RIGHT_IRS, INPUT);
  Serial.begin(9600);
}

void loop(){
  int right_ir_val, left_ir_val;
  left_ir_val = analogRead(LEFT_IRS);
  right_ir_val = analogRead(RIGHT_IRS);
  bool left_on_white = on_white(right_ir_val);
  bool right_on_white = on_white(left_ir_val);
  
  // Serial.print("left=");
  // Serial.println(left_ir_val);
  // Serial.print("right=");
  // Serial.println(right_ir_val);
  // delay(500);
  
  //Forward
  if( left_on_white && right_on_white){
  go_forward();
  }
  
  //turn left
  if ( !(left_on_white) && right_on_white){
    go_left();
  }

  //turn right
  if( left_on_white && !(right_on_white)){
    go_right();
  }

  //stop
  if(!(left_on_white && right_on_white)){
    RIGHT_MOTOR.run(RELEASE);
    LEFT_MOTOR.run(RELEASE);   
  }
}