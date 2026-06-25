//Motor Driver PIn Definitions

  const int enA=14;
  const int in1 = 27;
  const int in2 = 26;

  void setup()
  {
    //Serial Monitor
    Serial.begin(115200);

    delay(500);

    //Initialize Motor Driver Pins

    pinMode(enA,OUTPUT);
    pinMode(in1,OUTPUT);
    pinMode(in2,OUTPUT);

    //Start with motor off
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(enA,0);

    //Instructions to the user
    Serial.println("ESP 32 Trials");
    Serial.println("Type 'START' to turn motor on");
    Serial.println("Type 'STOP' to turn motor off");

  }

  void loop()
  {

    if (Serial.available() >0) //checking if user has typed anything in the Serial Monitor
    {
      String command = Serial.readStringUntil('\n');

      command.trim();
      command.toUpperCase();

      //clean up the string - not following the instructions

      Serial.print("Command Received: ");
      Serial.println(command);

      //Motor Logic

      if (command=="START")
      {
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        analogWrite(enA,200);
        Serial.println("Motor is Running");
      }

      else if (command=="STOP")
      {
        digitalWrite(in1,LOW);
        digitalWrite(in2,LOW);
        analogWrite(enA,0);
        Serial.println("Motor is not Running");
      }

      else
      {
        Serial.println("Unknown command typed");
      }
    }
  }