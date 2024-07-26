#define S0 11
#define S1 12
#define S2 13
#define S3 8
#define sensorOut 7

int redFrequency = 0;
int greenFrequency = 0;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  // Configurar el sensor en la frecuencia de escala del 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);

  Serial.begin(9600);
}

void loop() {
  // Configurar el sensor para medir el rojo
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  redFrequency = pulseIn(sensorOut, LOW);

  // Configurar el sensor para medir el verde
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  greenFrequency = pulseIn(sensorOut, LOW);

  // Imprimir los valores de frecuencia
  Serial.print("Red: ");
  Serial.print(redFrequency);
  Serial.print("  Green: ");
  Serial.println(greenFrequency);

  delay(500);
}
