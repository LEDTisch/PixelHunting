#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <SoftwareSerial.h>
SoftwareSerial softwareserial(13,15,false);

const char *ssid = "lap";
const char *password = "##Pilatus.b4##pi!?";
const uint16_t port = 1234;
const char *host = "79.231.224.114";

int myposx = 0;
int myposy = 5;
int thierposx = 0;
int thierposy = 0;

      WiFiClient client;


void setup()
{
  pinMode(LED_BUILTIN,OUTPUT);
                                digitalWrite(LED_BUILTIN,HIGH);
  softwareserial.begin(9600);

 

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED)
  {
   delay(100);
  }

     /*while (!client.connect(host, port)) {
 

    }
    client.write("ge");

    client.flush();*/
}
void settheirspos(int x, int y)
{
  thierposx=x;
  thierposy=y;
    String eins="T1";
  String zwei=" X";
  String drei=" Y";
  String senden=eins+zwei+thierposx+drei+thierposy;
    softwareserial.println(senden);
}

void setmyspos(int x, int y)
{
  myposx=x;
  myposy=y;
  String eins="T0";
  String zwei=" X";
  String drei=" Y";
  String senden=eins+zwei+myposx+drei+myposy;
    softwareserial.println(senden);
}

void sethunter(boolean isthisclienthunter)
{
 
}

void EthernetConnection(){
 


    if(client.available()){
      client.read();
    }
 

}

void loop()
{
  //EthernetConnection();

  String string="";
  char c=2;
  if (softwareserial.available())
  
  {

  }

  //sethunter(false);
  //settheirspos(9, 9);
 // delay(500);
setmyspos(0,0);
//settheirspos(5,6);
delay(200);
settheirspos(0,1);
delay(200);




}