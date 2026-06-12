// Include Libraries
#include "Wire.h"
#include "Adafruit_VL53L0X.h"
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"

// Object initialization
SSD1306AsciiWire display;   // OLED (I2C addr 0x3C, shares A4/A5 with the ToF)
Adafruit_VL53L0X ToF;       // Time of Flight sensor (I2C addr 0x29)

// Global variables and pin definitions
// Define the pins for the HC-SR04 sensor
const int trigPin2 = 3; // Pin that triggers the ultrasonic pulse
const int echoPin2 = 4; // Pin that receives the echo signal

// Define the pin for the IR obstacle module (digital output, active-LOW)
const int irPin = 5;

// Variables to store the pulse duration and calculated distances
long duration2;         // ultrasonic echo time in microseconds
float distance2;        // ultrasonic distance in cm
float distanceToF;      // time of flight distance in cm
bool irDetected;        // IR module: true = object detected


void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	// 115200 baud: set the Serial Monitor and CoolTerm to match.
	Serial.begin(115200);
  Wire.begin(); // initialize Wire library (default 100 kHz - this OLED panel

  // Setup function: runs once at startup
  // Configure the trigger pin as an OUTPUT and the echo pin as an INPUT
  pinMode(trigPin2, OUTPUT); // Set trigger pin as output
  pinMode(echoPin2, INPUT);  // Set echo pin as input

  // IR pin uses the internal pullup so a loose wire reads as "clear"
  // instead of a false permanent detect
  pinMode(irPin, INPUT_PULLUP);

  // OLED Setup (SSD1306Ascii: no framebuffer, prints go straight to the screen)

  display.begin(&Adafruit128x64, 0x3C);
  display.setFont(System5x7);
  display.clear();
  display.println(F("Test 3: 3 sensors"));

  // ToF Setup

  if(!ToF.begin())
  {
    Serial.println(F("VL53L0X failed"));
    display.println(F("ToF FAIL"));
    while (true);
  }

  // CSV heading with commas for Excel import - printed ONCE here in setup,
  // not in loop, so the captured file has a single header row
  Serial.println(F("time_ms,tof_cm,ultrasonic_cm,ir_detected"));
}


void loop() {
  // Main loop: continuously measures distance with all three sensors

  // ---------------- Ultrasonic measurement ----------------

  // Ensure the trigger pin is LOW to start
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2); // Short delay to allow sensor stabilization

  // Trigger the sensor by sending a HIGH pulse for 10 microseconds
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10); // Pulse duration
  digitalWrite(trigPin2, LOW);

  // Read the duration of the echo pulse (in microseconds)
  // 30 ms timeout so a missed echo does not freeze the loop for a second
  duration2 = pulseIn(echoPin2, HIGH, 30000UL);

  // Calculate the distance (cm) using the speed of sound (0.0343 cm/us)
  // Dividing by 2 accounts for the round-trip distance
  if (duration2 > 0) {
    distance2 = (duration2 * 0.0343) / 2;
  } else {
    distance2 = -1; // -1 means no echo / out of range
  }

  // ---------------- Time of Flight measurement ----------------

  VL53L0X_RangingMeasurementData_t measure;
  ToF.rangingTest(&measure, false);  // false = no debug printout

  if (measure.RangeStatus != 4) {            // 4 means out of range
    distanceToF = measure.RangeMilliMeter / 10.0; // convert mm to cm
  } else {
    distanceToF = -1;
  }

  // ---------------- IR measurement ----------------

  // Module is active-LOW: output goes LOW when an object is detected,
  // so invert the reading to get a friendly true = detected
  irDetected = !digitalRead(irPin);

  // ---------------- Output to the Serial Monitor (CSV) ----------------

  Serial.print(millis());
  Serial.print(',');
  Serial.print(distanceToF, 1);
  Serial.print(',');
  Serial.print(distance2, 1);
  Serial.print(',');
  Serial.println(irDetected ? 1 : 0);

  // ---------------- Display on OLED ----------------

  // No clearDisplay()/display() pair with this library: move the cursor to
  // each row and overwrite it; clearToEOL() wipes leftover characters

  display.setCursor(0, 2); // row units are 8-pixel text rows
  display.print(F("ToF: "));
  display.print(distanceToF, 1);
  display.print(F(" cm"));
  display.clearToEOL();

  display.setCursor(0, 4);
  display.print(F("US : "));
  display.print(distance2, 1);
  display.print(F(" cm"));
  display.clearToEOL();

  display.setCursor(0, 6);
  display.print(F("IR : "));
  if (irDetected) {
    display.print(F("DETECT"));
  } else {
    display.print(F("CLEAR"));
  }
  display.clearToEOL();

  // Short delay before the next measurement (~10 samples per second)
  delay(100);
}
