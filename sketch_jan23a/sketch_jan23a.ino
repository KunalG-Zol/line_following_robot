  #include <AFMotor.h>
  
  AF_DCMotor motor_right(1);
  AF_DCMotor motor_left(4);
  
  int ir_in_left = A5;
  int ir_in_right = A0;

void setup() {
  Serial.begin(9600);
  motor_right.setSpeed(200);
  motor_left.setSpeed(200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int irLeftVal = analogRead(ir_in_left);
  int irRightVal = analogRead(ir_in_right);

  int irThreshold = 450;

  if(irLeftVal>irThreshold && irRightVal>irThreshold){
    motor_left.setSpeed(200);
    motor_right.setSpeed(200);
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
  }

  else if(irLeftVal<irThreshold && irRightVal>irThreshold){
    motor_left.setSpeed(120);
    motor_right.setSpeed(0);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);
  }

  else if(irLeftVal>irThreshold && irRightVal<irThreshold){
    motor_left.setSpeed(0);
    motor_right.setSpeed(120);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);
  }

  else{
    motor_left.setSpeed(200);
    motor_right.setSpeed(200);
    motor_right.run(FORWARD);
    motor_left.run(FORWARD);
  }
}
