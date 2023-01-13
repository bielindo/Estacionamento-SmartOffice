//Sistema de Monitoramento de vagas - SmartOffice PTI (Parque tecnologico de Itaipu)
//Desenvolvidores: Gabriel Pereira de Araújo e Sofia Zanette Rovaris
//Desenvolvido em : 27/05/2022

#include <Arduino.h>
#include "./sensor/jsnsr04t.h"
#include "./mqtt/mqtt.h"

Mqtt mqtt;

//Classe main

//Funcao que chama as funcoes para inicializar os dados dos leds e sensores
void setup() {
  Serial.begin(115200);
  mqtt.wifiConnect();
  printf("Inicializando sensores...\n");
  for (int i = 0; i < QTD_SENSORES; i++) {
    sensores[i].inicializaSensor();
    sensores[i].inicializaLeds();
  }
}

void loop() {

  mqtt.reconnect();
  
  for (int i = 0; i < QTD_SENSORES; i++) {//  Repete de acordo com a quantidade de sensores fazendo individualmente
    sensores[i].calcularDistancia();      //  os calculos de cada sensor.
    printf("Distância %d sensor: %lf\n", i, sensores[i].getDistancia()); //Print a distancia no serial
    mqtt.enviaDados(i); //Envia os dados para o MQTT
  }
  mqttClient.loop();
  delay(5);
}