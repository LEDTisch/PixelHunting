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
  Serial.begin(9600);
  pinMode(LED_BUILTIN,OUTPUT);
                                digitalWrite(LED_BUILTIN,HIGH);
  softwareserial.begin(9600);

 

  WiFi.begin(ssid, password);
Serial.println("\n\n\nVersuche mit wlan zu verbinden");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
   delay(100);
  }
  Serial.println("\nverbindung hergestellt");
        Serial.println("\nVerbindung mit host");

     while (!client.connect(host, port)) {
Serial.print(".");
    }
    Serial.println("\nverbunden");
    Serial.println("\nserverIP: ");
    Serial.print(client.remoteIP());
   

    client.write("Hallo Tim😎");

    client.write("ge");

    client.flush();

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



void sendmyPositiontoServer(){
      String eins="T1";
  String zwei=" X";
  String drei=" Y";
  String senden=eins+zwei+myposx+drei+myposy;
  client.print(senden);
    }


int iindex=0;
char CHAR;
const int MaxLength=15;
char message[MaxLength];

float getValue(char gcode){
  	char *ptr=message;
	
	while ((ptr>=message) && (ptr<(message+MaxLength))){	
		if (*ptr==gcode){
			return(atof(ptr+1));
		}
		ptr=strchr(ptr,' ')+1;
	}
	
	return(-1);	
}

void process(){
  int tcode=(int) getValue('T');
switch(tcode){
  case 0:
  myposx=(int)getValue('X');
  myposy=(int)getValue('Y');
  Serial.println(myposy);

  sendmyPositiontoServer();


  break;
  case 1:
  thierposx=(int)getValue('X');
  thierposy=(int)getValue('Y');
  break;
}
}


void loop()
{
  //EthernetConnection();


  //sethunter(false);
  //settheirspos(9, 9);
 // delay(500);



  if(softwareserial.available()) {//eigene position aktualisieren
      CHAR=softwareserial.read();
      if(iindex < MaxLength-1){
      message[iindex++] = CHAR;

      }else{
        Serial.println("Error: BufferOverflow");
      }

      if(CHAR == '\n'){
        iindex=0;
        process();
      }

  }


//setmyspos(0,0);
//settheirspos(5,6);
//delay(200);
//settheirspos(0,1);
//delay(200);




}