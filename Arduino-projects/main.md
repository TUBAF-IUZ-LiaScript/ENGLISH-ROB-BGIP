<!--

author:   Students of ROB-BGIB english course
version:  0.1.0
language: EN
narrator: US English Female Female

import: https://raw.githubusercontent.com/liaTemplates/AVR8js/main/README.md

-->

[![LiaScript](https://raw.githubusercontent.com/LiaScript/LiaScript/master/badges/course.svg)](https://liascript.github.io/course/?https://github.com/TUBAF-IUZ-LiaScript/ENGLISH-ROB-BGIP/blob/main/Arduino-projects/main.md)

# Bubblesort on a Strip of 12 LEDs
## The Programm
1. It fills the strip randomly with 5 different colors
2. Starts the Bubblesort and orders the colors according to values assingend to them
3. In the end the strip shows the color in order and starts all over again

## The Code
<div id="matrix-experiment">
<wokwi-neopixel-matrix pin="6" cols="12" rows="1"></wokwi-neopixel-matrix>
<span id="simulation-time"></span>
</div>

```HK_LED_bubblesort.cpp             Automata
#include <Arduino.h>
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12
#define NUM_COLORS 6
int i = 0;
CRGB leds[NUM_LEDS];
CRGB colors[] = {CRGB:: Black, CRGB::Purple, CRGB::Blue , CRGB::Green,  CRGB::Yellow , CRGB::Red};
int sort[NUM_LEDS];

void led_colorval(int* array, CRGB* colors ){
  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = colors[sort[i]];
  }
}

void bubbleSort (int* array, int leng){
    int j = 0;
    int swapped = 0;
    for(int fertig = 0; fertig< leng; fertig ++){
        for(int i = leng-1; i> fertig; i--){
            if(array[i-1]> array[i]){
                int tmp = array[i];
                array[i]=array[i-1];
                array[i-1]= tmp;
                swapped = 1;
                delay(250); 
                led_colorval(array, colors);
                FastLED.show(); 

            }
        }
        delay(300);
        if(!swapped) return;
        swapped = 0;
    }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  for(int i = 0; i<NUM_LEDS; i++){
    sort[i] = rand() % (NUM_COLORS -1) +1;
  }
  led_colorval(sort, colors);
  FastLED.show();
  delay(1500);

  bubbleSort( sort, NUM_LEDS);

  delay(2000);

}
```
@AVR8js.sketch(matrix-experiment)

## Idea:
1. use the LEDs in a fun way thats also educational
2. visualize bubblesort
3. use the potential of having multiple colors

## further development:
1. also implement other Sorting Algorithms (like quicksort) in the same way
2. add more colors or LEDs
3. use a matrix to also be able to use height to show the values (not only color)

# Colormixing on a adressable LED strip

## Explanation

The file colormix is a simple programm, that uses two different colors to create a mixed color. 

The two colors are filled in from the left and the right side.
The values of these colors are randomly chosen by random8, a function that creates pseudorandom 8bit values.

These values are the hue in the HSV colorspectrum, 
which determines the random colors. Once the colors are filled in from the left and the right side and they touch in the middle, 

the mixed color is determined through average mixing. 

Then the fill color fills the LEDs outwards from the middle and the LED strip resets once it's fully filled. Then the code will loop indefinetly.  

## Video

!?[video](https://youtu.be/PGe-OgqjDAM)

## Working simulation

<div id="matrix-experiment">
<wokwi-neopixel-matrix pin="6" cols="12" rows="1"></wokwi-neopixel-matrix>
<span id="simulation-time"></span>
</div>

```cpp             Automata
#include "FastLED.h"
#define DATA_PIN 6
#define BRIGHTNESS 180
#define NUM_LEDS 12

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

CRGB random_color() {
  return CHSV(random8(), 255, 255);
}

void fill_leds_simultaneously(CRGB color_left, CRGB color_right, int delay_ms) {
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[i] = color_left;
    leds[NUM_LEDS - 1 - i] = color_right;
    FastLED.show();
    delay(delay_ms);
  }
}

CRGB average_mix(CRGB color1, CRGB color2) {
  CRGB combined_color;
  combined_color.r = (color1.r + color2.r) / 2;
  combined_color.g = (color1.g + color2.g) / 2;
  combined_color.b = (color1.b + color2.b) / 2;
  return combined_color;
}

void fill_combined_color(CRGB color_left, CRGB color_right, int delay_ms) {
  CRGB combined_color = average_mix(color_left, color_right);
  for (int i = 0; i < NUM_LEDS / 2; i++) {
    leds[NUM_LEDS / 2 - i - 1] = combined_color;
    leds[NUM_LEDS / 2 + i] = combined_color;
    FastLED.show();
    delay(delay_ms);
  }
}

void loop() {
  CRGB color_left = random_color();
  CRGB color_right = random_color();
  
  fill_leds_simultaneously(color_left, color_right, 250);
  fill_combined_color(color_left, color_right, 250);
  
  FastLED.clear();
  FastLED.show();
  delay(1000);
}

```
@AVR8js.sketch(matrix-experiment)

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
<wokwi-neopixel-matrix pin="6" cols="12" rows="1"></wokwi-neopixel-matrix>
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
