/*
This is un example howto use Touch Intrrerupts
The bigger the threshold, the more sensible is the touch
*/

#include <WiFi.h>
#include <PubSubClient.h>

const char* SSID="ASUS";
const char* PASS="MEGA SHED";
const char* MQTT="10.10.11.3";
const char* TOPIC="status/touch/";
WiFiClient espWifi;
PubSubClient client(espWifi);

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
  setup_wifi();
  delay(1000); // give me time to bring up serial monitor
  client.setServer(MQTT, 1883);
  
  Serial.println("ESP32 Touch Interrupt Test");
  touchAttachInterrupt(T0, gotTouch0, threshold);
//  touchAttachInterrupt(T1, gotTouch1, threshold); // Attached to the reset button, so won't work as capacitive
  touchAttachInterrupt(T2, gotTouch2, threshold);
}

void loop(){
  mqtt();

  if(touch0detected){
    touch0detected = false;
    Serial.printf("Touch 0 (pin %d) detected\n", T0);
    client.publish("status/esp32/touch", "0");
  }
  if(touch1detected){
    touch1detected = false;
    Serial.printf("Touch 1 (pin %d) detected\n", T1);
    client.publish("status/esp32/touch", "2");
  }
  if(touch2detected){
    touch2detected = false;
    Serial.printf("Touch 2 (pin %d) detected\n", T2);
    client.publish("status/esp32/touch", "2");
  }
  Serial.printf("w %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n", touchRead(T0), touchRead(T1), touchRead(T2), touchRead(T3), touchRead(T4), touchRead(T5), touchRead(T6), touchRead(T7), touchRead(T8), touchRead(T9));  // get value using T0
  delay(1000);
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

