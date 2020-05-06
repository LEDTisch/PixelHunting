#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "SoftwareSerial.h"

SoftwareSerial ConnectionSerial(3, 1);

const char *ssid = "WLANbridge";
const char *password = "Pi-Server";
const uint16_t port = 8090;
const char *host = "192.168.1.83";

int myposx = 0;
int myposy = 0;
int thierposx = 0;
int thierposy = 0;
void setup() {
  ConnectionSerial.begin(9600);
 Serial.begin(9600);
   WiFi.begin(ssid, password);
}


void settheirspos(int x, int y)
{
  ConnectionSerial.print("o");
  delay(2);
  ConnectionSerial.print("x");
  delay(2);
  ConnectionSerial.print(x);
  delay(2);
  ConnectionSerial.print("y");
  delay(2);
  ConnectionSerial.print(y);
  delay(2);
  ConnectionSerial.print("e");
}

void setmyspos(int x, int y)
{
  ConnectionSerial.print("m");
  delay(2);
  ConnectionSerial.print("x");
  delay(2);
  ConnectionSerial.print(x);
  delay(2);
  ConnectionSerial.print("y");
  delay(2);
  ConnectionSerial.print(y);
  delay(2);
  ConnectionSerial.print("e");
}

void loop() {
  String string="";
  char c=2;
  if (ConnectionSerial.available())
  
  {

    while (c != 'e')
    {
      delay(2);
      
      c = ConnectionSerial.read();

      string += c;
    }

    


    
    if (string.startsWith("x"))
    {

      int indexend = string.indexOf("e");
      myposx = string.substring(1, indexend).toInt();
    }

    if (string.startsWith("y"))
    {
      
      int indexend = string.indexOf("e");
      myposy = string.substring(1, indexend).toInt();
       delay(500);
    setmyspos(1,1);
    }
   
   
    //Handel input

    string = "";
  }

  WiFiClient client;
  //sethunter(false);
  //settheirspos(9, 9);
  delay(500);
}