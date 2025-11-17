1. # Semáforo para personas no videntes con alerta sonora

El sistema consiste en un semáforo automatizado que utiliza luces LED y señales sonoras para asistir a personas con discapacidad visual al cruzar la calle. Incluye un botón de petición de paso y un zumbador que emite sonido según el estado del semáforo.


2. ## Intregantes:
   
Lucas Viña 
lvinsci2006@gmail.com

Julian Rivadeo
julianrivadeo.tecnicatura@gmail.com

Maximiliano Candia
maximiliano.candia12@gmail.com

Juan Ignacio Cucarella
qkjuani29@gmail.com

3. ## Docentes y materia

Docentes: Pedro Iriso, Matias Gagliardo

Materia: Laboratorio de computacion 1  


4. ## Descripcion y funcionalidades.

   
Para este proyecto se simulará un paso peatonal para ciegos, adaptado a una avenida con 3 cruces peatonales, y una alarma sonora que se emitirá a petición del peaton cuando decida cruzar la calle, de esta manera la persona no vidente usará debidamente el paso mediante el sentido de la audicion.

Los semaforos seran realistas y continuos.
Los botones de cada cruce colocarán el semaforo a rojo durante determinado tiempo.



5. ## Requisitos funcionales cumplidos:

    Aquí listas los 4 requisitos que ya vimos:

    Control de Entradas/Salidas: El sistema lee 3 entradas (digitalRead de los botones) y controla 10 salidas (9 analogWrite para los LED RGB y 1 tone para el buzzer).

    Contador de Flancos: Se implementa con la variable conteoBuzzer. Solo se incrementa al detectar el flanco de activación del botón (if (... && !buzzerActivo)).

    Control Lógico por Tiempo: El sistema usa millis() para dos temporizadores independientes: la onda verde (ahora - tiempoInicio) y el cruce peatonal (ahora - buzzerInicio).

    Máquina de Estados: El sistema tiene 2 estados principales controlados por la variable buzzerActivo (MODO_NORMAL y MODO_PEATON).


6. ## Componentes utilizados
   1 Arduino UNO,
   1 Protoboard,
   3 Led's RGB,
   3 Pulsadores,
   1 Buzzer,
   13 Resistencias,
   22 Cables macho-macho.

7. ## Diagrama de conexiones
   
  
   

9. 


10.  //-------------------------------------------------------------------------------------------------//


11. El semaforo estará en continuo funcionamiento, debe accionar el boton para iniciar la peticion del cruce peatonal durante 5 segundos.


12. //-------------------------------------------------------------------------------------------------//


13. //-------------------------------------------------------------------------------------------------//
   



