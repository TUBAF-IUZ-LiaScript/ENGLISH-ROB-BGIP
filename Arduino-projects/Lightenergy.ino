#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
int i = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Red;  
            FastLED.show(); 
            delay(500);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(500);            
         }
        leds[i] = CRGB::Red; 
        FastLED.show();
    }
for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Orange;  
            FastLED.show(); 
            delay(400);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(400);            
         }
        leds[i] = CRGB::Orange; 
        FastLED.show();
    }
for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Yellow;  
            FastLED.show(); 
            delay(300);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(300);            
         }
        leds[i] = CRGB::Yellow; 
        FastLED.show();
    }
for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Green;  
            FastLED.show(); 
            delay(200);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(200);            
         }
        leds[i] = CRGB::Green; 
        FastLED.show();
    }
for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Blue;  
            FastLED.show(); 
            delay(100);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(100);            
         }
        leds[i] = CRGB::Blue; 
        FastLED.show();
    }
for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Cyan;  
            FastLED.show(); 
            delay(50);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(50);            
         }
        leds[i] = CRGB::Cyan; 
        FastLED.show();
    }for (i=0; i < NUM_LEDS-4; i++) 
    {
        for (int j = 0; j < 2; j++)
         {        
            leds[i] = CRGB::Violet;  
            FastLED.show(); 
            delay(25);
            leds[i] = CRGB::Black;
            FastLED.show();
            delay(25);            
         }
        leds[i] = CRGB::Violet; 
        FastLED.show();
    }
for (; i < NUM_LEDS; i++)
      {
         for (int j = 0; j < 2; j++)  
          {         
            leds[i] = CRGB::Black;
             FastLED.show();
             delay(0);
             leds[i] = CRGB::Black;
             FastLED.show();
             delay(0);           
          }
         leds[i] = CRGB::Black; 
         FastLED.show();
         if(i==NUM_LEDS-4)
         {
           for (int n = 0; n < NUM_LEDS-4; n++)
            {
             leds[n] = CRGB::Black;
             FastLED.show();
            }
         }
         else if(i==NUM_LEDS-1)
         {
           for (int n = 0; n < NUM_LEDS; n++)
             {
               leds[n] = CRGB::White;
               FastLED.show();
             }
            delay(10000);
         }
       }
for (int j = 0; j < NUM_LEDS; j++)
        { 
         leds[j] = CRGB::Black;
         FastLED.show();
        }
}