#include <Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//OLED Display Settings

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin2 = 4; // Pin that triggers the ultrasonic pulse
const int echoPin2 = 2; // Pin that receives the echo signal

// Variables to store the pulse duration and calculated distance
float duration2, distance2;
Servo myservo3;  // create servo object to control a servo
int pos3 = 0;    // variable to store the servo position


void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin2, OUTPUT); // Set trigger pin as output
  pinMode(echoPin2, INPUT);  // Set echo pin as input
  myservo3.attach(3);

  //OLED Setup

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 Allocation failed");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.display();
}


void loop() {
  // Main loop: continuously measures distance

  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2); // Short delay to allow sensor stabilization

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Pulse duration
  digitalWrite(trigPin2, LOW);

  // Read the duration of the echo pulse (in microseconds)
  duration2 = pulseIn(echoPin2, HIGH);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  distance2 = (duration2 * 0.0343) / 2;

  // Output the measured distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance2);

  // Short delay before the next measurement
  delay(100);  
  
  //adding in distance condition

  if(distance2 > 10 && distance2<=16)
  {
  
  for (pos3 = 0; pos3 <= 180; pos3 += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo3.write(pos3); // tell servo to go to position in variable 'pos'
    delay(15); // waits 15 ms for the servo to reach the position
  }
  for (pos3 = 180; pos3 >= 0; pos3 -= 1) { // goes from 180 degrees to 0 degrees
    myservo3.write(pos3); // tell servo to go to position in variable 'pos'
    delay(15); // waits 15 ms for the servo to reach the position
  }

  delay(1000);
  }

  //Display on OLED

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);

  display.println("Ultrasonic + Servo");

  display.setCursor(0,20);
  display.println("Distance: ");
  display.print(distance2);

  display.println(" cm");
  
  display.display();

  delay(100);

}


 
