//Sistema de Monitoramento de vagas - SmartOffice PTI (Parque tecnologico de Itaipu)
//Desenvolvidores: Gabriel Pereira de Araújo e Sofia Zanette Rovaris
//Desenvolvido em : 27/05/2022

#ifndef MQTT_H
#define MQTT_H

#include "../estrutura/estrutura.h"
#include <PubSubClient.h>
#include <WiFi.h>

//Define o IP e a porta do Broker para o MQTT
#define RASP_BROKER_IP "200.201.88.141"
#define PORTA 1883

//Define a o Wi-fi e a Senha que o esp ira se conectar
#define SSIDRASP "SmartPTI"
#define PASS "SmartPT12017."

extern WiFiClient wifiClient;
extern PubSubClient mqttClient;

//Função que identifica se as vagas foram reservadas, caso reservadas alteram a cor do led para laranja
// e publicam no topico do sersor que a vaga esta reservada.
void callback(char* topic, byte* message, unsigned int length);

class Mqtt{
public:
    //Funcao que verifica qual sera o estado da vaga de acordo com os dados recebidos do sensor
    //apos isso ela publica no topico do sensor qual e seu estado.
    void enviaDados(int indice);//indice é de acordo com a quantidade de sensores que tem (0 - 3)

    //Funcao para reconectar o Wi-fi no esp
    void reconnect();

    //Funcao para conectar o Wi-fi no esp
    void wifiConnect();
};

#endif