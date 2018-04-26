/*
This is un example howto use Touch Intrrerupts
The bigger the threshold, the more sensible is the touch
*/

#include "mqtt.h"

Mqtt mqtt = Mqtt("ASUS", "MEGA SHED", "10.10.11.2", 1883);

int threshold = 40;
bool touch0detected = false;
bool touch1detected = false;
bool touch2detected = false;

void gotTouch0(){
 touch0detected = true;
}

void gotTouch1(){
 touch1detected = true;
}

void gotTouch2(){
 touch2detected = true;
}

void setup() {
  Serial.begin(115200);
  mqtt.setup();
  delay(1000); // give me time to bring up serial monitor
  
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(T0, gotTouch0, threshold);
//  touchAttachInterrupt(T1, gotTouch1, threshold); // Attached to the reset button, so won't work as capacitive
  touchAttachInterrupt(T2, gotTouch2, threshold);
}

void loop(){
  mqtt.loop();

  if(touch0detected){
    touch0detected = false;
    Serial.printf("Touch 0 (pin %d) detected\n", T0);
    mqtt.publish("status/esp32/touch", "0");
  }
  if(touch1detected){
    touch1detected = false;
    Serial.printf("Touch 1 (pin %d) detected\n", T1);
    mqtt.publish("status/esp32/touch", "2");
  }
  if(touch2detected){
    touch2detected = false;
    Serial.printf("Touch 2 (pin %d) detected\n", T2);
    mqtt.publish("status/esp32/touch", "2");
  }
  Serial.printf("w %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", touchRead(T0), touchRead(T1), touchRead(T2), touchRead(T3), touchRead(T4), touchRead(T5), touchRead(T6), touchRead(T7), touchRead(T8), touchRead(T9));  // get value using T0
  delay(1000);
}