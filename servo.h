
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void initializeController();
void initializeControllerSpecific(char *PUERTO, char *BAUDIOS);
void DarServos(int num);
void ObtenerInicioServo(int NumServo, int PulsoPosicion);
void EnviarComando(char *comm);
void DarPosicion(int NumServo, int PulsoPosicion);
void DarPosicionConVelocidad(int NumServo, int PulsoPosicion, int Velocidad);
void DarVelocidad(int Velocidad);
void Centrar(int NumServo);
