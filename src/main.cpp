#include <Arduino.h>
#include "./sensor/jsnsr04t.h"
#include "./mqtt/mqtt.h"

Mqtt mqtt;

void setup() {
  Serial.begin(115200);
  printf("Setup...\n");
  mqtt.wifiConnect();
  mqtt.reconnect();
  printf("--------\n");
  for (int i = 0; i < QTD_SENSORES; i++) {
    sensores[i].inicializaSensor();
    sensores[i].inicializaLeds();
  }
}

void loop() {
  if (!mqttClient.connected()) {
    printf("Reconectando...\n");
    mqtt.reconnect();
  }
  
  for (int i = 0; i < QTD_SENSORES; i++) {
    sensores[i].calcularDistancia();
    printf("Distância %d sensor: %lf\n", i, sensores[i].getDistancia());
    mqtt.enviaDados(i);
  }
  mqttClient.loop();
  delay(5);
}