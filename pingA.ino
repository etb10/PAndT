#include <neopixel.h>
#include "application.h"
#include "Particle.h"

void colorAll(uint32_t c, uint8_t wait);
void colorWipe(uint32_t c, uint8_t wait);
void rainbow(uint8_t wait);
void rainbowCycle(uint8_t wait);
uint32_t Wheel(byte WheelPos);

SYSTEM_MODE(AUTOMATIC);

#define PIXEL_COUNT 24
#define CIRCLE_ONE_PIN D5
#define CIRCLE_TWO_PIN D6
#define CIRCLE_THREE_PIN D7
#define PIXEL_TYPE WS2812
Adafruit_NeoPixel circleOne(PIXEL_COUNT, CIRCLE_ONE_PIN, PIXEL_TYPE);
Adafruit_NeoPixel circleTwo(PIXEL_COUNT, CIRCLE_TWO_PIN, PIXEL_TYPE);
Adafruit_NeoPixel circleThree(PIXEL_COUNT, CIRCLE_THREE_PIN, PIXEL_TYPE);

char* state = "reset";
char myNum = 'a';

void setup() {
    //Serial.begin(115200);
    
    Particle.subscribe("transmitter_ECE364_Megaton", myHandler);
    Serial.begin(9600);
    circleOne.begin();
    circleOne.show();
    circleOne.setPixelColor(0, circleOne.Color(0,0,0));
    circleTwo.begin();
    circleTwo.show();
    circleTwo.setPixelColor(0, circleTwo.Color(0,0,0));
    circleThree.begin();
    circleThree.show();
    circleThree.setPixelColor(0, circleThree.Color(0,0,0));
}

void loop() {
    // Trigger pin, Echo pin, delay (ms), visual=true|info=false
    ping(D2, D3, 1000, true);
    
    if (strcmp(state, "reset") == 0){
        colorAllCircleOne(circleOne.Color(0, 0, 0), 5000);
        colorAllCircleTwo(circleTwo.Color(0, 0, 0), 5000);
        colorAllCircleThree(circleThree.Color(0, 0, 0), 5000); 
        
    } else if (strcmp(state, "state1") == 0 && (myNum == 'a')){
        colorAllCircleOne(circleOne.Color(10, 0, 0), 5000);
        colorAllCircleTwo(circleTwo.Color(10, 0, 0), 5000);
        colorAllCircleThree(circleThree.Color(10, 0, 0), 5000); 
        
    } else if (strcmp(state, "state2") == 0 && (myNum == 'a' || myNum == 'b')){
        colorAllCircleOne(circleOne.Color(0, 10, 0), 5000);
        colorAllCircleTwo(circleTwo.Color(0, 10, 0), 5000);
        colorAllCircleThree(circleThree.Color(0, 10, 0), 5000); 
        
    } else if (strcmp(state, "state3") == 0 && (myNum == 'a' || myNum == 'b' || myNum == 'c')){
        colorAllCircleOne(circleOne.Color(10, 0, 10), 5000);
        colorAllCircleTwo(circleTwo.Color(10, 0, 10), 5000);
        colorAllCircleThree(circleThree.Color(10, 0, 10), 5000); 
        
    } else if (strcmp(state, "state4") == 0 && (myNum == 'a' || myNum == 'b' || myNum == 'c' || myNum == 'd')){
        colorAllCircleOne(circleOne.Color(10, 0, 0), 5000);
        colorAllCircleTwo(circleTwo.Color(10, 0, 0), 5000);
        colorAllCircleThree(circleThree.Color(10, 0, 0), 5000); 
        
    }
}


