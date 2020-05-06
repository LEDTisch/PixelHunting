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

void loop()
{



  if(Serial2.available()) {
    Serial2.setTimeout(50);
    String readesp="";
char c = 2;
while(c!='e') {
  delay(2);
  c = Serial2.read();
  readesp += c;

}

Serial.println(readesp);

  if(readesp.startsWith("n")) {

    ingamewait = true;
  } 

if(readesp.startsWith("n")) {

    ingamewait = false;
  } 


 if(readesp.startsWith("h")) {
   if(readesp.substring(1).toInt()==1) {
     amihunter = true;
   }else{
     amihunter= false;
   }

 }

  if(readesp.startsWith("m")) { 


    int indexx = readesp.indexOf('x');
    int indexy = readesp.indexOf('y');
    int indexend = readesp.indexOf('e');
    if(indexy==-1||indexx==-1) {}else{
    
     mypixelx = readesp.substring(indexx+1,indexy).toInt();
     mypixely = readesp.substring(indexy+1,indexend).toInt();
    }
  }

  if(readesp.startsWith("o")) { 
     int indexx = readesp.indexOf('x');
    int indexy = readesp.indexOf('y');
    int indexend = readesp.indexOf('e');
    if(indexy==-1||indexx==-1) {}else{
    
     
     thierpixelx = readesp.substring(indexx+1,indexy).toInt();
     theirpixely = readesp.substring(indexy+1,indexend).toInt();
     
    }
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
        Serial2.print("y");
        delay(2);
        Serial2.print(mypixely);
        delay(2);
         Serial2.println("e");
         delay(2);
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
         Serial2.print("x");
        delay(2);
        Serial2.print(mypixelx);
        delay(2);
         Serial2.println("e");
         delay(2);
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

         Serial2.print("x");
        delay(2);
        Serial2.print(mypixelx);
        delay(2);
         Serial2.println("e");
         delay(2);
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
          Serial2.print("y");
        delay(2);
        Serial2.print(mypixely);
        delay(2);
         Serial2.println("e");
         delay(2);
      }

      if (blue == '1')
      { //neuesspiel
      }
    }
  }

  led.clear();

  if (amihunter)
  {
    led.setPixelColor(pixel[thierpixelx][theirpixely], led.Color(10, 0, 0));
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
    led.setPixelColor(pixel[mypixelx][mypixely], led.Color(0, 10, 0));

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