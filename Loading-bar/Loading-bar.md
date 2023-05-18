<!--

author:   Samuel Vogel, Sophie Farkov
email:    samuel.vogel0306@gmail.com
version:  0.1.0
language: EN
narrator: US English Female Female

import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md

-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://github.com/TUBAF-IUZ-LiaScript/ENGLISH-ROB-BGIP/blob/main/Loading-bar/Loading-bar.md)

# Loading bar

## 1. Video

!?[video](https://youtu.be/2svc2AZ6yAM)

## 2. Q&A

What does our code do?
- simulates loading bar that can go faster or slower randomly
- last bit will take extra long
- 70 percent chance that the loading process will fail and start over again (red lights)

How does our code work?
- set up fail variable as random number between 1 and 10 (will be different each loop)
- for first 11 pixels, assign random speed value
- add extra delay via "delay(4000);"
- two different ending animations depending on the size of the fail variable

How could it be used?
- originally, no plan to use it; was made just for fun
- could maybe be used to study people's behaviour when waiting for something

How could the program be upgraded?
- increase code quality
- not only make it random IF it's going to fail, but also WHEN it's going to fail

## 3. Simulation

<div id="matrix-experiment">
<wokwi-neopixel-matrix pin="6" cols="12" rows="1"></wokwi-neopixel-matrix>
<span id="simulation-time"></span>
</div>

```cpp             Automata
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

```
@AVR8js.sketch(matrix-experiment)
