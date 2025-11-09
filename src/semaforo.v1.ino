// ---------------- PRIMER SEMÁFORO ----------------
#define R1 3
#define G1 6
#define B1 5
#define button 2

// ---------------- SEGUNDO SEMÁFORO ----------------
#define R2 9
#define G2 11
#define B2 10
#define button2 4

// ---------------- TERCER SEMÁFORO ----------------
#define R3 7
#define G3 12
#define B3 8
#define button3 13

// ---------------- VARIABLES DE CONTROL ----------------
unsigned long tiempoInicio = 0;
const unsigned long TIEMPO_VERDE = 3000;    // 3 segundos
const unsigned long TIEMPO_AMARILLO = 1000; // 1 segundo
const unsigned long TIEMPO_ROJO = 2000;     // 2 segundos
int estado = 0; // 0=verde, 1=amarillo, 2=rojo

bool rojoForzado1 = false;
bool rojoForzado2 = false;
bool rojoForzado3 = false;

void setup() {
  pinMode(R1, OUTPUT); pinMode(G1, OUTPUT); pinMode(B1, OUTPUT);
  pinMode(R2, OUTPUT); pinMode(G2, OUTPUT); pinMode(B2, OUTPUT);
  pinMode(R3, OUTPUT); pinMode(G3, OUTPUT); pinMode(B3, OUTPUT);

  // Botones conectados a GND (con resistencia interna activada)
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);
}

void loop() {
  unsigned long ahora = millis();

  // Lectura de botones (LOW = presionado)
  if (digitalRead(button) == LOW) rojoForzado1 = true;
  if (digitalRead(button2) == LOW) rojoForzado2 = true;
  if (digitalRead(button3) == LOW) rojoForzado3 = true;

  // Cambios de estado del ciclo normal
  if (estado == 0 && ahora - tiempoInicio >= TIEMPO_VERDE) {
    estado = 1;
    tiempoInicio = ahora;
  } else if (estado == 1 && ahora - tiempoInicio >= TIEMPO_AMARILLO) {
    estado = 2;
    tiempoInicio = ahora;
  } else if (estado == 2 && ahora - tiempoInicio >= TIEMPO_ROJO) {
    estado = 0;
    tiempoInicio = ahora;

    // Reinicio de los botones forzados al terminar el ciclo
    rojoForzado1 = false;
    rojoForzado2 = false;
    rojoForzado3 = false;
  }

  // -------- SEMÁFORO 1 --------
  if (rojoForzado1) {
    analogWrite(R1, 255); // rojo
    analogWrite(G1, 0);
    analogWrite(B1, 0);
  } else {
    if (estado == 0) {        // verde
      analogWrite(R1, 0);
      analogWrite(G1, 255);
      analogWrite(B1, 0);
    } else if (estado == 1) { // amarillo
      analogWrite(R1, 255);
      analogWrite(G1, 120);
      analogWrite(B1, 0);
    } else if (estado == 2) { // rojo
      analogWrite(R1, 255);
      analogWrite(G1, 0);
      analogWrite(B1, 0);
    }
  }

  // -------- SEMÁFORO 2 --------
  if (rojoForzado2) {
    analogWrite(R2, 255);
    analogWrite(G2, 0);
    analogWrite(B2, 0);
  } else {
    if (estado == 0) {
      analogWrite(R2, 0);
      analogWrite(G2, 255);
      analogWrite(B2, 0);
    } else if (estado == 1) {
      analogWrite(R2, 255);
      analogWrite(G2, 120);
      analogWrite(B2, 0);
    } else if (estado == 2) {
      analogWrite(R2, 255);
      analogWrite(G2, 0);
      analogWrite(B2, 0);
    }
  }

  // -------- SEMÁFORO 3 --------
  if (rojoForzado3) {
    analogWrite(R3, 255);
    analogWrite(G3, 0);
    analogWrite(B3, 0);
  } else {
    if (estado == 0) {
      analogWrite(R3, 0);
      analogWrite(G3, 255);
      analogWrite(B3, 0);
    } else if (estado == 1) {
      analogWrite(R3, 255);
      analogWrite(G3, 120);
      analogWrite(B3, 0);
    } else if (estado == 2) {
      analogWrite(R3, 255);
      analogWrite(G3, 0);
      analogWrite(B3, 0);
    }
  }
}