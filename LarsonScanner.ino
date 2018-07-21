#include <Adafruit_NeoPixel.h>

#define PIN 3  //data pin for neo-pixel signal
#define LENGTH 288 //max number of pixels

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LENGTH, PIN, NEO_GRB + NEO_KHZ800);

// Global Constants (User Configurable)

// because I used a longer than needed neo-pixel strip I set the area of the strip I wanted to use with the next 2 constants
const int START=71; //The first pixel where the effect will start
const int WIDTH=144; //Defines the range that the effect will occur

const int BLOCK=5; //The size bright bouncing block (pixels)

const unsigned long RED=0xFF0000; //The HEX code for Red
const unsigned long GREEN=0x00FF00; //The HEX code for Green
const unsigned long BLUE=0x0000FF; //The HEX code for Blue

// here you can set the color of the effect
const unsigned long COLOR=RED; //The HEX code for the brightest color (or type RED, GREEN, or BLUE)

const int SPEED=100; //range = 0 to 100 (100 results in ZERO latency)
const int PERSISTENCE=95; //range = 0-100 (100 NEVER fades, 0 fades INSTANTLY)

// Calculated Global Contants
const int LATENCY=(100-SPEED)/2; //LATENCY is better for calulations than SPEED

//Global Variables (initialized to default values)
int position=BLOCK;
int direction=1;
int pixel=1;
unsigned long red=(COLOR&RED)>>16; //extacts just the red value from the HEX color code
unsigned long green=(COLOR&GREEN)>>8; //extacts just the green value from the HEX color code
unsigned long blue=(COLOR&BLUE); //extacts just the blue value from the HEX color code
unsigned long color=(red<<16)+(green<<8)+(blue);  //combines red, green, and blue values to create a HEX color code

void setup()
{
  //Initialize and set all pixels to 'off'
  strip.begin();
  strip.clear();strip.show();
}

void loop()
{
//set the color of each pixel to a faded value of its previous color
//for (int i=0; i<WIDTH; i++)

//select a pixel within the range
pixel=START+POSITION;

//get the current color of the selected pixel
color=strip.getPixelColor(pixel);

//extract each color value from the HEX color code of the selected pixel
red=(color&RED)>>16;
green=(color&GREEN)>>8;
blue=(color&BLUE);

//dim each color value based on the PERSISTENCE setting
red*=(PERSISTENCE/100.0);
green*=(PERSISTENCE/100.0);
blue*=(PERSISTENCE/100.0);

//create a new HEX color code using the dimmed values
color=(red<<16)+(green<<8)+(blue);

//set the selected pixel's value to the new dimmed value
strip.setPixelColor(pixel, color);

//set "HEAD" pixels to full brightness
pixel=START+position;
for (int i=0; i<BLOCK; i++)
{
  pixel-=direction; //move index BACKWARD one pixel
  strip.setPixelColor(pixel, COLOR);
}

//display the NEW pixels data on the strip
strip.show();

//wait a faction of a second based on SPEED setting
delay(LATENCY);

//set the direction and advance to the next pixel
if (position>=WIDTH) {direction=-1; position-=BLOCK;}
if (position<=0) {direction=1; position=BLOCK;}
position+=direction; //move index FORWARD one pixel
}
