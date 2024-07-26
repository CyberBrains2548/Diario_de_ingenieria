// Definir pines para el sensor ultrasónico
#define TRIG_PIN  9
#define ECHO_PIN  10

// Definir pines para el puente H
#define ENA 5
#define IN1 3
#define IN2 4

// Definir distancia para detener el motor
#define DISTANCIA_DETECCION 15
#define DISTANCIA_FRENADO 20

// Definir pines para el sensor de color TCS3200
#define S0 11
#define S1 12
#define S2 13
#define S3 8
#define OUT 7

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
  
  Serial.begin(9600);
  
  // Configurar el sensor TCS3200 para detectar colores
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
}

void loop() {
  unsigned int distancia = obtenerDistancia();
  Serial.print("Distancia: ");
  Serial.println(distancia);

  if (distancia <= DISTANCIA_DETECCION) {
    detenerMotor();
    String color = detectarColor();
    Serial.print("Color detectado: ");
    Serial.println(color);

    if (color == "Verde") {
      retrocederMotor(1500); // Retrocede 1.5 segundos si el objeto es verde
    } else if (color == "Rojo") {
      retrocederMotor(5000); // Retrocede 3 segundos si el objeto es rojo
      delay(3000); // Pausa antes de avanzar de nuevo
      avanzarMotor(); // Avanza de nuevo
    }
  } else if (distancia <= DISTANCIA_FRENADO) {
    frenarMotor();
  } else {
    avanzarMotor();
  }

  delay(100); // Pequeña pausa para no saturar el sensor
}

// Función para avanzar el motor
void avanzarMotor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 170);
}

// Función para retroceder el motor
void retrocederMotor(int duracion) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 130);
  delay(duracion);
  detenerMotor();
}

// Función para frenar el motor
void frenarMotor() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, 200);
}

// Función para detener el motor
void detenerMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
}

// Función para obtener la distancia usando el sensor ultrasónico
unsigned int obtenerDistancia() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duracion = pulseIn(ECHO_PIN, HIGH);
  unsigned int distancia = duracion / 58;

  return distancia;
}

// Función para detectar el color usando el sensor TCS3200
String detectarColor() {
  int frecuenciaRojo = leerColor(LOW, LOW);
  int frecuenciaVerde = leerColor(HIGH, HIGH);

  if (frecuenciaVerde < frecuenciaRojo) {
    return "Verde";
  } else if (frecuenciaRojo < frecuenciaVerde) {
    return "Rojo";
  } else {
    return "Desconocido";
  }
}

// Función para leer la frecuencia de color del sensor TCS3200
int leerColor(bool estadoS2, bool estadoS3) {
  digitalWrite(S2, estadoS2);
  digitalWrite(S3, estadoS3);
  delay(100);
  
  int frecuencia = pulseIn(OUT, LOW);
  
  return frecuencia;
}
