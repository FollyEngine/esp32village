

#include "mqtt.h"


Mqtt::Mqtt(const char *SSID, const char *PASS, const char *Mqttserver, int Mqttport) {
  m_SSID = (char*) malloc(strlen(SSID) + 1);
  strcpy(m_SSID, SSID);
  m_PASS = (char*) malloc(strlen(PASS) + 1);
  strcpy(m_PASS, PASS);
  m_MQTTServer = (char*) malloc(strlen(Mqttserver) + 1);
  strcpy(m_MQTTServer, Mqttserver);
  m_MQTTPort = Mqttport;
}

void Mqtt::setCallback(MQTT_CALLBACK_SIGNATURE) {
  this->callback = callback;
}

void Mqtt::setup() {
    client = PubSubClient(espWifi);
    delay(10);
    WiFi.begin(m_SSID, m_PASS);
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println(".");
      delay(500);
    }
    Serial.println("Connected:");
    Serial.println( WiFi.localIP());
    client.setServer(m_MQTTServer, m_MQTTPort);
    if (callback != NULL) {
      client.setCallback(callback);
    }
  };

void Mqtt::loop() {
    while (!client.connected()) {
      while (!client.connected()) {
        client.connect("testesp32");
        Serial.println("+");
      }
      client.publish("status/esp32/mqtt", "connected");
    }
    client.loop();
  };

void Mqtt::publish(const char *topic, const char *message) {
    client.publish(topic, message);
  };

void Mqtt::subscribe(const char *topic) {
    client.subscribe(topic);
  };