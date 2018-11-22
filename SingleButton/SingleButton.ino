#include "mqtt.h"

#include <ArduinoJson.h>


Mqtt mqtt = Mqtt("uhome", "WhatTheHe11", "mqtt", 1883);

// constants won't change. They're used here to set pin numbers:
// D3 is the LOLIN Wemos 1-Button Shield: https://wiki.wemos.cc/products:d1_mini_shields:1-button_shield
const int buttonPin = D3;     // the number of the pushbutton pin
//const int ledPin =  BUILTIN_LED;      // the number of the LED pin
const int ledPin =  LED_BUILTIN;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {

  //while (!Serial);
  Serial.begin(115200);
  Serial.printf("Started\n");

  mqtt.setHostname("Button1");
  mqtt.setup();

  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  mqtt.loop();

  // read the state of the pushbutton value:
  int nextButtonState = digitalRead(buttonPin);
  // TODO: need to debounce

  if (nextButtonState != buttonState) {
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (nextButtonState == HIGH) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      root["state"] = 1;
      mqtt.publish("button", "pushed", root);
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      root["state"] = 0;
      mqtt.publish("button", "pushed", root);
    }
    buttonState = nextButtonState;
  }
}
