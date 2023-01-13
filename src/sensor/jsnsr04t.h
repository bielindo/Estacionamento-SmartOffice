//Sistema de Monitoramento de vagas - SmartOffice PTI (Parque tecnologico de Itaipu)
//Desenvolvidores: Gabriel Pereira de Araújo e Sofia Zanette Rovaris
//Desenvolvido em : 27/05/2022

#ifndef JSNSR04T_H
#define JSNSR04T_H

#include <Arduino.h>
#include "../estrutura/estrutura.h"
#include <Adafruit_NeoPixel.h>
#include <array>

class Jsnsr04t : public Adafruit_NeoPixel {
protected:
    int8_t pinTrigger;
    int8_t pinEcho;
    float distancia;
    String estado;
    int32_t cor;

public:
//    -------------- Getters e Setters --------------
    float getDistancia() const;
    String getEstado() const;
    int32_t getCor() const;

    void setDistancia(float distancia);
    void setEstado(String estado);
    void setCor(int32_t cor);

    //construtor
    Jsnsr04t(int8_t trigger, int8_t echo, int dado);

    //Funcao que inicializa os sensores
    void inicializaSensor();

    //Funcao que inicializa os LEDs
    void inicializaLeds();

    //Funcao que calcula a distancia com uma media entre as leituras, buscando uma melhor precisao
    void calcularDistancia();

    //Funcao que coleta a leitura dos sensores bruto, fazendo a divisao em um valor proximo a precisao de centimetros
    float leituraSensor();

    //Funcao que altera as cores dos Leds
    void mudaCorFitaSensor(int32_t cor);
};

extern Jsnsr04t sensores[QTD_SENSORES];

#endif