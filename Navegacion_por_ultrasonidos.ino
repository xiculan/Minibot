//Librerias
#include "SR04.h"
//Variables
long DistI;
long DistM;
long DistD;
int Vmin = 130;
int Vmed = 200;
int Vmax = 255;
//Pines
#define TRIG_PIN1 3
#define ECHO_PIN1 2
SR04 SIzquierda = SR04(ECHO_PIN1,TRIG_PIN1);
#define TRIG_PIN2 5
#define ECHO_PIN2 4
SR04 SMedio = SR04(ECHO_PIN2,TRIG_PIN2);
#define TRIG_PIN3 6
#define ECHO_PIN3 7
SR04 SDerecha = SR04(ECHO_PIN3,TRIG_PIN3);

#define MotorI1 10
#define MotorI2 11
#define MotorD1 12
#define MotorD2 13

void Variador_velocidad(){
  if (DistM < 20){
    analogWrite(MotorI1, Vmin);
    analogWrite(MotorD1, Vmin);
    Serial.println("Adelante min");
  }
  else if (DistM < 30){
    analogWrite(MotorI1, Vmed);
    analogWrite(MotorD1, Vmed);
    Serial.println("Adelante med");
  }
  else if (DistM >= 30){
    analogWrite(MotorI1, Vmax);
    analogWrite(MotorD1, Vmax);
    Serial.println("Adelante max");
  }
  analogWrite(MotorI1, 0);
  analogWrite(MotorD1, 0);
  
}

void setup() {
  Serial.begin(9600);
  pinMode(MotorI1, OUTPUT);
  pinMode(MotorD1, OUTPUT);
  pinMode(MotorI2, OUTPUT);
  pinMode(MotorD2, OUTPUT);

}

void loop() {
  //pedimos las 3 distancias para poder empezar a comparar
  //DistI=SIzquierda.Distance();
  DistM=SMedio.Distance();
  //DistD=SDerecha.Distance();
  DistI= 100;  //Anulamos los sensores de los lados hasta colocarlos
  DistD= 100;

  if (DistM < 10){
    analogWrite(MotorI1, 0);
    analogWrite(MotorD1, 0);
    if (DistI > DistD){
      Serial.println("Girando Izquierda");
      analogWrite(MotorI2, Vmin);
      analogWrite(MotorD1, Vmin);
      delay(300);    // Provisional
      analogWrite(MotorD1, 0);
      analogWrite(MotorI2, 0);
    }
    else if (DistI < DistD){
      Serial.println("Girando Derecha");
      analogWrite(MotorI1, Vmin);
      analogWrite(MotorD2, Vmin);
      delay(300);    // Provisional
      analogWrite(MotorD2, 0);
      analogWrite(MotorI1, 0);
    }
    else{
      Serial.println(DistM);
    }
  }
  else {
    Variador_velocidad();
  }
  delay(200);
}




















