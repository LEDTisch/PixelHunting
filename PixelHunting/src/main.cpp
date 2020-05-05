#include <Arduino.h>

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
#include <avr/power.h>
#endif
#define PIN 10        // Hier wird angegeben, an welchem digitalen Pin die WS2812 LEDs bzw. NeoPixel angeschlossen sind
#define NUMPIXELS 150 // Hier wird die Anzahl der angeschlossenen WS2812 LEDs bzw. NeoPixel angegeben
Adafruit_NeoPixel led = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int mypixelx=5;
int mypixely=5;
int thierpixelx=6;
int theirpixely=6;
boolean amihunter =true;
char blue;
int pixel[10][15];

int row_x[10];

void setup() {
   led.begin();
  Serial.begin(9600);
 Serial1.begin(9600);
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

void loop() {

  //GET PIXEL THIERSX AND Y and if i hunter

if(Serial1.available()){
     
    
     //blue=Serial1.read();
     Serial1.setTimeout(50);
     String bb=Serial1.readString(); 

      if(bb[0]=='s'){
blue=bb[1];
if(blue=='4'){//hoch
mypixely++;
}

if(blue=='2'){//rechts
if(mypixelx<9) {
mypixelx++;
}
}

if(blue=='0'){//links
if(mypixelx>0) {
mypixelx--;
}
}

if(blue=='7'){//runter
mypixely--;
}

if(blue=='1'){//neuesspiel

}
}

    }

  led.clear();

  if(amihunter) {
 led.setPixelColor(pixel[thierpixelx][theirpixely],led.Color(10,0,0));
  led.setPixelColor(pixel[mypixelx][mypixely],led.Color(0,70,0));

  if(pixel[thierpixelx][theirpixely]==pixel[mypixelx][mypixely]) {
    for(int y =0;y<15;y++) {
      for(int x=0;x<15;x++) {
          led.setPixelColor(pixel[x][y],led.Color(0,100,0)); //Hier warten auf weitere Angaben des Server wann ein neues Spiel gestartet wird
      }
    } 
  }
  
  }else{
    led.setPixelColor(pixel[thierpixelx][theirpixely],led.Color(70,0,0));
  led.setPixelColor(pixel[mypixelx][mypixely],led.Color(0,10,0));

  if(pixel[thierpixelx][theirpixely]==pixel[mypixelx][mypixely]) {
    for(int y =0;y<15;y++) {
      for(int x=0;x<15;x++) {
          led.setPixelColor(pixel[x][y],led.Color(100,0,0));
      }
    } 
  }
  }
  
 
  led.show();
}