/*
  Button

  Turns on and off a light emitting diode(LED) connected to digital pin 13,
  when pressing a pushbutton attached to pin 2.

  The circuit:
  - LED attached from pin 13 to ground
  - pushbutton attached to pin 2 from +5V
  - 10K resistor attached to pin 2 from ground

  - Note: on most Arduinos there is already an LED on the board
    attached to pin 13.

  created 2005
  by DojoDave <http://www.0j0.org>
  modified 30 Aug 2011
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Button
*/

#include <WiFi.h>
#include <PubSubClient.h>

const char* SSID="ASUS";
const char* PASS="MEGA SHED";
const char* MQTT="10.10.11.3";
const char* TOPIC="status/touch/";
WiFiClient espWifi;
PubSubClient client(espWifi);

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 36;     // the number of the pushbutton pin
const int ledPin =  BUILTIN_LED;      // the number of the LED pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status

void setup() {
  setup_wifi();
  delay(1000); // give me time to bring up serial monitor
  client.setServer(MQTT, 1883);
  
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  mqtt();

  // read the state of the pushbutton value:
  int nextButtonState = digitalRead(buttonPin);
  // TODO: need to debounce

  if (nextButtonState != buttonState) {
    // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
    if (nextButtonState == HIGH) {
      // turn LED on:
      digitalWrite(ledPin, HIGH);
      client.publish("status/esp32/button", "1");
    } else {
      // turn LED off:
      digitalWrite(ledPin, LOW);
      client.publish("status/esp32/button", "0");
    }
    buttonState = nextButtonState;
  }
}

void mqtt() {
  while (!client.connected()) {
    client.connect("testesp32");
    Serial.println("+");
  }
  client.loop();
}

void setup_wifi() {
  delay(10);
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println(".");
    delay(500);
  }
  Serial.println("Connected:");
  Serial.println( WiFi.localIP());
}
