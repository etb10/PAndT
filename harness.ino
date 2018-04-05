// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

// This #include statement was automatically added by the Particle IDE.
#include <neopixel.h>

/*-------------------------------------------------------------------------
  Spark Core, Particle Photon, P1, Electron and RedBear Duo library to control
  WS2811/WS2812/WS2813 based RGB LED devices such as Adafruit NeoPixel strips.
  Supports:
  - 800 KHz WS2812, WS2812B, WS2813 and 400kHz bitstream and WS2811
  - 800 KHz bitstream SK6812RGBW (NeoPixel RGBW pixel strips)
    (use 'SK6812RGBW' as PIXEL_TYPE)
  Also supports:
  - Radio Shack Tri-Color Strip with TM1803 controller 400kHz bitstream.
  - TM1829 pixels
  PLEASE NOTE that the NeoPixels require 5V level inputs
  and the Spark Core, Particle Photon, P1, Electron and RedBear Duo only
  have 3.3V level outputs. Level shifting is necessary, but will require
  a fast device such as one of the following:
  [SN74HCT125N]
  http://www.digikey.com/product-detail/en/SN74HCT125N/296-8386-5-ND/376860
  [SN74HCT245N]
  http://www.digikey.com/product-detail/en/SN74HCT245N/296-1612-5-ND/277258
  Written by Phil Burgess / Paint Your Dragon for Adafruit Industries.
  Modified to work with Particle devices by Technobly.
  Contributions by PJRC and other members of the open source community.
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing products
  from Adafruit!
  --------------------------------------------------------------------*/

/* ======================= includes ================================= */

#include "Particle.h"
#include "neopixel.h"

/* ======================= prototypes =============================== */

void colorAll(uint32_t c, uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
uint32_t Wheel(byte WheelPos);

/* ======================= extra-examples.cpp ======================== */

SYSTEM_MODE(AUTOMATIC);

// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_COUNT 65
#define GREEN_PIN D2
#define YELLOW_PIN D2
#define RED_PIN D2
#define Bright 200


int redPin = D4;
int yellowPin = D3;
int greenPin = D2;


#define PIXEL_TYPE WS2812


Adafruit_NeoPixel stripGreen(PIXEL_COUNT, greenPin, PIXEL_TYPE);
Adafruit_NeoPixel stripYellow(PIXEL_COUNT, yellowPin, PIXEL_TYPE);
Adafruit_NeoPixel stripRed(PIXEL_COUNT, redPin, PIXEL_TYPE);

char* greenTurnOns[] = {"greenOn","switchGreen","goodToGo","ALL_ON"};
int greenTurnOnsLength = 4;
char* greenTurnOffs[] = {"greenOff","ALL_OFF"};
int greenTurnOffsLength = 4;

char* yellowTurnOns[] = {"yellowOn","switchYellow","letsJustBeFriends","ALL_ON"};
int yellowTurnOnsLength = 4;
char* yellowTurnOffs[] = {"yellowOff","ALL_OFF"};
int yellowTurnOffsLength = 4;

char* redTurnOns[] = {"redOn","switchRed","LetsGetLunch","ALL_ON"};
int redTurnOnsLength = 4;
char* redTurnOffs[] = {"redOff","ALL_OFF"};
int redTurnOffsLength = 4;


void setup() {
    
  stripGreen.begin();
  stripYellow.begin();
  stripRed.begin();
  stripGreen.show();
  stripYellow.show();
  stripRed.show();
  
  
  Particle.subscribe("transmitter_ECE364_Megaton",myHandler);
    pinMode(yellowPin,OUTPUT);
    pinMode(greenPin,OUTPUT);
    pinMode(redPin,OUTPUT);
    
    digitalWrite(yellowPin,LOW);
    digitalWrite(greenPin,LOW);
    digitalWrite(redPin,LOW);
    
    Serial.begin(9600);

  
}

void loop() {

 
  
    
}

// // Set all pixels in the strip to a solid color, then wait (ms)
void colorAllRed(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<stripRed.numPixels(); i++) {
    stripRed.setPixelColor(i, c);
  }
  stripRed.show();
  delay(wait);
}

void colorAllYellow(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<stripYellow.numPixels(); i++) {
    stripYellow.setPixelColor(i, c);
  }
  stripYellow.show();
  delay(wait);
}

void colorAllGreen(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<stripGreen.numPixels(); i++) {
    stripGreen.setPixelColor(i, c);
  }
  stripGreen.show();
  delay(wait);
}





bool turnGreenOn(String data)
{
    for(int i = 0; i < greenTurnOnsLength; i++)
    {
        if(strcmp(data,greenTurnOns[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool turnGreenOff(String data)
{
    for(int i = 0; i < greenTurnOffsLength; i++)
    {
        if(strcmp(data,greenTurnOffs[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool turnYellowOn(String data)
{
    for(int i = 0; i < yellowTurnOnsLength; i++)
    {
        if(strcmp(data,yellowTurnOns[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool turnYellowOff(String data)
{
    for(int i = 0; i < yellowTurnOffsLength; i++)
    {
        if(strcmp(data,yellowTurnOffs[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool turnRedOn(String data)
{
    for(int i = 0; i < redTurnOnsLength; i++)
    {
        if(strcmp(data,redTurnOns[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

bool turnRedOff(String data)
{
    for(int i = 0; i < redTurnOffsLength; i++)
    {
        if(strcmp(data,redTurnOffs[i]) == 0)
        {
            return true;
        }
    }
    return false;
}


// HANDLER -------------------

void myHandler(const char *event, const char *data) {


  if (data) {

    //Serial.println(data);
     //  colorAllGreen(stripGreen.Color(255, 0, 0), 50); // Red

    if (turnRedOn(data)) {
      digitalWrite(redPin,HIGH);
      colorAllGreen(stripGreen.Color(Bright, 0, 0), Bright); // Red
    } 
   // else if (turnRedOff(data)) {
     // digitalWrite(redPin,LOW);
     // colorAllGreen(stripGreen.Color(0, 0, 0), 50); // Red
    //}
    
    else if (turnYellowOn(data)) {
      digitalWrite(yellowPin,HIGH);
      colorAllGreen(stripGreen.Color(Bright/4, Bright/2, 0), Bright/2); // Yellow
    } 
    //else if (turnYellowOff(data)) {
   //   digitalWrite(yellowPin,LOW);
   //     colorAllGreen(stripGreen.Color(0, 0, 0), 50); // Yellow
    //}
    
    else if (turnGreenOn(data)) {
      digitalWrite(greenPin,HIGH);
      colorAllGreen(stripGreen.Color(0, Bright, 0), Bright); // Green
    } 
    else 
   // if (turnGreenOff(data)) 
    {
      digitalWrite(greenPin,LOW);
      colorAllGreen(stripGreen.Color(0, 0, 0), Bright); // Green
    }
    
}



}