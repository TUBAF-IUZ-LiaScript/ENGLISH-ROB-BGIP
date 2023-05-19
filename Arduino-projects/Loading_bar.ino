#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
int pos = 0;
int speed = 500;
int fail = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {    
fail = random(0,10);
for (pos=0; pos < NUM_LEDS-1; pos++) 
    {
        speed = random(200,2000);
        leds[pos] = CRGB::Green; 
        FastLED.show();
        delay(speed);
    }
delay(4000);

if (fail < 4)
    {
        for (int j = 0; j < 6; j++)  
          {         
            for (int m = 0; m < NUM_LEDS; m++)
             {
               leds[m] = CRGB::Green;
               FastLED.show();
             }
             delay(100);
             for (int m = 0; m < NUM_LEDS; m++)
             {
               leds[m] = CRGB::Black;
               FastLED.show();
             }
             delay(100);           
          }
    } else {
        for (int j = 0; j < 4; j++)
        {
           for (int n = 0; n < NUM_LEDS; n++)
             {
               leds[n] = CRGB::Red;
               FastLED.show();
               delay(10);
             }  
           for (int n = 0; n < NUM_LEDS; n++)
             {
               leds[n] = CRGB::Black;
               FastLED.show();
               delay(10);
             }   
        }
    }

for (int j = 0; j < NUM_LEDS; j++)
        { 
         leds[j] = CRGB::Black;
         FastLED.show();
        }
        
delay(2000);        
}