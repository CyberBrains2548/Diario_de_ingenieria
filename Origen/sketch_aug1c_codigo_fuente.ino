#include <Servo.h>

// Definición de pines
const int trigPin = 9;
const int echoPin = 10;
const int motorPin1 = 2;
const int motorPin2 = 4;
const int enablePin = 3;
const int servoPin = 6;

// Variables
long duration;
int distance;
Servo servoMotor;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);

  // Inicializa el servo
  servoMotor.attach(servoPin);

  // Inicializa el monitor serial
  Serial.begin(9600);

  // Pausa inicial antes de iniciar el movimiento
  delay(500); // Espera 500 ms antes de comenzar

  // Inicia el motor
  analogWrite(enablePin, 250); // Velocidad máxima
}

void loop() {
  // Envía un pulso ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // Lee el tiempo del eco
  duration = pulseIn(echoPin, HIGH);

  // Calcula la distancia
  distance = duration * 0.034 / 2;

  // Imprime la distancia en el monitor serial
  Serial.print("Distancia: ");
  Serial.println(distance);

  if (distance > 35) {
    avanzar();
  } else {
    detener();         // Detiene el coche inmediatamente
    enderezar();       // Endereza antes de retroceder
    retroceder();
    delay(920);        // Retrocede durante 920 ms

    girarIzquierda();
    delay(1140);       // Gira hacia la izquierda durante 1,3 segundos
  }

  delay(100);
}

void avanzar() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  servoMotor.write(85); // Mantiene el servo en posición central (recto)
}

void detener() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void retroceder() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
}

void girarIzquierda() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  servoMotor.write(50); // Gira el servo hacia la izquierda
}

void enderezar() {
  servoMotor.write(85); // Coloca el servo en posición central (recto)
  delay(200);           // Espera 200 ms para que el servo se enderece
}
