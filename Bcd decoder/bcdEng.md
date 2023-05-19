<!--

author:   Ben und Martin
email:    
version:  0.1.7
language: EN
narrator: US English Female Female


import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md
        

-->
[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://github.com/BenWeckend/BCD/blob/main/bcd.md?plain=1)

# BCD Decoder
-------------

## Video
--------
!?[bcd](https://cdn.discordapp.com/attachments/505834702515470348/1106535704860827658/20230512_1158062.mp4)

## Text
-------

**What does it do**

The led strip displays the conversion of an 8 bit binary number into a three digit BCD number. 

**How does it work?**

First an input number is displayed in a standard binary format.
It then gets converted using the double-dabble algorithm, which alternates between doubling the input number (shifting it one position to the left) and dabbling with the number (adding the value of 3 in the according places if necessary).

**Where is the idea from?**

Little Jimmy, 3rd grade Freiberg elementary school. 

**Where did you get the coding knowledge from?**

- Introductory programming course in the winter semester
- Personal experience

**How could you develop the idea further?**

- Display both the input and output number on seperate LED strips



## Simulation
-----
<div id="matrix-experiment">
<wokwi-neopixel-matrix pin="6" cols="9" rows="9"></wokwi-neopixel-matrix>
<span id="simulation-time"></span>
</div>

```cpp             Automata

#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
uint8_t num = 0;

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void writeLeds(uint32_t input) {
    memset(leds, 0x0, sizeof(CRGB) * NUM_LEDS);
    for (int i = 0; i < NUM_LEDS; i++) {
        if(input & (1 << (NUM_LEDS - i - 1))) {
            leds[i] = CRGB::White;
        };
    }
    FastLED.show();
}

void dabble(uint32_t* input, int offset) {
    uint32_t temp = *input >> offset;
    temp &= 15;

    if(temp > 4) temp += 3;

    *input &= ~(15 << offset);
    *input |= temp << offset;
}

void loop() {
    num += 31415962 / num;
    uint32_t workingVar = num;
    
    writeLeds(workingVar);
    delay(5000);

    workingVar = workingVar << 1;
    for(int i = 0; i < 7; i++) {
        // dabble
        dabble(&workingVar, 8);
        dabble(&workingVar, 12);
        dabble(&workingVar, 16);

        // display 1
        writeLeds(workingVar >> 8);
        delay(500);

        // double
        workingVar = workingVar << 1;

        // display 2
        writeLeds(workingVar >> 8);
        delay(500);
    }

    for(int i = 0; i < NUM_LEDS; i++) {
        if(leds[i] = CRGB::Black) {
            if( i < 4)     leds[i] = CRGB::Red;
            else if(i > 7) leds[i] = CRGB::Blue;
            else           leds[i] = CRGB::Green;
        }
    }
    FastLED.show();
    delay(10000);
}


```
@AVR8js.sketch(matrix-experiment)
