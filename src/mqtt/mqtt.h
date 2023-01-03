#ifndef MQTT_H
#define MQTT_H

#include "../estrutura/estrutura.h"
#include <PubSubClient.h>
#include <WiFi.h>

#define RASP_BROKER_IP "200.201.88.141"
#define PORTA 1883

#define SSIDRASP "SmartPTI"
#define PASS "SmartPT12017."

extern WiFiClient wifiClient;
extern PubSubClient mqttClient;

void callback(char* topic, byte* message, unsigned int length);

class Mqtt{
public:
    void enviaDados(int indice);
    void reconnect();
    void wifiConnect();
};

#endif