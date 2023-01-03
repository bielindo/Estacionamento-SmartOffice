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
    //getters
    float getDistancia() const;
    String getEstado() const;
    int32_t getCor() const;
    //int getTempo();

    //setters
    void setDistancia(float distancia);
    void setEstado(String estado);
    void setCor(int32_t cor);
    //void setTempo(int tempo);

    //construtor
    Jsnsr04t(int8_t trigger, int8_t echo, int dado);

    //funcoes
    void inicializaSensor();
    void inicializaLeds();
    void calcularDistancia();
    float leituraSensor();
    void mudaCorFitaSensor(int32_t cor);
};

extern Jsnsr04t sensores[QTD_SENSORES];

#endif