#include "mqtt.h"

#include <ArduinoJson.h>

#include <Adafruit_NeoPixel.h>

// GO READ https://www.tweaking4all.com/hardware/arduino/adruino-led-strip-effects/

Mqtt mqtt = Mqtt("uhome", "WhatTheHe11", "mqtt.local", 1883, "5RGBShield");

// constants won't change. They're used here to set pin numbers:
// D3 is the LOLIN Wemos 1-Button Shield: https://wiki.wemos.cc/products:d1_mini_shields:1-button_shield
//const int ledPin =  LED_BUILTIN;      // the number of the LED pin
//const int ledPin =  BUILTIN_LED;      // the number of the LED pin

// D4 is the default pin for the 6 LED RBG shield
// https://wiki.wemos.cc/products:d1_mini_shields:rgb_led_shield
// https://github.com/wemos/D1_mini_Examples/blob/master/examples/04.Shields/RGB_LED_Shield/simple/simple.ino
//#define PIN   16    // wemos esp32 pin 16
#define PIN   D4  // wemos d1 mini esp8266     BUILD with "LOLIN(WEMOS) D1 R2 & mini"
#define LED_NUM 7

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel leds = Adafruit_NeoPixel(LED_NUM, PIN, NEO_GRB + NEO_KHZ800);

boolean on = false;
void mqtt_callback_fn(const char* topic, byte* payload, unsigned int length) {
  Serial.printf("Callback: %s\n", topic);

  on = ! on;  
//  flashRandom(15, 3);
//  flashRandom(15, 2);
//  flashRandom(15, 1);
}

#define BRIGHT 160

void setup() {
  //while (!Serial);
  Serial.begin(115200);
  Serial.printf("Started\n");

  mqtt.setCallback(mqtt_callback_fn);
  mqtt.setup();

  // initialize the LED pin as an output:
  //pinMode(ledPin, OUTPUT);
  // turn off the cpu board led
  //digitalWrite(ledPin, HIGH);

  
  leds.begin(); // This initializes the NeoPixel library.
  leds.setBrightness(BRIGHT);
  leds.show();                //Set all pixels to "off"

}

void led_set(uint8_t R, uint8_t G, uint8_t B) {
  for (int i = 0; i < LED_NUM; i++) {
    leds.setPixelColor(i, leds.Color(R, G, B));
    leds.show();
    delay(50);
  }
}

boolean initialised = false;
int colour = 0;


void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  mqtt.loop();

  if (colour > 4) {
    colour = 0;
  }

  if (!initialised) {
    led_set(0, 0, 0);
  
    delay(1);
    initialised = mqtt.subscribe("esp8266-84f3eb3b74a6", "button", "pushed");
    Serial.printf("loop Subscription returned: %s\n", initialised ? "true" : "false");
    // esp8266-84f3eb3b74a6/button/pushed
    for (int i = 0; i < 20; i++) {
      pixie_dust(colour);
      delay(2);
    }
    colour++;
  }
  if (on) {
    Serial.printf("pixie_dust");
    for (int i = 0; i < 20; i++) {
      pixie_dust(colour);
      delay(2);
    }
    colour++;
  }
}


// from https://learn.adafruit.com/neopixel-pixie-dust-bag/arduino-code
    #define DELAY_MILLIS 10  // delay between blinks, smaller numbers are faster 
    #define DELAY_MULT 8     // Randomization multiplier on the delay speed of the effect
    #define BRIGHT 100        // Brightness of the pixels, max is 255
     
    bool oldState = HIGH; //sets the initial variable for counting touch sensor button pushes
     
    void pixie_dust(int showColor) {
      int RColor = 100; //color (0-255) values to be set by cylcing touch switch, initially GOLD
      int GColor = 0 ;
      int BColor = 0 ;
      
           if (showColor==0) {//Garden PINK
             RColor = 242;
             GColor = 90;
             BColor = 255; 
           }
           if (showColor==1) {//Pixie GOLD
             RColor = 255;
             GColor = 222;
             BColor = 30; 
           }
           if (showColor==2) {//Alchemy BLUE
             RColor = 50;
             GColor = 255;
             BColor = 255; 
           }
           if (showColor==3) {//Animal ORANGE
             RColor = 255;
             GColor = 100;
             BColor = 0; 
           }
           if (showColor==4) {//Tinker GREEN
             RColor = 0;
             GColor = 255;
             BColor = 40; 
           }
      
      //sparkling
      int p = random(LED_NUM); //select a random pixel
      leds.setPixelColor(p,RColor,GColor,BColor); //color value comes from cycling state of momentary switch
      leds.show();
      delay(DELAY_MILLIS * random(DELAY_MULT) ); //delay value randomized to up to DELAY_MULT times longer
      int dim = 20;
      leds.setPixelColor(p, RColor/dim, GColor/dim, BColor/dim); //set to a dimmed version of the state color
      leds.show();
      int moredim = 50;
      leds.setPixelColor(p+1, RColor/moredim, GColor/moredim, BColor/moredim); //set a neighbor pixel to an even dimmer value
      leds.show();
      
//      //button check to cycle through color value sets
//      bool newState = digitalRead(TOUCH_PIN); //Get the current button state
//      // Check if state changed from high to low (button press).
//      if (newState == LOW && oldState == HIGH) {
//        // Short delay to debounce button.
//        delay(20);
//        // Check if button is still low after debounce.
//        newState = digitalRead(TOUCH_PIN);
//        if (newState == LOW) {
//          showColor++;
//          if (showColor > 4)
//            showColor=0;
//           }   
//      }
      // Set the last button state to the old state.
//      oldState = newState;  
      
    }



// from https://learn.adafruit.com/sparkle-skirt/code-battery
// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                                  R   G   B
uint8_t myFavoriteColors[][3] = {
                               //  {146,   0, 146},   // purple
                               //  {146,   0,  0},   // red 
                               //  {146,   146,  146},   // white 
                               //  {255,   215,  0},   // lemon yellow? 
                                 {255,   222,  30},   // Pixie GOLD
                               //  {50, 255, 255},    // Alchemy BLUE
                                 {255, 100, 0},     // Animal Orange 
                               //  {0,    0, 146},   // blue
                               };
// don't edit the line below
#define FAVCOLORS sizeof(myFavoriteColors) / 3

// first number is 'wait' delay, shorter num == shorter twinkle
// second number is how many neopixels to simultaneously light up
void flashRandom(int wait, uint8_t howmany) {
 
  for(uint16_t i=0; i<howmany; i++) {
    // pick a random favorite color!
    int c = random(FAVCOLORS);
    int red = myFavoriteColors[c][0];
    int green = myFavoriteColors[c][1];
    int blue = myFavoriteColors[c][2]; 
 
    // get a random pixel from the list
    int j = random(leds.numPixels());
    //Serial.print("Lighting up "); Serial.println(j); 
    
    // now we will 'fade' it in 5 steps
    for (int x=0; x < 5; x++) {
      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;
      
      leds.setPixelColor(j, leds.Color(r, g, b));
      leds.show();
      delay(wait);
    }
    // & fade out in 5 steps
    for (int x=5; x >= 0; x--) {
      int r = red * x; r /= 5;
      int g = green * x; g /= 5;
      int b = blue * x; b /= 5;
      
      leds.setPixelColor(j, leds.Color(r, g, b));
      leds.show();
      delay(wait);
    }
  }
  // LEDs will be off when done (they are faded to 0)
}
