//Programa: Controlando o brilho de uma fita led, de acordo com a leitura da intensidade do som/música
//Autor: Eu

//https://adafruit.github.io/Adafruit_NeoPXL8/html/class_adafruit___neo_p_x_l8.html
//https://learn.adafruit.com/adafruit-neopixel-uberguide/arduino-library-use
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

int brilho = 0;
int nleds = 8; // Numero de LEDs na fita
int pinoLED = 6; // Pino que vai enviar os dados para a fita de LED
int pinoSom = A5; // Pino que recebe a saida analogica do sensor de som
//int pinoDigital = 7;

int meuDelay = 30;

//https://www.arduinoecia.com.br/2015/07/sensor-de-som-ky-038-microfone-arduino.html
int som = 0; 

int somMin;
int somMax; //1023= Valor maximo, para referencia.
int amplitude = 0;
float indice = 0;
float percentual = 0;

int corEscolhida = 0;
int vermelho;
int verde;
int azul;

Adafruit_NeoPixel pixels=Adafruit_NeoPixel(nleds,pinoLED,NEO_GRB+NEO_KHZ800); // Define com a biblioteca o tipo de fita de LEDs que voce esta usando

void setup()
{
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(0); // Passa para os LEDs o valor da variável brilho
  pixels.show();  
  pinMode(pinoSom, INPUT); // Define o pino de entrada do sensor de som
//  pinMode(pinoDigital, INPUT);
  somMin = analogRead(pinoSom); //Lê o valor da porta analógica do sensor de som
  somMax = somMin + 10;

  //loading: uma firula de inicio de código, só para incrementar...
  for (int j = 1; j < 7; j ++) {
    arcoIris(j, 40, nleds);
  }  
      
  //escolhendo a cor dos leds, randomicamente, entre as 7 cores do arco-iris
  //if (amplitude == 0) {  
    corEscolhida = (somMin % 7) + 1;
    arcoIris(corEscolhida, 10, nleds);
  //}
}

void loop(){
  som = analogRead(pinoSom); //Lê o valor da porta analógica do sensor de som
//  valor_D = digitalRead(pinoDigital);
  
  Serial.print("somA5: ");
  Serial.print(som);

//  Serial.print(" SaidaD0: ");
//  Serial.print(valor_D);

  Serial.print(" cor: ");
  Serial.print(corEscolhida);

  if (som > somMax) {
    somMax = som;
  }
  Serial.print(" somMax: ");
  Serial.print(somMax);
  
  if (somMin > som) {
    somMin = som;
  }
  Serial.print(" somMin: ");
  Serial.print(somMin);

  indice = (som - somMin);
  Serial.print(" indice: ");
  Serial.print(indice);

  amplitude = somMax - somMin;
  Serial.print(" amplitude: ");
  Serial.print(amplitude); 
  
  percentual = (indice / amplitude);
  Serial.print(" perc: ");
  Serial.print(percentual, 4);  
  
  brilho = 255 * percentual;
  Serial.print(" brilho: ");
  Serial.println(brilho);
 
  for (int i = 0; i < nleds; i++){
    pixels.begin();
    pixels.setBrightness(brilho); // Passa para os LEDs o valor da variável brilho
    pixels.setPixelColor(i, vermelho, verde, azul); //0, 150, 255: azulzinho
    pixels.show();
  }
}

void arcoIris(int cor, int tempoDelay, int leds) {
      switch (cor) {
        case 1: // vermelho
          vermelho =  255;
          verde =  0;
          azul =  0;
          break;
        case 2: // laranja
          vermelho =  255;
          verde =  127;
          azul =  10;
          break;
        case 3: // amarelo 
          vermelho =  255;
          verde =  255;
          azul =  0;
          break;
        case 4: // verde
          vermelho =  0;
          verde =  255;
          azul =  0;
            break;
        case 5: // azul 
          vermelho =  0;
          verde =  0;
          azul =  255;
          break;
        case 6: // indigo
          vermelho =  75;
          verde =  0;
          azul =  130;
          break;
        case 7: // roxo
          vermelho =  143;
          verde =  0;
          azul =  255;
        break;
      }

      for (int i = 0; i < leds; i++) {
        pixels.begin();
        pixels.setBrightness(255);        
        pixels.setPixelColor(i, vermelho, verde, azul);    
        pixels.show();
        delay(tempoDelay);
      }
}
