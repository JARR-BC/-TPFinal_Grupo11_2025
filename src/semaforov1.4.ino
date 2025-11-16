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

// BUZZER (LED)
#define BUZZER_LED A0  // LED que simula el buzzer

// VARIABLES DE CONTROL
unsigned long ahora = 0;
unsigned long tiempoInicio = 0;

const unsigned long TIEMPO_VERDE = 3000;
const unsigned long TIEMPO_AMARILLO = 1000;
const unsigned long TIEMPO_ROJO = 2000;
const unsigned long DESFASE = 1500;

// Para cada semaforo, guardamos su propio "inicio de ciclo"
unsigned long inicio1 = 0;
unsigned long inicio2 = DESFASE;
unsigned long inicio3 = 2 * DESFASE;

// Buzzer simulado (LED)
unsigned long buzzerInicio = 0;
bool buzzerActivo = false; 

bool rojoForzado1 = false;
bool rojoForzado2 = false;
bool rojoForzado3 = false;

// contador de flancos
unsigned long conteoBuzzer = 0;



// FUNCIONES DE COLOR 
// Funcion 1
void colorRojo(int R, int G, int B) {
  analogWrite(R, 255);
  analogWrite(G, 0);
  analogWrite(B, 0);
}

// Funcion 2
void colorVerde(int R, int G, int B) {
  analogWrite(R, 0);
  analogWrite(G, 255);
  analogWrite(B, 0);
}

// Funcion 3
void colorAmarillo(int R, int G, int B) {
  analogWrite(R, 255);
  analogWrite(G, 255);
  analogWrite(B, 0);
}

// ---------------- FUNCION DE ACTUALIZACION ----------------
// Funcion 4
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

void setup() {
  // Salidas Semaforo 1
  pinMode(R1, OUTPUT);
  pinMode(G1, OUTPUT);
  pinMode(B1, OUTPUT);
  
  // Salidas Semaforo 2
  pinMode(R2, OUTPUT);
  pinMode(G2, OUTPUT);
  pinMode(B2, OUTPUT);
  
  // Salidas Semaforo 3
  pinMode(R3, OUTPUT);
  pinMode(G3, OUTPUT);
  pinMode(B3, OUTPUT);

  // Entradas de botones
  pinMode(button, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button3, INPUT_PULLUP);

  // Salida Buzzer
  pinMode(BUZZER_LED, OUTPUT);
  
  // Serial monitor
  Serial.begin(9600);
  Serial.println("Sistema de semaforos iniciado");
}

void loop() {
  ahora = millis();
  
  // 1- Detectamos si se presiona algún botón *mientras el sistema no esté ya activo*
  bool boton1_presionado = (digitalRead(button) == LOW);
  bool boton2_presionado = (digitalRead(button2) == LOW);
  bool boton3_presionado = (digitalRead(button3) == LOW);

  if ((boton1_presionado || boton2_presionado || boton3_presionado) && !buzzerActivo) {
    // Si se presiona un botón y el buzzer no sonaba, INICIAMOS el modo peatón
    buzzerActivo = true;
    buzzerInicio = ahora;
    tone(BUZZER_LED, 500);

    // Forzamos a rojo SÓLO el semáforo del botón presionado
    if (boton1_presionado) 
        rojoForzado1 = true;
    if (boton2_presionado)
        rojoForzado2 = true;
    if (boton3_presionado)
        rojoForzado3 = true;

    // Se cuenta e inicializa el flanco de Buzzer
    conteoBuzzer++;
    Serial.print("Activacion de buzzer numero: ");
    Serial.println(conteoBuzzer);
  }

  // 2- Apagar buzzer y rojos forzados después de 3 segundos
  if (buzzerActivo && (ahora - buzzerInicio >= 3000)) {
    buzzerActivo = false;
    noTone(BUZZER_LED);
    
    rojoForzado1 = false;
    rojoForzado2 = false;
    rojoForzado3 = false;
  }
  

  // -------- Reinicio del ciclo total --------
  unsigned long cicloTotal = TIEMPO_VERDE + TIEMPO_AMARILLO + TIEMPO_ROJO + 2 * DESFASE;
  if (ahora - tiempoInicio >= cicloTotal) {
    tiempoInicio = ahora;
    inicio1 = 0;
    inicio2 = DESFASE;
    inicio3 = 2 * DESFASE;
    
  }

  // Actualizacion de semaforos, llama a funcion void actualizarSemaforo()...
  actualizarSemaforo(R1, G1, B1, inicio1, rojoForzado1);
  actualizarSemaforo(R2, G2, B2, inicio2, rojoForzado2);
  actualizarSemaforo(R3, G3, B3, inicio3, rojoForzado3);
}

