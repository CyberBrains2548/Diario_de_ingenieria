#include <NewPing.h>

// Definición de pines para el sensor ultrasónico HC-SR04
#define TRIGGER_PIN  9
#define ECHO_PIN     8
#define MAX_DISTANCE 200 // Distancia máxima en centímetros para medir (en este caso, 200 cm o 2 metros)

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Crea un objeto NewPing

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serial
}

void loop() {
  delay(1000); // Espera medio segundo entre cada medición

  // Realiza una medición de distancia
  unsigned int distancia = sonar.ping_cm();

  // Muestra la distancia medida en el monitor serial
  Serial.print("Distancia: ");
  if (distancia == 0) {
    Serial.println("Fuera de rango");
  } else {
    Serial.print(distancia);
    Serial.println(" cm");
  }
}
