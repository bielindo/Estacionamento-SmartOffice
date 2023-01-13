//Sistema de Monitoramento de vagas - SmartOffice PTI (Parque tecnologico de Itaipu)
//Desenvolvidores: Gabriel Pereira de Araújo e Sofia Zanette Rovaris
//Desenvolvido em : 27/05/2022

#include "mqtt.h"
#include "../sensor/jsnsr04t.h"


WiFiClient wifiClient;
PubSubClient mqttClient(RASP_BROKER_IP, PORTA, callback, wifiClient);

//Funcao que verifica qual sera o estado da vaga de acordo com os dados recebidos do sensor
//apos isso ela publica no topico do sensor qual e seu estado.
void Mqtt::enviaDados(int indice){ //indice e de acordo com a quantidade de sensores que tem (0 - 3)
    String anterior = sensores[indice].getEstado();
    if(sensores[indice].getDistancia() <=140){ //verifica se a distancia recebida do sensor e menor q 1 metro e 40 centimetos                                
        sensores[indice].setEstado(ESTA_OCUPADO); //se for menor identifica que possui um carro.

        sensores[indice].mudaCorFitaSensor(VERMELHO);// Muda a cor do led para vermelha

        sensores[indice].setCor(VERDE);//  Quando os carros sao reservados set a cor verde para o led nao ficar laranja

    }else{ //caso a distancia do sensor retorne maior que 1 metro e 40 centimetros
        sensores[indice].setEstado(NAO_ESTA_OCUPADO);// identifica que nao possui nenhum carro.
        sensores[indice].mudaCorFitaSensor(sensores[indice].getCor()); //muda a cor do led pra cor setada, inicialmente e settada como VERDE
    }
    
    if(mqttClient.connected()){
        std::string topico = "/MVA/dispositivo1/sensor" + std::to_string(indice);// topico que sera publicado no mqtt
        if(!(sensores[indice].getEstado() == anterior)){//verifica se nao e o mesmo estado para nao publicar varias vezes
            if(mqttClient.publish(topico.c_str(), sensores[indice].getEstado().c_str())){ // caso publique no topico, print no serial que enviou os dados.
                printf("Enviei dado\n");
            }else{
                printf("Não enviei dado\n");
            }
        }
    }
}

//Função que identifica se as vagas foram reservadas, caso reservadas alteram a cor do led para laranja
// e publicam no topico do sersor que a vaga esta reservada.
void callback(char* topic, byte* message, unsigned int length) {
    char buffer[length+1];
    memcpy(buffer, message, length);
    buffer[length] = '\0';

    if(!strcmp(topic, "/MVA/dispositivo1/sensor0/reservado")){
        if(!strcmp(buffer,"sim")){
            sensores[0].setCor(LARANJA);//Altera a cor do Led para laranja (reservado)
            mqttClient.publish("/MVA/dispositivo1/sensor0", "reservado"); //publica no topico do sensor 
        }                                                                 //que ele esta reservado.
        
    }else if (!strcmp(topic, "/MVA/dispositivo1/sensor1/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[1].setCor(LARANJA);//Altera a cor do Led para laranja (reservado)
            mqttClient.publish("/MVA/dispositivo1/sensor1", "reservado"); //publica no topico do sensor 
        }                                                                 //que ele esta reservado.

    }else if (!strcmp(topic, "/MVA/dispositivo1/sensor2/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[2].setCor(LARANJA);//Altera a cor do Led para laranja (reservado)
            mqttClient.publish("/MVA/dispositivo1/sensor2", "reservado"); //publica no topico do sensor 
        }                                                                 //que ele esta reservado.

    }else if (!strcmp(topic, "/MVA/dispositivo1/sensor3/reservado")) {
        if(!strcmp(buffer,"sim")){
            sensores[3].setCor(LARANJA);//Altera a cor do Led para laranja (reservado)
            mqttClient.publish("/MVA/dispositivo1/sensor3", "reservado"); //publica no topico do sensor 
    }                                                                 //que ele esta reservado.
}

//Funcao para reconectar o Wi-fi no esp
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

//Funcao para conectar o Wi-fi no esp
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