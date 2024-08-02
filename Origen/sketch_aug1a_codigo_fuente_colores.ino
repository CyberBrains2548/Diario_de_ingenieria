// codigo de fuente de colores 
#include <Servo.h>

// Pines del sensor ultrasónico
const int trigPin = 9;
const int echoPin = 10;

// Pines del puente H (Motor DC)
const int motorPin1 = 2;
const int motorPin2 = 4;
const int enablePin = 3;

// Servo motor MG996R
Servo servoMotor;
const int servoPin = 6;

// Pines del sensor de color TCS3200
const int S0 = 11;
const int S1 = 7;
const int S2 = 13;
const int S3 = 12;
const int sensorOut = 8;

// Definiciones de colores
#define RED 0
#define GREEN 1

// Variables para los valores de color
int redValue = 0;
int greenValue = 0;

// Variables para el ultrasonido
long duration;
int distance;

void setup() {
  // Configuración de pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Configuración de pines del puente H
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  analogWrite(enablePin, 175);  // Motor a máxima velocidad

  // Configuración del servo motor
  servoMotor.attach(servoPin);
  servoMotor.write(85); // Poner servo en posición inicial (recto)

  // Configuración del sensor de color TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Frecuencia de salida del sensor de color
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);

  // Pausa inicial antes de iniciar el movimiento
  delay(500); // Espera 500 ms antes de comenzar
}

void loop() {
  // Medir la distancia con el sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Si detecta un obstáculo a menos de 10 cm
  if (distance < 15) {
    retrocederCoche();  // Retroceder por un segundo

    // Leer color del objeto detectado
    redValue = leerColor(RED);
    greenValue = leerColor(GREEN);
    
    // Si detecta color verde
    if (greenValue > redValue) {
      girarDerecha();
    }
    // Si detecta color rojo
    else if (redValue > greenValue) {
      girarIzquierda();
    }
  } else {
    // Si no hay obstáculos, el coche avanza recto
    avanzarCoche();
  }
  
  delay(100);
}

void avanzarCoche() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  servoMotor.write(85); // Recto
}

void detenerCoche() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void retrocederCoche() {
  // Invertir la polaridad para retroceder
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  delay(1000); // Retroceder por 1 segundo
}

void girarDerecha() {
  servoMotor.write(105); // Girar a la derecha
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(1000); // Avanzar durante 1 segundo en la dirección del giro
  servoMotor.write(85); // Regresar el servo a la posición recta
  avanzarCoche(); // Continuar avanzando recto
}

void girarIzquierda() {
  servoMotor.write(65); // Girar a la izquierda
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  delay(1000); // Avanzar durante 1 segundo en la dirección del giro
  servoMotor.write(85); // Regresar el servo a la posición recta
  avanzarCoche(); // Continuar avanzando recto
}

int leerColor(int color) {
  switch (color) {
    case RED:
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      break;
    case GREEN:
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      break;
  }
  return pulseIn(sensorOut, LOW);
}

//  pruebas de obtaculos mas color 
#include <Servo.h>

// Pines del sensor ultrasónico
const int trigPin = 9;
const int echoPin = 10;

// Pines del puente H (Motor DC)
const int motorPin1 = 2;
const int motorPin2 = 4;
const int enablePin = 3;

// Servo motor MG996R
Servo servoMotor;
const int servoPin = 6;

// Pines del sensor de color TCS3200
const int S0 = 11;
const int S1 = 7;
const int S2 = 13;
const int S3 = 12;
const int sensorOut = 8;

// Definiciones de colores
#define RED 0
#define GREEN 1

// Variables para los valores de color
int redValue = 0;
int greenValue = 0;

// Variables para el ultrasonido
long duration;
int distance;

void setup() {
  // Configuración de pines del sensor ultrasónico
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  // Configuración de pines del puente H
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
  analogWrite(enablePin, 190);  // Motor a máxima velocidad

  // Configuración del servo motor
  servoMotor.attach(servoPin);
  servoMotor.write(85); // Poner servo en posición inicial (recto)

  // Configuración del sensor de color TCS3200
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  // Frecuencia de salida del sensor de color
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  // Medir la distancia con el sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  // Si detecta un obstáculo a menos de 10 cm
  if (distance < 15) {
    retrocederCoche();  // Retroceder por un segundo

    // Leer color del objeto detectado
    redValue = leerColor(RED);
    greenValue = leerColor(GREEN);
    
    // Si detecta color verde
    if (greenValue > redValue) {
      girarDerecha();
    }
    // Si detecta color rojo
    else if (redValue > greenValue) {
      girarIzquierda();
    }
  } else {
    // Si no hay obstáculos, el coche avanza recto
    avanzarCoche();
  }
  
  delay(100);
}