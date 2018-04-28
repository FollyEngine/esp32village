#include "mqtt.h"

Mqtt mqtt = Mqtt("ASUS", "MEGA SHED", "10.10.11.2", 1883);

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 36;     // the number of the pushbutton pin
const int ledPin =  BUILTIN_LED;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {

  while (!Serial);
  Serial.begin(115200);
  Serial.printf("Started\n");
  
  mqtt.setup();
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  mqtt.loop();

  // read the state of the pushbutton value:
  int nextButtonState = digitalRead(buttonPin);
  // TODO: need to debounce

  if (nextButtonState != buttonState) {
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (nextButtonState == HIGH) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      mqtt.publish("status/esp32/button", "1");
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      mqtt.publish("status/esp32/button", "0");
    }
    buttonState = nextButtonState;
  }
}




