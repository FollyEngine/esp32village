

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

void Mqtt::setHostname(char *name) {
  strncpy(m_Hostname, name, 255);
}


void Mqtt::setup() {
    client = PubSubClient(espWifi);
    delay(10);

    WiFi.begin(m_SSID, m_PASS);

    uint8_t mac[6];
    WiFi.macAddress(mac);
    snprintf(m_Hostname, 255, "esp32-%x%x%x%x%x%x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    WiFi.setHostname(m_Hostname);
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

bool Mqtt::loop() {
    bool reInit = true;
    while (!client.connected()) {
      reInit = false;
      while (!client.connected()) {
        Serial.println("Connected:");
        Serial.println( WiFi.localIP());
        Serial.println( WiFi.getHostname());

        client.connect(WiFi.getHostname());
        Serial.println("+");
      }
      char topic[81];
      snprintf(topic, 80, "status/%s/mqtt", WiFi.getHostname());
      client.publish(topic, "connected");
    }
    client.loop();
    return reInit;
  };

void Mqtt::publish(const char *topic, const char *message) {
    client.publish(topic, message);
  };

void Mqtt::subscribe(const char *topic) {
    client.subscribe(topic);
  };