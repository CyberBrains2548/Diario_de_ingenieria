#include <Servo.h>

// Definición de pines para el motor DC
const int pinIN1 = 4;  // Control de dirección 1
const int pinIN2 = 2;  // Control de dirección 2
const int pinENA = 3;  // Control PWM

void setup() {
  // Configurar los pines del motor como salida
  pinMode(pinIN1, OUTPUT);
  pinMode(pinIN2, OUTPUT);
  pinMode(pinENA, OUTPUT);
}

// Funciones para controlar el motor DC
void avanzar() {
  digitalWrite(pinIN1, HIGH);
  digitalWrite(pinIN2, LOW);
  analogWrite(pinENA, 120); // Velocidad máxima
  delay(2000); // Avanzar por 2 segundos
  detenerMotor(); // Detener el motor
}

void retroceder() {
  digitalWrite(pinIN1, LOW);
  digitalWrite(pinIN2, HIGH);
  analogWrite(pinENA, 120); // Velocidad máxima
  delay(2000); // Retroceder por 2 segundos
  detenerMotor(); // Detener el motor
}

void detenerMotor() {
  analogWrite(pinENA, 0); // Detener el motor
}

void loop() {
  // Control del motor DC
  avanzar();
  delay(1000); // Esperar 1 segundo
  retroceder();
  delay(1000); // Esperar 1 segundo
  }
