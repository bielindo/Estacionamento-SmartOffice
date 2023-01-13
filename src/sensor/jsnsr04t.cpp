//Sistema de Monitoramento de vagas - SmartOffice PTI (Parque tecnologico de Itaipu)
//Desenvolvidores: Gabriel Pereira de Araújo e Sofia Zanette Rovaris
//Desenvolvido em : 27/05/2022

#include "jsnsr04t.h"

//Classe dos sensores
Jsnsr04t sensores[QTD_SENSORES] = {
  Jsnsr04t(4,2,18), // Paramentros (Trigger, echo, LED)
  Jsnsr04t(22,23,19),
  Jsnsr04t(33,32,25),
  Jsnsr04t(13,12,14)
};

//construtor
Jsnsr04t::Jsnsr04t(int8_t trigger, int8_t echo, int dado) : Adafruit_NeoPixel(QTD_LEDS, dado, NEO_RGBW + NEO_KHZ800){
    this->pinTrigger = trigger;
    this->pinEcho = echo;
    this->distancia = 0;
    this->estado = NAO_ESTA_OCUPADO;
    this->cor = VERDE;
}

//Inicializa os Leds
void Jsnsr04t::inicializaLeds(){
    begin();
    setBrightness(50);
}

//Incicializa os sensores
void Jsnsr04t::inicializaSensor() {
  pinMode(this->pinTrigger, OUTPUT); 
  pinMode(this->pinEcho, INPUT);
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(500);
}

//Funcao que calcula a distancia com uma media entre as leituras, buscando uma melhor precisao
void Jsnsr04t::calcularDistancia(){
  float leituraSum = 0;
  float resultado = 0;
  
  for (int index = 0; index < QTD_MEDIDAS; index++) {
    delay(INTERVALOR_MEDIDA);
    leituraSum += leituraSensor();
  }

  this->distancia = (float) leituraSum / QTD_MEDIDAS;
  this->distancia = this->distancia + 2.2;
}

//Funcao que coleta a leitura dos sensores bruto, fazendo a divisao em um valor proximo a precisao de centimetros
float Jsnsr04t::leituraSensor() {
  long duracao = 0; 
  float resultado = 0;
  
  digitalWrite(this->pinTrigger, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(this->pinTrigger, LOW);

  duracao = pulseIn(this->pinEcho, HIGH);

  resultado = ((float) duracao / DIVISOR);
  
  return resultado;
}

//Funcao que altera as cores dos Leds
void Jsnsr04t::mudaCorFitaSensor(int32_t cor){
    fill(cor, 0, QTD_LEDS);
    show();
}

// -------------- Getters e Setters --------------
float Jsnsr04t::getDistancia() const{
    return this->distancia;
}

String Jsnsr04t::getEstado() const{
    return this->estado;
}

int32_t Jsnsr04t::getCor() const{
    return this->cor;
}

void Jsnsr04t::setEstado(String estado){
    this->estado = estado;
}

void Jsnsr04t::setCor(int32_t cor){
    this->cor = cor;
}
void Jsnsr04t::setDistancia(float distancia){
    this->distancia = distancia;
}