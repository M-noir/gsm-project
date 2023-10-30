#include <SoftwareSerial.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino #2 & #3

void setup()
{
  //Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial.begin(9600);

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);
  delay(500);
  
  Serial.println("Initializing...");

  mySerial.println("AT"); //Once the handshake test is successful, i t will back to OK
  delay(50);
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  delay(50);
  updateSerial();

  mySerial.println("AT+CNMI=2,2,0,0,0"); // Configuring TEXT mode
  delay(50);
  updateSerial();

  mySerial.println("AT+CMGS=\"+250785097557\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  delay(50);
  updateSerial();

  mySerial.print("Hello There"); //text content
  mySerial.write(26);
  delay(50);
  updateSerial();


}


void loop()
{
  updateSerial();
}

void updateSerial()
{
  while (Serial.available())
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  
  while (mySerial.available())
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}