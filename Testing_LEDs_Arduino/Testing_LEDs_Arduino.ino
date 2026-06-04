const int LED1_Pin=3;

const int button1_Pin=2;

int button1_state=0;

void setup() {
	// Initialize serial communication - allows printing to the console for debugging.
	Serial.begin(9600);
	pinMode(LED1_Pin, OUTPUT); // Set the LED anode pin as an output
  pinMode(button1_Pin, INPUT); //Set the Button pin as an input
}


void loop() {

  //Read Button State
  button1_state = digitalRead(button1_Pin);

 if (button1_state==HIGH)
{
   Serial.println("Button is Pressed"); //Print a meassage to the output terminal
    digitalWrite(LED1_Pin, HIGH); // Turn the LED on
  
}
 else
{
   Serial.println("Button is no longer Pressed"); //Print a meassage to the output terminal
    digitalWrite(LED1_Pin, LOW); // Turn the LED off
}
   delay(100); // Small delay to avoid spamming the serial controller
}

 
