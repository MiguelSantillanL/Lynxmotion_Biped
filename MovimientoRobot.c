#include"MovimientoRobot.h"
void MenuRobot(){
	char opc;
	printf("\nUse las siguientes teclas para manejar al robot\n q   -Llevar al robot a una posicion de firmes\n w   -El robot avanzara\n s   -El robot caminara haca atras\n");
	while(1){
	scanf("%c",&opc);
	switch(opc)
            {
				case 'q':
					CentrarRobot();
					break;
				case 's':
					CaminarHaciaAtras();
					break;
				case 'w':
					CaminarAdelante();
					break;
				
				default:
					break;
			}
			
		}
}




void CentrarRobot(int servos){
	printf("\nEl robot va a estar en posicion de firmes\n");
		Centrar(0);
		Centrar(3);
		Centrar(4);
		Centrar(1);
		Centrar(2);
		Centrar(5);	
		
}

void CaminarAdelante(){
	printf("\nEl robot camina hacia adelante\n");
	DarPosicion(3, 1350); //pie ->
	DarPosicion(0, 1340); //pie <-
	DarPosicion(2, 600); //pierna <-
	
	DarPosicion(4, 1300); //pierna ->
	DarPosicion(1, 1200); //pierna <-
	Centrar(0);
	Centrar(3);
	
	DarPosicion(0,1850);
	DarPosicion(3,2000);
	//sleep(3);
	
	DarPosicion(5, 1500); 
	DarPosicion(4, 1500); 
	DarPosicion(5, 2500); 
	
	Centrar(2);//A
	Centrar(1);
	Centrar(3);
	DarPosicion(4, 1900); 
	DarPosicion(2, 1650);
	DarPosicion(3, 1500);
	sleep(3);
	DarPosicion(0, 1500);
	sleep(3);
	
	DarPosicion(3, 1300);//
	DarPosicion(0, 1300);
	
	Centrar(5);//AQUI COMIENZA
	Centrar(4);
	Centrar(0);
}

void CaminarHaciaAtras(){
	printf("\nEl robot camina hacia atras\n");
	
	DarPosicion(0, 1340);
	DarPosicion(3, 1350); 
	DarPosicion(2, 1800);
	DarPosicion(4, 1700);
	DarPosicion(0,1800);
	DarPosicion(3,2000);
	Centrar(3);
	DarPosicion(4, 1450);
	
	DarPosicion(2, 1800);
	DarPosicion(4, 1200);
	DarPosicion(2, 1300);
	Centrar(0);
	Centrar(4);
	
}

