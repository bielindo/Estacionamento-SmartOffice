//Sistema de Monitoramento de vagas - SmartOffice PTI (Parque tecnologico de Itaipu)
//Desenvolvidores: Gabriel Pereira de Araújo e Sofia Zanette Rovaris
//Desenvolvido em : 27/05/2022

#ifndef ESTRUTURA_H
#define ESTRUTURA_H

//Define as cores dos leds
#define LARANJA Adafruit_NeoPixel::Color(50, 255, 0)
#define VERMELHO Adafruit_NeoPixel::Color(0, 255, 0)
#define VERDE Adafruit_NeoPixel::Color(255, 0, 0)

//Define quantos leds serao acessos na fita de Led
#define QTD_LEDS 25

//Define a quantidade de sensores que serao utilizados (min 1 - max 4)
#define QTD_SENSORES 4

//Definição dos valores da conta dos dados coletados dos sensores, deixando mais preciso com esses valores
#define DIVISOR 58.0
#define INTERVALOR_MEDIDA 5
#define QTD_MEDIDAS 10

//Definicao dos valores que serão publicados no MQTT
#define ESTA_OCUPADO "ocupado"
#define NAO_ESTA_OCUPADO "vago"

#endif