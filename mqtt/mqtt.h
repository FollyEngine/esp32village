/*
  mqtt.h - Library for simplified use of PubSubClient.
  Created by Sven Dowideit, 2018.
  Released into the public domain.
*/
#ifndef Morse_h
#define Morse_h

#include <WiFi.h>
#include <PubSubClient.h>

class Mqtt
{
  public:
    Mqtt(const char *SSID, const char *PASS, const char *Mqttserver, int Mqttport);
    void setCallback(MQTT_CALLBACK_SIGNATURE);

    void setup();
    void loop();

    void publish(const char *topic, const char *message);
    void subscribe(const char *topic);
  private:
    char *m_SSID;
    char *m_PASS;
    char *m_MQTTServer;
    int m_MQTTPort;
    MQTT_CALLBACK_SIGNATURE;

    // I wonder if the WifiClient should be static
    WiFiClient espWifi;
    PubSubClient client;
};

#endif