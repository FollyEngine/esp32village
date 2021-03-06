

#include "mqtt.h"

#include <Time.h>
#include <NtpClientLib.h>

Mqtt::Mqtt(
		const char *SSID,
		const char *PASS,
		const char *Mqttserver,
		int Mqttport,
		const char *MqttUser,
		const char *MqttPass,
		const char *object
) {
  Mqtt(SSID, PASS, Mqttserver, Mqttport, object);

  m_MqttUser = (char*) malloc(strlen(MqttUser) + 1);
  strcpy(m_MqttUser, MqttUser);
  m_MqttPass = (char*) malloc(strlen(MqttPass) + 1);
  strcpy(m_MqttPass, MqttPass);
}

Mqtt::Mqtt(const char *SSID, const char *PASS, const char *Mqttserver, int Mqttport, const char *object) {
  m_SSID = (char*) malloc(strlen(SSID) + 1);
  strcpy(m_SSID, SSID);
  m_PASS = (char*) malloc(strlen(PASS) + 1);
  strcpy(m_PASS, PASS);
  m_MQTTServer = (char*) malloc(strlen(Mqttserver) + 1);
  strcpy(m_MQTTServer, Mqttserver);
  m_MQTTPort = Mqttport;
  m_MqttUser = NULL;
  m_MqttPass = NULL;
  m_Object = (char*) malloc(strlen(object) + 1);
  strcpy(m_Object, object);
}

void Mqtt::setCallback(MQTT_CALLBACK_SIGNATURE) {
  this->callback = callback;
  if (client.connected()) {
    client.setCallback(this->callback);
  }
}

const char *Mqtt::getHostname() {
  return m_Hostname;
}

const char *Mqtt::getObject() {
  return m_Object;
}


void Mqtt::setup() {
    client = PubSubClient(espWifi);
    delay(10);

    WiFi.begin(m_SSID, m_PASS);

    uint8_t mac[6];
    WiFi.macAddress(mac);
#ifdef ESP8266
    char *hostPrefix = "esp8266";
#else
    char *hostPrefix = "esp32";
#endif
    snprintf(m_Hostname, 255, "%s-%x%x%x%x%x%x", hostPrefix, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

#ifndef ESP8266
    // TODO: does this exist in some other way?
    WiFi.setHostname(m_Hostname);
#endif
    while (WiFi.status() != WL_CONNECTED) {
      Serial.println(".");
      delay(500);
    }

    Serial.println("Setup Wifi Connected:");
    Serial.println( WiFi.localIP());

    NTP.begin (); // Only statement needed to start NTP sync.
    //timeZone = 0;
    //minutesTimeZone = 0;
    //NTP.begin ("pool.ntp.org", timeZone, true, minutesTimeZone);
    //NTP.setInterval (63);

    Serial.printf("Host %s, Port %d", m_MQTTServer, m_MQTTPort);
    client.setServer(m_MQTTServer, m_MQTTPort);
    client.setCallback(callback);
  };


bool Mqtt::loop() {
    bool reInit = true;
    while (!client.connected()) {
      reInit = false;
      while (!client.connected()) {
        Serial.println("Wifi Connected:");
        Serial.println( WiFi.localIP());
        Serial.println( m_Hostname);

	if (m_MqttPass == NULL) {
          client.connect(m_Hostname);
        } else {
          Serial.printf("Host %s, Port %d", m_MQTTServer, m_MQTTPort);
          boolean ok = client.connect(m_Hostname, m_MqttUser, m_MqttPass);
          Serial.printf("MQTT: %s", (ok?"true":"false"));
        }
        Serial.println("+");
      }
      client.setCallback(callback);
    }
    client.loop();

    if (client.connected()) {
      time_t time_now = now();
      if (time_now - m_lastStatus > (STATUSRATE)) {
        m_lastStatus = time_now;

        StaticJsonBuffer<300> jsonBuffer;
        JsonObject& root = jsonBuffer.createObject();
        status(root);
      }
    }

    return reInit;
  };

  void Mqtt::publishString(const char *object, const char *verb, const char *message) {
    char topic[81];
    snprintf(topic, 80, "%s/%s/%s", m_Hostname, object, verb);
    client.publish(topic, message);
  };

  void Mqtt::publish(const char *object, const char *verb, JsonObject& root) {
    char str[201];
    // TODO: only set it if its not already set
    root["device"] = String(object);
    // TODO: only set it if its not already set
    time_t t = now();
    //2018-11-17T06:52:44.747234
    snprintf(str, 100, "%d-%02d-%02dT%02d:%02d:%02d", year(t), month(t), day(t), hour(t), minute(t), second(t));
    root["time"] = String(str);

    root.printTo(str, 200);
    publishString(object, verb, str);
  };

  //String hello = String("hello");
  char str[301];
  void Mqtt::status(JsonObject& root) {
    // TODO: only set it if its not already set
    root["ip"] = WiFi.localIP().toString();
//    root["device"] = String(m_Object);
    root["from"] = String(m_Hostname);
    root["ping"] = String(m_Object);

    // TODO: only set it if its not already set
    time_t t = now();
    //2018-11-17T06:52:44.747234
    snprintf(str, 100, "%d-%02d-%02dT%02d:%02d:%02d", year(t), month(t), day(t), hour(t), minute(t), second(t));
    root["time"] = String(str);

    root.printTo(str, 300);
    statusString(str);
  };


  const char *status_topic = "node-red/status/ping";
  void Mqtt::statusString(const char *message) {
//    snprintf(status_topic, 80, "%s/%s/%s", m_Hostname, m_Object, "status");
    client.publish(status_topic, message, true);
  };

// TODO: need to add a callback...
boolean Mqtt::subscribe(const char *host, const char *object, const char *verb) {
    char topic[81];
    snprintf(topic, 80, "%s/%s/%s", host, object, verb);
    return client.subscribe(topic);
  };
