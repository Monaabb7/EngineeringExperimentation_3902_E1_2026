#include <WiFi.h>
#include <WiFiUdp.h>
//Wifi config

  const char* ssid="ESP32_Control";
  const int localPort = 5005;

//Motor Driver Pin Definitions

  const int enA = 14;
  const int in1 = 27;
  const int in2 = 26;

  WiFiUDP udp;
  char packetBuffer[255];

  void setup()
  {
    //Serial Monitor
    Serial.begin(115200);

    delay(500);

    // Configure Wi-Fi Access Point
    WiFi.mode(WIFI_AP);
    bool success = WiFi.softAP(ssid, NULL, 1);

    if (success){
      Serial.println("Access Point successfully started!");
      Serial.print("SSID: ");
      Serial.println(ssid);
      Serial.print("AP IP Address: ");
      Serial.println(WiFi.softAPIP()); //Should be 192.168.4.1
    } 
    else{
      Serial.println("Failed to start Access Point");

    } 
    
    //Start listening for UDP packets from MATLAB
    udp.begin(localPort);
    Serial.printf("Listening on UDP port %d\n", localPort);


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

    //if (Serial.available() >0) //checking if user has typed anything in the Serial Monitor
    {
      // String command = Serial.readStringUntil('\n');

      // command.trim();
      // command.toUpperCase();

      // //clean up the string - not following the instructions

      // Serial.print("Command Received: ");
      // Serial.println(command);

      // //Motor Logic

      int packetSize = udp.parsePacket();

      if (packetSize)
      {
        int len=udp.read(packetBuffer, 255);
        if(len>0)
        {
          packetBuffer[len]=0;
        }
      }

      String command = String(packetBuffer);
      command.trim();

      //char command = Serial.read();

      if (command=="1")
      {
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        analogWrite(enA,20);
        Serial.println("Motor is Running");
      }

      else if (command=="0")
      {
        digitalWrite(in1,LOW);
        digitalWrite(in2,LOW);
        analogWrite(enA,0);
        Serial.println("Motor is not Running");
      }

      // else
      // {
      //   Serial.println("Unknown command typed");
      // }
    }
  }