void ping(pin_t trig_pin, pin_t echo_pin, uint32_t wait, bool info)
{
    uint32_t duration, inches, cm;
    static bool init = false;
    if (!init) {
        pinMode(trig_pin, OUTPUT);
        digitalWriteFast(trig_pin, LOW);
        pinMode(echo_pin, INPUT);
        delay(50);
        init = true;
    }

    /* Trigger the sensor by sending a HIGH pulse of 10 or more microseconds */
    digitalWriteFast(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWriteFast(trig_pin, LOW);
  
    duration = pulseIn(echo_pin, HIGH);
    inches = duration / 74 / 2;
    cm = duration / 29 / 2;
    Particle.publish("STATE",String(state));
    if (inches < 12){
        
        if (strcmp(state, "reset") == 0) {
            if (myNum == 'a'){
                state = "state1";
                Particle.publish("transmitter_ECE364_Megaton", "state1");
            } else {
                state = "reset";
                Particle.publish("transmitter_ECE364_Megaton", "reset");
            }
        } 
        else if (strcmp(state, "state1") == 0){
            if (myNum == 'a'){
                state = "state1";
                Particle.publish("transmitter_ECE364_Megaton", "state1");
            } else if (myNum == 'b') {
                state = "state2";
                Particle.publish("transmitter_ECE364_Megaton", "state2");
            } else {
                state = "reset";
                Particle.publish("transmitter_ECE364_Megaton", "reset");
            }
            
        } 
        else if (strcmp(state, "state2") == 0){
            if (myNum == 'b'){
                state = "state2";
                Particle.publish("transmitter_ECE364_Megaton", "state2");
            } else if (myNum == 'c') {
                state = "state3";
                Particle.publish("transmitter_ECE364_Megaton", "state3");
            } else {
                state = "reset";
                Particle.publish("transmitter_ECE364_Megaton", "reset");
            }
            
        }
        else if (strcmp(state, "state3") == 0){
            if (myNum == 'c'){
                state = "state3";
                Particle.publish("transmitter_ECE364_Megaton", "state3");
            } else if (myNum == 'd') {
                state = "state4";
                Particle.publish("transmitter_ECE364_Megaton", "state4");
            } else {
                state = "reset";
                Particle.publish("transmitter_ECE364_Megaton", "reset");
            }
            
        }
        else if (strcmp(state, "state4") == 0){
            if (myNum == 'd'){
                state = "state4";
                Particle.publish("transmitter_ECE364_Megaton", "state4");
            } else {
                state = "reset";
                Particle.publish("transmitter_ECE364_Megaton", "reset");
            }
        }
        
    }
      
    if (info) { /* Visual Output */
        Serial.printf("%2d:", inches);
        for(int x=0;x<inches;x++) Serial.print("#");
        Serial.println();
    } else { /* Informational Output */
        Serial.printlnf("%6d in / %6d cm / %6d us", inches, cm, duration);
    }
    delay(wait); // slow down the output
}

void colorAllCircleOne(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<circleOne.numPixels(); i++) {
    circleOne.setPixelColor(i, c);
  }
  circleOne.show();
  delay(wait);
}

void colorAllCircleTwo(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<circleOne.numPixels(); i++) {
    circleTwo.setPixelColor(i, c);
  }
  circleTwo.show();
  delay(wait);
}

void colorAllCircleThree(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<circleOne.numPixels(); i++) {
    circleThree.setPixelColor(i, c);
  }
  circleThree.show();
  delay(wait);
}

void colorWipeCircleOne(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<circleOne.numPixels(); i++) {
    circleOne.setPixelColor(i, c);
    circleOne.show();
    delay(wait);
  }
}

void rainbowCircleOne(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<circleOne.numPixels(); i++) {
      circleOne.setPixelColor(i, Wheel((i+j) & 255));
    }
    circleOne.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout, then wait (ms)
void rainbowCycleCircleOne(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) { // 1 cycle of all colors on wheel
    for(i=0; i< circleOne.numPixels(); i++) {
      circleOne.setPixelColor(i, Wheel(((i * 256 / circleOne.numPixels()) + j) & 255));
    }
    circleOne.show();
    delay(wait);
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return circleOne.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return circleOne.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return circleOne.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

// HANDLER -------------------

void myHandler(const char *event, const char *data)
{
    if (data) {
        state = (char*) data;
    }
}
