
/*
 * ERRORES/PROBLEMAS CONOCIDOS:
 * -La memoria no se libera para cada función.
 * -Los comandos tienen un tamaño limitado
 * -El tiempo de espera solo se mide en segundos enteros, no en decimal
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "servo.h"

//Prototipos de funciones
void fallo(char *mensaje);
int TiempoNecesario(int NumServo, int Destino, int Velocidad);
int ObtenerDistancia(int NumServo, int Destino);
int ObtenerPulsoPosicion(int NumServo);

//Constantes
#define TAMANO_DEL_COMANDO 100 //Tamaño maximo de comando
#define TAMANO_USUAL_DEL_COMANDO 60 //Tamaño usual de comando
#define NUM_MAXIMO_DE_SERVOS 6 //Numero maximo de servos
#define POSICION_MINIMA 500 //limite minimo de posicion  del servo
#define POSICION_MAXIMA 2500 //limite maximo de posicion del servo
#define POSICION_CENTRAL 1500 //posicion central del sevo
#define DEFAULT_SLEEP_TIME 3//tiempo de espera para que cada servo inicie

//Variables globales
char PUERTO[13] = "/dev/ttyUSB0 "; // ID DEL PUERTO USB  
char BAUDIOS[6] = "115200"; // Radio de Baudios
int VELOCIDAD = 500; // Velocidad del servo
int NUM_SERVOS_ACTIVOS;

int PosicionPulsoServos[6];



/*
 * Establece los servos en su posición inicial y establece el número activo de servos
 * -NUM    El índice más alto de servos conectados al tablero.
 */
void DarServos(int num) {
    NUM_SERVOS_ACTIVOS = num;
    for(int i = 0; i <= NUM_SERVOS_ACTIVOS; i++) {
        char ComandoCOM[TAMANO_DEL_COMANDO];
        char ComandoParcialCOM[TAMANO_USUAL_DEL_COMANDO];
        sprintf(ComandoParcialCOM, "#%dP%dS%d<CR>", i, PosicionPulsoServos[i], VELOCIDAD);
        sprintf(ComandoCOM, "echo \"%s\" > %s", ComandoParcialCOM, PUERTO);
        system(ComandoCOM);
        sleep(DEFAULT_SLEEP_TIME); //tiempo de espera para cada servo
   }
}

 /*
  *Establecer en qué debe comenzar un servo específico
  * -NUMSERVO          numero de servo
  * -PULSOPOSICION     movimiento del servo
  */
void ObtenerInicioServo(int NumServo, int PulsoPosicion) {
    PosicionPulsoServos[NumServo] = PulsoPosicion;
}


 /*
 * Dar comando especifico 
 * -COMM   cadena para enviar al dispositivo
 */
void EnviarComando(char *comm) {
    if(sizeof(comm) > (TAMANO_DEL_COMANDO - 2))
        fallo("Comando muy largo");
        
    char ComandoCOM[TAMANO_DEL_COMANDO];
    sprintf(ComandoCOM, "echo \"%s\" > %s", comm, PUERTO);
    system(ComandoCOM);
}


 /*
  *Establece la posición de un servo específico enviando ancho de pulso
  * -NUMSERVO          numero del servo
  * -PULSOPOSICION     movimiento del servo
  */
void DarPosicion(int NumServo, int PulsoPosicion) {
    if((NumServo > NUM_MAXIMO_DE_SERVOS) || (PulsoPosicion < POSICION_MINIMA) || (PulsoPosicion > POSICION_MAXIMA))
        fallo("Numero de servo o Posicion invalida");
    char ComandoCOM[TAMANO_DEL_COMANDO];
    char ComandoParcialCOM[TAMANO_USUAL_DEL_COMANDO];
    sprintf(ComandoParcialCOM, "#%dP%dS%d<CR>", NumServo, PulsoPosicion, VELOCIDAD);
    sprintf(ComandoCOM, "echo \"%s\" > %s", ComandoParcialCOM, PUERTO);
    system(ComandoCOM);
    sleep(TiempoNecesario(NumServo, PulsoPosicion, VELOCIDAD));
    PosicionPulsoServos[NumServo] = PulsoPosicion;
}


 /*
  *Establece la posición de un servo específico enviando ancho de pulso
  * -NUMSERVO          numero del servo
  * -PULSOPOSICION     movimiento del servo
  * -VELOCIDAD         velocidad del servo
  */
void DarPosicionConVelocidad(int NumServo, int PulsoPosicion, int Velocidad) {
    if((NumServo > NUM_MAXIMO_DE_SERVOS) || (PulsoPosicion < POSICION_MINIMA) || (PulsoPosicion > POSICION_MAXIMA))
        fallo("Numero de servo o Posicion invalida");
    char ComandoCOM[TAMANO_DEL_COMANDO];
    char ComandoParcialCOM[TAMANO_USUAL_DEL_COMANDO];
    sprintf(ComandoParcialCOM, "#%dP%dS%d<CR>", NumServo, PulsoPosicion, Velocidad);
    sprintf(ComandoCOM, "echo \"%s\" > %s", ComandoParcialCOM, PUERTO);
    system(ComandoCOM);
    sleep(TiempoNecesario(NumServo, PulsoPosicion, Velocidad));
    PosicionPulsoServos[NumServo] = PulsoPosicion;
}


 /*
  *Establecer la velocidad global de todos los servos.
  * -VELOCIDAD    velocidad del servo
  */
void DarVelocidad(int Velocidad) {
    VELOCIDAD = Velocidad;
}


  /*
  *Centrar un servo especifico
  * -NUMSERVO          numero del servo
  */
void Centrar(int NumServo) {
    char ComandoCOM[TAMANO_DEL_COMANDO];
    char ComandoParcialCOM[TAMANO_USUAL_DEL_COMANDO];
    sprintf(ComandoParcialCOM, "#%dP%dS%d<CR>", NumServo, POSICION_CENTRAL, VELOCIDAD);
    sprintf(ComandoCOM, "echo \"%s\" > %s", ComandoParcialCOM, PUERTO);
    system(ComandoCOM);
}


 /*
  *Si llega a fallar en algun aspecto
  * -MENSAJE     mensaje de salida
  */
void fallo(char *mensaje) {
    printf("%s\n", mensaje);
    exit(1);
}


  /*
  *Establece la posición de un servo específico enviando ancho de pulso
  * -NUMSERVO         numero del servo
  * -DESTINO          destino del servo
  * -VELOCIDAD        velocidad utilizada
  */
int TiempoNecesario(int NumServo, int Destino, int Velocidad) {
    int TiempoN;
    int Distancia = ObtenerDistancia(NumServo, Destino);
    TiempoN = Distancia / Velocidad;
    return TiempoN;   
}


  /*
  *Obtiene la distancia entre la posición actual y el destino.
  * -NUMSERVO          numero del servo
  * -DESTINO     	   destino del servo
  */
int ObtenerDistancia(int NumServo, int Destino) {
    int Distancia = abs(ObtenerPulsoPosicion(NumServo) - Destino);
    return Distancia;
}


  /*
  *Obtener el ancho de pulso del servo especificado
  * -NUMSERVO          numero del servo
  */
int ObtenerPulsoPosicion(int NumServo) {
   return PosicionPulsoServos[NumServo];
}
