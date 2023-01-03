#include "mqtt.h"
#include "../sensor/jsnsr04t.h"

WiFiClient wifiClient;
PubSubClient mqttClient(RASP_BROKER_IP, PORTA, callback, wifiClient);

void Mqtt::enviaDados(int indice){
    //printf("enviando dado... indice: %d\n", indice);
    String anterior = sensores[indice].getEstado();
    if(sensores[indice].getDistancia() <=140){
        sensores[indice].setEstado(ESTA_OCUPADO);
        sensores[indice].mudaCorFitaSensor(VERMELHO);
    }else{
        sensores[indice].setEstado(NAO_ESTA_OCUPADO);
        sensores[indice].mudaCorFitaSensor(sensores[indice].getCor());
    }
    
    if(mqttClient.connected()){
        printf("enviando dado... indice: %d\n", indice);
        String vaga;
        switch (indice){
        case 0:
            vaga = "881787";
        break;
        case 1:
            vaga = "913371";
        break;
        case 2:
            vaga = "252117";
        break;
        case 3:
            vaga = "894106";
        break;
        default:
            break;
        }
        String topico = "/paraki/Carcara/Vaga" + vaga;
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

    if(!strcmp(topic, "/paraki/Carcara/Vaga881787/reservado")){
        if(!strcmp(buffer,"sim")){
            sensores[0].setCor(LARANJA);
        }else if(!strcmp(buffer,"nao")){
            sensores[0].setCor(VERDE);
        }
    }else if (!strcmp(topic, "/paraki/Carcara/Vaga913371/reservado")) {
        if(!strcmp(buffer,"sim")){
             
            sensores[1].setCor(LARANJA);
        }else if(!strcmp(buffer,"nao")){
            sensores[1].setCor(VERDE);
        }
    }else if (!strcmp(topic, "/paraki/Carcara/Vaga252117/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[2].setCor(LARANJA);
        }else if(!strcmp(buffer,"nao")){
            sensores[2].setCor(VERDE);
        }
    }else if (!strcmp(topic, "/paraki/Carcara/Vaga894106/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[3].setCor(LARANJA);
        }else if(!strcmp(buffer,"nao")){
            sensores[3].setCor(VERDE);
        }
    }
}

void Mqtt::reconnect(){
    printf("Connectando ao Broker MQTT...\n");
    while (!mqttClient.connected()) {
        printf("Reconectando to Broker MQTT...\n");
        mqttClient.publish("/mva/dispositivo2/internet", "e", 1);
        if (mqttClient.connect("testecores")) {
            printf("Connected.\n");
            //se inscreve nos tópicos necessários para receber os dados de reserva de vagas
            mqttClient.subscribe("/paraki/Carcara/Vaga881787/reservado");
            mqttClient.subscribe("/paraki/Carcara/Vaga913371/reservado");
            mqttClient.subscribe("/paraki/Carcara/Vaga252117/reservado");
            mqttClient.subscribe("/paraki/Carcara/Vaga894106/reservado");
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