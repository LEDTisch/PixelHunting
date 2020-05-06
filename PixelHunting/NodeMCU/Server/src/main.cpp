#include <Arduino.h>
#include <ESP8266WiFi.h>
const char *ssid = "WLANbridge";
const char *password = "Pi-Server";


int myposx = 0;
int myposy = 0;
int thierposx = 0;
int thierposy = 0;
 
WiFiServer wifiServer(1234);
void setup() {
  Serial.begin(9600);
   WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
   
  }
   wifiServer.begin();
}


void settheirspos(int x, int y)
{
  Serial.print("o");
  delay(2);
  Serial.print("x");
  delay(2);
  Serial.print(x);
  delay(2);
  Serial.print("y");
  delay(2);
  Serial.print(y);
  delay(2);
  Serial.print("e");
}

void setmyspos(int x, int y)
{
  Serial.print("m");
  delay(2);
  Serial.print("x");
  delay(2);
  Serial.print(x);
  delay(2);
  Serial.print("y");
  delay(2);
  Serial.print(y);
  delay(2);
  Serial.print("e");
}

void sethunter(boolean isthisclienthunter)
{
  Serial.print("h");

  if (isthisclienthunter)
  {
    Serial.print(1);
  }
  else
  {
    Serial.print(0);
  }

  Serial.print("e");
}

void loop() {
  String string="";
  char c=2;
  if (Serial.available())
  
  {

    while (c != 'e')
    {
      delay(2);
      
      c = Serial.read();

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



   WiFiClient client = wifiServer.available();
char t=2;
String test;
   if(client) {
     if(client.available()>0)  {
       while(c!='e') {
         delay(2);
          t=client.read();
         test+=t; 
         setmyspos(3,3);
         delay(12);
       }

       

            
        

       //Handel

       test ="";
     }
   }

  //sethunter(false);
 
  delay(500);
}