#include <neopixel.h>

#include "application.h"
#include "Particle.h"
#include "neopixel.h"

void colorMany(int which_ones[], int num, int RGB[]);
void colorOne(uint32_t c, uint8_t wait, int index);

SYSTEM_MODE(AUTOMATIC);

/* Pixel definitions */
#define Bright 100
#define PIXEL_COUNT 65
#define PIXEL_TYPE WS2812

/* Strip definitions */
#define STRIP_1 D2
#define STRIP_2 D3
#define STRIP_3 D4
#define STRIP_4 D5
#define STRIP_5 D6

Adafruit_NeoPixel strip_1(PIXEL_COUNT, STRIP_1, PIXEL_TYPE);
Adafruit_NeoPixel strip_2(PIXEL_COUNT, STRIP_2, PIXEL_TYPE);
Adafruit_NeoPixel strip_3(PIXEL_COUNT, STRIP_3, PIXEL_TYPE);
Adafruit_NeoPixel strip_4(PIXEL_COUNT, STRIP_4, PIXEL_TYPE);
Adafruit_NeoPixel strip_5(PIXEL_COUNT, STRIP_5, PIXEL_TYPE);

/* State definitions */
char* state = "reset";

void setup() {
    //Serial.begin(115200);
    
    Particle.subscribe("transmitter_ECE364_Megaton", myHandler);
    Serial.begin(9600);

    /* For each strip, initalize a color */
    strip_1.begin();
    strip_1.show();
    strip_1.setPixelColor(0, strip_1.Color(0,0,0));
    pinMode(STRIP_1,OUTPUT);
    digitalWrite(STRIP_1,LOW);

    strip_2.begin();
    strip_2.show();
    strip_2.setPixelColor(0, strip_2.Color(0,0,0));
    pinMode(STRIP_2,OUTPUT);
    digitalWrite(STRIP_2,LOW);

    strip_3.begin();
    strip_3.show();
    strip_3.setPixelColor(0, strip_3.Color(0,0,0));
    pinMode(STRIP_3,OUTPUT);
    digitalWrite(STRIP_3,LOW);

    strip_4.begin();
    strip_4.show();
    strip_4.setPixelColor(0, strip_4.Color(0,0,0));
    pinMode(STRIP_4,OUTPUT);
    digitalWrite(STRIP_4,LOW);

    strip_5.begin();
    strip_5.show();
    strip_5.setPixelColor(0, strip_5.Color(0,0,0));
    pinMode(STRIP_5,OUTPUT);
    digitalWrite(STRIP_5,LOW);

}

void loop() {

    if (strcmp(state, "reset") == 0){
        int choices[] = {1,2,3,4,5};
        int RGB[] = {Bright/2, 0, Bright/2};
        colorMany(choices, 5, RGB);  // all purple
        
    } else if (strcmp(state, "state1") == 0){
        
        int choices[] = {1,2};
        int RGB[] = {Bright, 0, 0};
        colorMany(choices, 2, RGB);  // 1 and 2 red
        
        int turnOff[] = {3,4,5};
        int black[] = {0,0,0};
        colorMany(turnOff, 3, black);  // 1 and 2 red
        
    } else if (strcmp(state, "state2") == 0){
        int choices[] = {2,3};
        int RGB[] = {Bright/2, Bright/2, 0};
        colorMany(choices, 2, RGB);  // 2 and 3 orange
        
        int turnOff[] = {1,4,5};
        int black[] = {0,0,0};
        colorMany(turnOff, 3, black);  // 1 and 2 red
        
    } else if (strcmp(state, "state3") == 0){
        int choices[] = {3,4};
        int RGB[] = {0, 0, Bright};
        colorMany(choices, 2, RGB);  // 3 and 4 blue
        
        int turnOff[] = {1,2,5};
        int black[] = {0,0,0};
        colorMany(turnOff, 3, black);  // 1 and 2 red
        
    } else if (strcmp(state, "state4") == 0){
        int choices[] = {1,2,3,4,5};
        int RGB[] = {Bright/3, Bright/3, Bright/3};
        colorMany(choices, 5, RGB);  // all white
    }
}

void colorMany(int which_ones[], int num, int RGB[]) {

  for (int i = 0; i < num; ++i) {
    switch(which_ones[i]) {
      case 1:
        colorOne(strip_1.Color(RGB[0], RGB[1], RGB[2]), 100, which_ones[i]);
        break;
      case 2:
        colorOne(strip_2.Color(RGB[0], RGB[1], RGB[2]), 100, which_ones[i]);
        break;
      case 3:
        colorOne(strip_3.Color(RGB[0], RGB[1], RGB[2]), 100, which_ones[i]);
        break;
      case 4:
        colorOne(strip_4.Color(RGB[0], RGB[1], RGB[2]), 100, which_ones[i]);
        break;
      case 5:
        colorOne(strip_5.Color(RGB[0], RGB[1], RGB[2]), 100, which_ones[i]);
        break;

      default:  
        break;
    }
  }

}

void colorOne(uint32_t c, uint8_t wait, int index) {
  uint16_t i;

  switch(index) {
    case 1:
      digitalWrite(STRIP_1,HIGH);
      for(i=0; i<strip_1.numPixels(); i++) {
        strip_1.setPixelColor(i, c);
      }
      strip_1.show();
      break;

    case 2:
      digitalWrite(STRIP_2,HIGH);
      for(i=0; i<strip_2.numPixels(); i++) {
        strip_2.setPixelColor(i, c);
      }
      strip_2.show();
      break;

    case 3:
      digitalWrite(STRIP_3,HIGH);
      for(i=0; i<strip_3.numPixels(); i++) {
        strip_3.setPixelColor(i, c);
      }
      strip_3.show();
      break;

    case 4:
      digitalWrite(STRIP_4,HIGH);
      for(i=0; i<strip_4.numPixels(); i++) {
        strip_4.setPixelColor(i, c);
      }
      strip_4.show();
      break;

    case 5:
      digitalWrite(STRIP_5,HIGH);
      for(i=0; i<strip_5.numPixels(); i++) {
        strip_5.setPixelColor(i, c);
      }
      strip_5.show();
      break;

    default:
      break;

  }

  delay(wait);
}


/* HANDLER */

void myHandler(const char *event, const char *data)
{
    if (data) {
        state = (char*) data;
    }
}
