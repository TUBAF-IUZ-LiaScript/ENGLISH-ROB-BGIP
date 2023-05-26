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

## Questions

### What do the lights do and how does the code work?

The lights create a dynamic animation effect which changes every 1.5 seconds. Initially two random colors fill up the strip from each end. After that, the color that results from the average of the two fills the LED strip from the center towards the ends. This animation then repeats in a loop.

The script uses the FastLED library to control a strip of RGB LED lights. Constants define the LED data pin, brightness, and count. A CRGB array stores color data for each LED. In setup(), the strip is initialized and brightness is set.
random_color() generates a random hue color using random8, which creates a pseudorandom 8bit value.
fill_leds_simultaneously() fills the LED strip with the two colors, starting from the ends towards the center.
average_mix() calculates the average of the two colors.
fill_combined_color() fills the LED strip with the average color from the center outward.
In loop(), the previous steps are looped and the strip is cleared at the end.

### What is the intention and how did you come up with the idea?

The Intention was to showcase a dynamic and pleasing/soothing lighting effect using an LED strip. 

### What could the light animation be used for and how could the idea be developed further?

It can be used for visual art, decoration. With further development it could be used for visual feedback like music sync.
Furthermore matching colorpaletts could be created, to always display colors that match.

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

1.A What do the lights do?
* simulate loading bar that can go faster or slower randomly
* last pixel will take extra long
* 70 percent chance that the loading process will fail and start over again (red lights)

1.B How does our code work?
* set up fail variable as random number between 1 and 10 (will be different each loop)
* for first 11 pixels, assign random speed value
* add extra delay via "delay(4000);"
* two different ending animations depending on the size of the fail variable

2. What is the intention and how did we come up with the idea?
* originally, no real intention, we just wanted something annoying
* loading bar is one dimensional and would fit on LED stripe

3.A How could it be used?
* originally, no plan to use it; was made just for fun
* could maybe be used to study people's behaviour when waiting for something

3.B How could the program be developed further?
* increase code quality
* not only make it random IF it's going to fail, but also WHEN it's going to fail

4. Where did you get the coding knowledge from and what did we learn from this expierience?
* got coding knowledge from past lectures and Guide on LiaScript
* learned different ways to use a simple LED stripe

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

# electromagnetic Lightenergy
-------------
## the idea of this program
--------
The idea is based on the LED strip itself. 
It works with optical signals: light. Accordingly, we wanted to represent the physical view of light with the help of the LEDs. 
## working with the idea
--------
?[img](https://bodell.mtchs.org/OnlineBio/BIOCD/text/chapter8/08images/08-05.gif)

Quite a substantial part of physics deals with the nature of light. While light is a part of everyones life, there are many other characteristics, 
some which the human eye cannot make out at all!
So, dealing with the mere visibility of light was not the purpose of this code and we decided to focus on another characteristic of light: 
its electromagnetic energy and the corresponding wavelength: The visible light ranges from a wide variety of colors, 
including some such as: red, orange, yellow, green, blue, cyan and violet. 
Now, the wavelength ranges from 400 nm(violet) up to 700 nm(red), with shorter wavelengths having more energy. 
We decided to visualize this with the speed of the LED Bar filling, 
so that a shorter wavelength will fill the stripe much quicker than a longer wavelength.
The LED-Stripe starts with the color red, the longest wavelength and the one, which will take the longest to fill the LED-Stripe due to our code. 
In addition, the whole is summarized by white light. This symbolizes the totality of the lights and can be seen for the longest period of time before all the lights go out. Black, meaning the total absence of light, ends the code and serves as a clean finish. 
**How could you develop the idea further?**
One can more precisely determine the relationship between the speed of the colored light and the delay of the LEDs. 
Before each colour, a sequence of black and white single LED's can be used to simulate the wavelength 
(i.e. 3 LED lights turning white and black in sequency to simulate a low frequency wave, 1 LED light turning white and black in alternation to simulate a high frequency wave). 


## showcasing the program 
--------
!?[example](https://cdn.discordapp.com/attachments/1092117701520015430/1110470527589552258/20230519_1159522.mp4)
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

```

@AVR8js.sketch(matrix-experiment)
