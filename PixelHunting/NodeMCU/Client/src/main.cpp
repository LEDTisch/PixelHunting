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

    Serial.println("\nwriteerror");
    Serial.print(client.getWriteError());


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

void sendHunter(int hunter){
String eins="T2";
String zwei=" H";
String senden=eins+zwei+hunter;
softwareserial.println(senden);
}




void sendmyPositiontoServer(){
      String eins="T1";
  String zwei=" X";
  String drei=" Y";
  String senden=eins+zwei+myposx+drei+myposy;
  client.println(senden);
    }


int iindex=0;
char CHAR;
const int MaxLength=15;
char message[MaxLength];

float getValue(char gcode,char m[]){
  	char *ptr=m;
	
	while ((ptr>=m) && (ptr<(m+MaxLength))){	
		if (*ptr==gcode){
			return(atof(ptr+1));
		}
		ptr=strchr(ptr,' ')+1;
	}
	
	return(-1);	
}

void process(){
  int tcode=(int) getValue('T',message);
switch(tcode){
  case 0:
  myposx=(int)getValue('X',message);
  myposy=(int)getValue('Y',message);
  Serial.println(myposy);

  sendmyPositiontoServer();


  break;
  case 1:
  thierposx=(int)getValue('X',message);
  thierposy=(int)getValue('Y',message);
  break;

}
}

void process(String i){
  int n = i.length();
char test[n+1];
 strcpy(test, i.c_str()); 

  int tcode=(int) getValue('T',test);
switch(tcode){
  case 0:
  myposx=(int)getValue('X',test);
  myposy=(int)getValue('Y',test);

  setmyspos(myposx,myposy);


  break;
  case 1:
  thierposx=(int)getValue('X',test);
  thierposy=(int)getValue('Y',test);

  settheirspos(thierposx,thierposy);
  break;
    case 2:
    sendHunter((getValue('H',test)));
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


String resived;






client.setTimeout(50);
    if(client.available()) {
    resived = client.readString();
    }else{

    }
       
   if(resived!="") {

process(resived);

}



resived="";

//setmyspos(0,0);
//settheirspos(5,6);
//delay(200);
//settheirspos(0,1);
//delay(200);




}