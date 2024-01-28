 #include <AFMotor.h>
 #include <PID_v1.h>

 double setpoint = 0.0; //center of the line
 double input = 0.0; //current sensor reading
 double output = 0.0; //output after pid calculation
 double kp = 1.0;
 double ki = 0.1;
 double kd = 0.01;
 int const base_speed = 150;

 PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);
  
  AF_DCMotor motor_right(1);
  AF_DCMotor motor_left(4);
  
  int ir_in_left = A5;
  int ir_in_right = A0;

void setup() {
  Serial.begin(9600);
  pinMode(ir_in_left, INPUT);
  pinMode(ir_in_right, INPUT);
  pid.SetMode(AUTOMATIC);
  pid.SetOutputLimits(0, 255);
}

void loop() {
  // put your main code here, to run repeatedly:
  int irLeftVal = digitalRead(ir_in_left);
  int irRightVal = digitalRead(ir_in_right);

  int irLeftValNorm = map(irLeftVal, LOW, HIGH, -1, 1);
  int irRightValNorm = map(irRightVal, LOW, HIGH, -1, 1);

  input = irLeftValNorm - irRightValNorm;
  


  if(irLeftVal==HIGH && irRightVal==HIGH){
    motor_left.setSpeed(base_speed);
    motor_right.setSpeed(base_speed);
    motor_left.run(FORWARD);
    motor_right.run(FORWARD);
  }

  else{
   /* motor_left.run(BACKWARD);
    motor_right.run(BACKWARD);
    delay(50);*/
    if (irLeftVal==LOW && irRightVal==LOW){
    motor_right.run(RELEASE);
    motor_left.run(RELEASE);
  }

    else if(irLeftVal==HIGH && irRightVal==LOW){
    adjustMotors(output);
    motor_right.run(BACKWARD);
    motor_left.run(FORWARD);

  }

  else if(irLeftVal==LOW && irRightVal==HIGH){
    adjustMotors(output);
    motor_left.run(BACKWARD);
    motor_right.run(FORWARD);
  }
  }
}

void adjustMotors(double pidOutput){
 int base_speed = 150;
 motor_left.setSpeed(base_speed-pidOutput);
 motor_right.setSpeed(base_speed+pidOutput);
}