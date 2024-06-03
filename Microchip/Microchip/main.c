/*
 * Microchip.c
 *
 * Created: 28/5/2024 21:19:47
 * Author : manuc
 */ 
/*
#include <avr/io.h>
#include "serialPort.h"
#include "RTC.h"
#include "DHT11.h"
//#include "timer.h" esta en duda su uso
int main(void)
{
	SerialPort_Init();
    
    while (1) 
    {
		
    }
}

*/
#define F_CPU 16000000UL
#include <avr/io.h>
#include "serialPort.h"

#define BR9600 (0x67)	// 0x67=103 configura BAUDRATE=9600@16MHz

//mensajes de bienvenida y despedida
char msg1[] = "TEMP: %02d �C HUM: %02d\% FECHA: %02d/%02d/%02d HORA:%02d:%02d:%03d\r\n";//temp, hum, dd/mm/aa, hh/mm/sss


int main(void)	
{
	volatile char dato = 0;
	
	SerialPort_Init(BR9600); 		// Inicializo formato 8N1 y BAUDRATE = 9600bps
	SerialPort_TX_Enable();			// Activo el Transmisor del Puerto Serie
	SerialPort_RX_Enable();			// Activo el Receptor del Puerto Serie
	SerialPort_Send_String(msg1);    
	while(1)
	{
		SerialPort_Wait_Until_New_Data();	  // Pooling - Bloqueante, puede durar indefinidamente.
		dato = SerialPort_Recive_Data();

		// Si presionan 's' se termina o reanuda
		if( dato == 's')
		{
			// bool activo o desactivo
		}	
		else
		{				
			SerialPort_Wait_For_TX_Buffer_Free(); // Espero a que el canal de transmisi�n este libre (bloqueante)
			//cada 2 segundos mando a terminal
			SerialPort_Send_String(msg1);    
		}
	}
	return 0;
}
// Rutina de Servicio de Interrupci�n de Byte Recibido
ISR(USART_RX_vect){
	if (activo)
		imprimirMensaje();
	RX_Buffer = UDR0; //la lectura del UDR borra flag RXC
}
