#include <Stepper.h>
  //1.8 degree step angle = 200 steps per revolution

  const int StepsPerRevolution = 200;

  //Initializing Stepper Library 
  //(steps,AIN1,AIN2, BIN1,BIN2)
  Stepper nema17Stepper(StepsPerRevolution,5,4,6,7);

void setup() {
  // put your setup code here, to run once:

  //Set the motor speed in rpm
  nema17Stepper.setSpeed(10);

  Serial.begin (9600);

  Serial.println("NEMA 17 is initialized with TB6612");

}

void loop() {
  // put your main code here, to run repeatedly:

  Serial.println("Moving Clockwise");
  nema17Stepper.step(StepsPerRevolution);
  delay(1000); //Pause for one second

  Serial.println("Moving CCW");
  nema17Stepper.step(-StepsPerRevolution);
  delay(1000);

}
