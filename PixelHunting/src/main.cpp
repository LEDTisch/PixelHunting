#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 10        // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 150 // Hier wird die Anzahl der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int mypixelx = 5;
int mypixely = 5;
int thierpixelx = 6;
int theirpixely = 6;
boolean amihunter = true;
boolean ingamewait = false;
char blue;
int pixel[10][15];
boolean testconnnection = false;

int row_x[10];

void setup()
{
  led.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  row_x[0] = 135;
  row_x[1] = 134;
  row_x[2] = 105;
  row_x[3] = 104;
  row_x[4] = 75;
  row_x[5] = 74;
  row_x[6] = 45;
  row_x[7] = 44;
  row_x[8] = 15;
  row_x[9] = 14;

  for (int x = 0; x < 10; x++)
  {
    for (int y = 0; y < 15; y++)
    {

      if (x % 2 == 0)
      {

        pixel[x][y] = row_x[x] + y;
      }
      else
      {
        pixel[x][y] = row_x[x] - y;
      }
    }
  }
}



void draw(){
  led.clear();

  if (amihunter)
  {
    led.setPixelColor(pixel[thierpixelx][theirpixely], led.Color(30, 0, 0));
    led.setPixelColor(pixel[mypixelx][mypixely], led.Color(0, 70, 0));

    if (pixel[thierpixelx][theirpixely] == pixel[mypixelx][mypixely])
    {
      for (int y = 0; y < 15; y++)
      {
        for (int x = 0; x < 15; x++)
        {
          led.setPixelColor(pixel[x][y], led.Color(0, 100, 0)); //Hier warten auf weitere Angaben des Server wann ein neues Spiel gestartet wird
        }
      }
      ingamewait = true;
    }
    
  }
  else
  {
    led.setPixelColor(pixel[thierpixelx][theirpixely], led.Color(70, 0, 0));
    led.setPixelColor(pixel[mypixelx][mypixely], led.Color(0, 30, 0));

    if (pixel[thierpixelx][theirpixely] == pixel[mypixelx][mypixely])
    {
      for (int y = 0; y < 15; y++)
      {
        for (int x = 0; x < 15; x++)
        {
          led.setPixelColor(pixel[x][y], led.Color(100, 0, 0));
        }
      }
      ingamewait = true;
    }
    

  }

  if(testconnnection)  {
led.setPixelColor(pixel[0][0],led.Color(100,0,0));

  }

  led.show();
}



int index=0;
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



void sendmyPosition(int x,int y){
//Serial2.println("T0"+" X"+x+" Y"+y);
}

void process(){
  int tcode=(int) getValue('T');
switch(tcode){
  case 0:
  mypixelx=(int)getValue('X');
  mypixely=(int)getValue('Y');
  Serial.println(mypixely);
  draw();
  break;
  case 1:
    thierpixelx=(int)getValue('X');
  theirpixely=(int)getValue('Y');
  draw();
  break;
}
}


void loop()
{







  if(Serial2.available()) {//eigene position aktualisieren
      CHAR=Serial2.read();
      if(index < MaxLength-1){
      message[index++] = CHAR;

      }else{
        Serial.println("Error: BufferOverflow");
      }

      if(CHAR == '\n'){
        index=0;
        process();
      }

  }










  //GET PIXEL THIERSX AND Y and if i hunter 

  //UND abfrage der eigenen Position falls diese durch eine Zufällige positionierung des esp32 servers verändert wird





  if (Serial1.available()&&!ingamewait)
  {

    //blue=Serial1.read();
    Serial1.setTimeout(50);
    String bb = Serial1.readString();

    if (bb[0] == 's')
    {
      blue = bb[1];
      if (blue == '4')
      { //hoch
        if (mypixely < 14)
        {
          mypixely++;
         

        }
        else
        {
          mypixely = 0;
        }

      }
      if (blue == '2')
      { //rechts
        if (mypixelx < 9)
        {
          mypixelx++;
        }
        else
        {
          mypixelx = 0;
        }

      }

      if (blue == '0')
      { //links
        if (mypixelx > 0)
        {
          mypixelx--;
        }
        else
        {
          mypixelx = 9;
        }


      }

      if (blue == '7')
      { //runter
        if (mypixely > 0)
        {
          mypixely--;
        }
        else
        {
          mypixely = 14;
        }

      }

      if (blue == '1')
      { //neuesspiel
      }
    }

    sendmyPosition(mypixelx,mypixely);
  }





  
}