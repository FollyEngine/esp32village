/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald

 modified for the ESP32 on March 2017
 by John Bennett

 see http://www.arduino.cc/en/Tutorial/Sweep for a description of the original code

 * Added mqtt callback to set servo position

 */

#include <ESP32Servo.h>
#include "mqtt.h"
Mqtt mqtt = Mqtt("ASUS", "MEGA SHED", "10.10.11.2", 1883);

Servo myservo;  // create servo object to control a servo
                // 16 servo objects can be created on the ESP32

int pos = 0;    // variable to store the servo position
// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 22;
char buffer[256];

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  pos = atoi((char*) payload);
  // get pos back within 0 to 180
  while (pos > 178) { pos = 178;}
  while (pos < 1) { pos = 1;}

  myservo.write(pos);              // tell servo to go to position in variable 'pos'

  snprintf(buffer, 255, "%d", pos);
  mqtt.publish("status/servo/position", buffer);
}


void setup() {
  while (!Serial);
  Serial.begin(115200);
  Serial.printf("Started\n");

  mqtt.setCallback(callback);
  mqtt.setup();

  myservo.attach(servoPin);   // attaches the servo on pin 18 to the servo object
                              // using default min/max of 1000us and 2000us
                              // different servos may require different min/max settings
                              // for an accurate 0 to 180 sweep
}

void loop() {
  if (!mqtt.loop()) {
    mqtt.subscribe("cmnd/servo/position");
  }
}

