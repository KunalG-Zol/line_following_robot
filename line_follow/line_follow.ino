//including the libraries
#include <AFMotor.h>

//defining pins and variables
#define RIGHT_IRS A0
#define LEFT_IRS A5

//defining motors
AF_DCMotor RIGHT_MOTOR(1, 120); 
AF_DCMotor LEFT_MOTOR (4, 120);

int motor_speed = 80;

bool on_white(int ir_value){
  if (ir_value < 450){
    return true;
  }
  else {
    return false;
  }
}

void setup() {

  LEFT_MOTOR.setSpeed(motor_speed);
  RIGHT_MOTOR.setSpeed(motor_speed);

  pinMode(LEFT_IRS, INPUT);
  pinMode(RIGHT_IRS, INPUT);

  Serial.begin(9600);
}

void loop(){
  int turn_delay = 500;

  int ir_left,ir_right;
  ir_right = analogRead(rightLS);
  ir_left = analogRead(leftLS);
  bool left_on_white = on_white(ir_left);
  bool right_on_white = on_white(ir_right);
  
  Serial.print("right=");
  Serial.println(ir_right);
  Serial.print("left=");
  Serial.println(ir_left);
  delay(500);
  
  //Forward
  if( left_on_white && right_on_white){
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);
  }
  
  //turn left
  if ( !(left_on_white) && right_on_white){
    motor_right.run(FORWARD);
    motor_left.run(RELEASE);
    delay(turn_delay);
  }

  //turn right
  if( left_on_white && !(right_on_white)){
    motor_right.run(RELEASE);
    motor_left.run(FORWARD);
    delay(turn_delay);
  }

  //stop
  if(!(left_on_white && right_on_white)){
    motor_right.run(RELEASE);
    motor_left.run(RELEASE);   
  }
}