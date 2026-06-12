
// Include Libraries
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_VL53L0X.h"
#include "Adafruit_SSD1306.h"
#include "Adafruit_GFX.h"

//OLED Display Settings

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_VL53L0X ToF;

// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin2 = 3; // Pin that triggers the ultrasonic pulse
const int echoPin2 = 4; // Pin that receives the echo signal

//Define pin for IR sensor
const int irPin = A0;

// Variables to store the pulse duration and calculated distance
float duration2, distance2;
float distanceToF;
float distanceIR;

// Global variables and defines

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(115200);
  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin2, OUTPUT); // Set trigger pin as output
  pinMode(echoPin2, INPUT);  // Set echo pin as input

  //OLED Setup

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println("SSD1306 Allocation failed");
    while (true);
  }

  // ToF Setup

  if(!ToF.begin())
  {
    Serial.println("VL53L0X failed");
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
  

  //Display on OLED

  display.clearDisplay();
  display.setTextSize(1);

  display.setCursor(0,0);

  display.println("Ultrasonic");

  display.setCursor(0,20);
  display.println("Distance: ");
  display.print(distance2);

  display.println(" cm");
  
  display.display();

  delay(100);

}


 


