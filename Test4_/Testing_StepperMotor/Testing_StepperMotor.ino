#include <Stepper.h>
  //1.8 degree step angle = 200 steps per revolution

  const int StepsPerRevolution = 200;

  //Initializing Stepper Library 
  //(steps, AIN1, AIN2, BIN1, BIN2)
  Stepper nema17Stepper(StepsPerRevolution,5,4,6,7);

  int sensor2 =2; // sensor pin
  int val2; // 0: Magnetic field detected, 1: No magnetic field detected


void setup() {
  // put your setup code here, to run once:

  //Set the motor speed in rpm
  nema17Stepper.setSpeed(10);

  Serial.begin (9600);

  Serial.println("NEMA 17 is initialized with TB6612");

    pinMode(sensor2, INPUT); // set sensor pin as input
}

void loop() {
  // put your main code here, to run repeatedly:

  //Serial.println("Moving Clockwise");
 // nema17Stepper.step(StepsPerRevolution);
  //delay(1000); //Pause for one second

  //Serial.println("Moving Counter Clock Wise");
  //nema17Stepper.step(-StepsPerRevolution);
  //delay(1000);

  val2 = digitalRead(sensor2); //Read the sensor

  if(val2==1){
    Serial.println("Magnet Not Detected");
  }
  else{
    Serial.println("Magnet Detected");
  }

  Serial.print("ky003 value: ");
  Serial.println(val2);
  
  delay(1000);
}
