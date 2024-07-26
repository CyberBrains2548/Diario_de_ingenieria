#include <Servo.h>

// Crear un objeto Servo
Servo miServo;

// Definir el pin donde está conectado el servomotor
const int pinServo = 5;

void setup() {
  
  // Asociar el objeto Servo al pin
  miServo.attach(pinServo);
}

// Funciones para controlar el servomotor
void moverIzquierda() {
  miServo.write(60);
  delay(1000); // Esperar 1 segundo
}

void moverCentro() {
  miServo.write(90);
  delay(1000); // Esperar 1 segundo
}

void moverDerecha() {
  miServo.write(120);
  delay(1000); // Esperar 1 segundo
}

void loop() {
  // Control del servomotor
  moverIzquierda();
  moverCentro();
  moverDerecha();
}
