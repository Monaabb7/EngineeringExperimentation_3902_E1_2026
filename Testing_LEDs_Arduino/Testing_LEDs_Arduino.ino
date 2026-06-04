



void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
	pinMode(2, OUTPUT); // Set the LED anode pin as an output
}


void loop() {
  digitalWrite(2, HIGH); // Turn the LED on
  delay(1000); // Wait for 1 second
  digitalWrite(2, LOW); // Turn the LED off
  delay(1000); // Wait for 1 second before repeating
}


 
