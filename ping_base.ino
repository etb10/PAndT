// This #include statement was automatically added by the Particle IDE.
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
#define GREEN_PIN D4

#define PIXEL_TYPE WS2812
Adafruit_NeoPixel stripGreen(PIXEL_COUNT, GREEN_PIN, PIXEL_TYPE);

void setup() {
    Serial.begin(115200);
    pinMode(D7, OUTPUT);
    stripGreen.begin();
    stripGreen.show();
    stripGreen.setPixelColor(0,stripGreen.Color(0,0,0));
}

void loop() {
    // Trigger pin, Echo pin, delay (ms), visual=true|info=false
    ping(D5, D6, 20, true);
}

void colorAllGreen(uint32_t c, uint8_t wait) {
  uint16_t i;

  for(i=0; i<stripGreen.numPixels(); i++) {
    stripGreen.setPixelColor(i, c);
  }
  stripGreen.show();
  delay(wait);
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
    
    /* Convert the time into a distance */
    // Sound travels at 1130 ft/s (73.746 us/inch)
    // or 340 m/s (29 us/cm), out and back so divide by 2
    // Ref: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
    inches = duration / 74 / 2;
    cm = duration / 29 / 2;
    
    if (inches < 12){
        digitalWrite(D7, HIGH);
        colorAllGreen(stripGreen.Color(0, 90, 0), 50); // Green
    } else {
        digitalWrite(D7, LOW);
        colorAllGreen(stripGreen.Color(0, 0, 0), 50); // Green
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