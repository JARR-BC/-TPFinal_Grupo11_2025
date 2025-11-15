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

// ---------------- BUZZER (LED) ----------------
#define BUZZER_LED A0  // LED que simula el buzzer

// ---------------- VARIABLES DE CONTROL ----------------
unsigned long ahora = 0;
unsigned long tiempoInicio = 0;

const unsigned long TIEMPO_VERDE = 2000;
const unsigned long TIEMPO_AMARILLO = 500;
const unsigned long TIEMPO_ROJO = 2000;
const unsigned long DESFASE = 1000; // 1 segundos entre semáforos

// Para cada semáforo, guardamos su propio "inicio de ciclo"
unsigned long inicio1 = 0;
unsigned long inicio2 = DESFASE;
unsigned long inicio3 = 2 * DESFASE;

// Buzzer simulado (LED)
unsigned long buzzerInicio = 0;
bool buzzerActivo = false;

bool rojoForzado1 = false;
bool rojoForzado2 = false;
bool rojoForzado3 = false;

// Contador de flancos 

unsigned long conteoBuzzer = 0;


void setup() {
  pinMode(R1, OUTPUT); pinMode(G1, OUTPUT); pinMode(B1, OUTPUT);
  pinMode(R2, OUTPUT); pinMode(G2, OUTPUT); pinMode(B2, OUTPUT);
  pinMode(R3, OUTPUT); pinMode(G3, OUTPUT); pinMode(B3, OUTPUT);

  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  pinMode(BUZZER_LED, OUTPUT);
// Se inicializa el monitor serial

Serial.begin(9600);
Serial.println("Sistema de semaforos iniciado");
  
}

void loop() {
  ahora = millis();

  // -------- BUZZER (LED) activado por cualquier botón --------
  if ((digitalRead(button) == LOW || digitalRead(button2) == LOW || digitalRead(button3) == LOW) && !buzzerActivo) {
    buzzerActivo = true;
    buzzerInicio = ahora;
    tone(BUZZER_LED, 500); 
  
  // Se cuenta e inicializa el flanco de Buzzer
    conteoBuzzer++;
    Serial.print("Activacion de buzzer numero: ");
    Serial.println(conteoBuzzer);
  
  }

  // Apagar buzzer después de 5 segundos
  if (buzzerActivo && (ahora - buzzerInicio >= 5500)) {
    buzzerActivo = false;
    noTone(BUZZER_LED);
    
  }

  // -------- Lógica de botones (forzar rojo) --------
  if (digitalRead(button) == LOW) rojoForzado1 = true;
  if (digitalRead(button2) == LOW) rojoForzado2 = true;
  if (digitalRead(button3) == LOW) rojoForzado3 = true;

  // -------- Reinicio del ciclo total --------
  unsigned long cicloTotal = TIEMPO_VERDE + TIEMPO_AMARILLO + TIEMPO_ROJO + 2 * DESFASE;
  if (ahora - tiempoInicio >= cicloTotal) {
    tiempoInicio = ahora;
    inicio1 = 0;
    inicio2 = DESFASE;
    inicio3 = 2 * DESFASE;
    rojoForzado1 = rojoForzado2 = rojoForzado3 = false;
  }

  // -------- Actualización de semáforos --------
  actualizarSemaforo(R1, G1, B1, inicio1, rojoForzado1);
  actualizarSemaforo(R2, G2, B2, inicio2, rojoForzado2);
  actualizarSemaforo(R3, G3, B3, inicio3, rojoForzado3);
}

// ---------------- FUNCIÓN DE ACTUALIZACIÓN ----------------
void actualizarSemaforo(int R, int G, int B, unsigned long desfase, bool forzado) {
  if (forzado) {
    colorRojo(R, G, B);
    return;
  }

  unsigned long tiempo = (millis() - tiempoInicio);

  if (tiempo < desfase) {
    colorRojo(R, G, B); // espera su turno
    return;
  }

  unsigned long t = tiempo - desfase;

  if (t < TIEMPO_VERDE) {
    colorVerde(R, G, B);
  } else if (t < TIEMPO_VERDE + TIEMPO_AMARILLO) {
    colorAmarillo(R, G, B);
  } else {
    colorRojo(R, G, B);
  }
}

// ---------------- FUNCIONES DE COLOR ----------------
void colorRojo(int R, int G, int B) {
  analogWrite(R, 255); analogWrite(G, 0); analogWrite(B, 0);
}

void colorVerde(int R, int G, int B) {
  analogWrite(R, 0); analogWrite(G, 255); analogWrite(B, 0);
}

void colorAmarillo(int R, int G, int B) {
  analogWrite(R, 255); analogWrite(G, 255); analogWrite(B, 0);
}