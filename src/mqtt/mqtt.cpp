#include "mqtt.h"
#include "../sensor/jsnsr04t.h"

WiFiClient wifiClient;
PubSubClient mqttClient(RASP_BROKER_IP, PORTA, callback, wifiClient);

void Mqtt::enviaDados(int indice){
    String anterior = sensores[indice].getEstado();
    if(sensores[indice].getDistancia() <=140){
        sensores[indice].setEstado(ESTA_OCUPADO);
        sensores[indice].mudaCorFitaSensor(VERMELHO);
        sensores[indice].setCor(VERDE);
    }else{
        sensores[indice].setEstado(NAO_ESTA_OCUPADO);
        sensores[indice].mudaCorFitaSensor(sensores[indice].getCor());
    }
    
    if(mqttClient.connected()){
        std::string topico = "/MVA/dispositivo1/sensor" + std::to_string(indice);
        if(!(sensores[indice].getEstado() == anterior)){ //aproximadamente 1 minuto
            if(mqttClient.publish(topico.c_str(), sensores[indice].getEstado().c_str())){
                printf("Enviei dado\n");
            }else{
                printf("Não enviei dado\n");
            }
        }
    }
}

void callback(char* topic, byte* message, unsigned int length) {
    printf("\n\nRecebi um dado*/*/*/*/*/*/*/*/*/*/\n");
    char buffer[length+1];
    memcpy(buffer, message, length);
    buffer[length] = '\0';

    if(!strcmp(topic, "/MVA/dispositivo1/sensor0/reservado")){
        if(!strcmp(buffer,"sim")){
            sensores[0].setCor(LARANJA);
            mqttClient.publish("/MVA/dispositivo1/sensor0", "reservado");
        }
    }else if (!strcmp(topic, "/MVA/dispositivo1/sensor1/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[1].setCor(LARANJA);
            mqttClient.publish("/MVA/dispositivo1/sensor1", "reservado");
        }
    }else if (!strcmp(topic, "/MVA/dispositivo1/sensor2/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[2].setCor(LARANJA);
            mqttClient.publish("/MVA/dispositivo1/sensor2", "reservado");
        }
    }else if (!strcmp(topic, "/MVA/dispositivo1/sensor3/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[3].setCor(LARANJA);
            mqttClient.publish("/MVA/dispositivo1/sensor3", "reservado");
        }
    }
}

void Mqtt::reconnect(){

    while (!mqttClient.connected()) {
        printf("Reconectando to Broker MQTT...\n");
        if (mqttClient.connect("conectado")) {
            printf("Connected.\n");
            //se inscreve nos tópicos necessários para receber os dados de reserva de vagas
            mqttClient.subscribe("/MVA/dispositivo1/sensor0/reservado");
            mqttClient.subscribe("/MVA/dispositivo1/sensor1/reservado");
            mqttClient.subscribe("/MVA/dispositivo1/sensor2/reservado");
            mqttClient.subscribe("/MVA/dispositivo1/sensor3/reservado");
        }
    }
}

void Mqtt::wifiConnect() {
    WiFi.begin(SSIDRASP, PASS);
    int time_lim = millis() + 10000;

    while ((WiFi.status() != WL_CONNECTED) && (millis() < time_lim)) {
        printf(".");
        delay(500);
    }

    if (WiFi.status() != WL_CONNECTED) {
        printf("Falha ao conectar!");
        delay(100);
        ESP.restart();
    }
    printf("Conectado\n");
    WiFi.mode(WIFI_STA);
}