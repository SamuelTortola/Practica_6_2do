//******************************************************************************
// Universidad Del Valle De Guatemala
// IE2023: Electrónica digital 2
// Autor: Samuel Tortola - 22094
// Proyecto: Laboratorio 6
// Hardware: Atmega238p
// Creado: 20/09/2024
//Última modificación: 20/09/2024
//******************************************************************************
  //CODIGO DEL CONTROL

#define F_CPU 16000000
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/twi.h>

#include "UART/UART.h"

volatile char receivedChar = 0;    //Variable que almacena el valor del UART
int cambio = 0;

void setup(void);
void setup(void){
	cli();  //Apagar interrupciones
	
	DDRB = 0b00000000;   //PB0, PB1, PB2, PB3, PB4 como entrada
	PORTB = 0b00011111;		//pull up encendido en PB0 y PB1 y PB2
	
	 DDRD &= ~(1 << PIND2);   // Configura PD2 como entrada
	 PORTD |= (1 << PIND2);   // Habilita el pull-up interno en PD2
	
	initUART9600();  //Iniciar UART
	
	PCMSK0 |= (1 << 0)|(1 << 1)|(1 << 2)|(1 << 3)|(1 << 4); //PCINT0, PCINT1, PCINT2, PCINT3, PCINT4
	PCICR |= (1 << 0); //Mascara de interrupción
	
	EICRA &= ~((1 << ISC01) | (1 << ISC00));  // Configura INT0 para que se dispare en nivel bajo
	EIMSK |= (1 << INT0);  // Habilita la interrupción externa INT0

	sei(); //Activar interrupciones
}
int main(void)
{
    setup();
    while (1) 
    {
		_delay_ms(10);
		
	
		
    }
}


ISR(PCINT0_vect){
	
	if(((PINB) & (1<<0)) == 0){   //Condicional que compara si se presionó el pulsador 1
		_delay_ms(20);  //antirrebote
		
		writeUART('1');
		
		
		while ((PINB & (1 << PINB0)) == 0)   //While para evitar sumas indebidas
		{
			_delay_ms(10);
		}
		
	}
	
	 if(((PINB) & (1<<1)) == 0){   //Condicional que compara si se presionó el pulsador  2
		_delay_ms(20);  //antirrebote
		
		writeUART('2');
		
		while ((PINB & (1 << PINB1)) == 0)   //While para evitar sumas indebidas
		{
			_delay_ms(10);
		}
		
	}
	
	 if(((PINB) & (1<<2)) == 0){   //Condicional que compara si se presionó el pulsador  3
		_delay_ms(20);  //antirrebote
		
		writeUART('3');
		
		while ((PINB & (1 << PINB2)) == 0)   //While para evitar sumas indebidas
		{
			_delay_ms(10);
		}
		
	}

	else if(((PINB) & (1<<3)) == 0){   //Condicional que compara si se presionó el pulsador  4
		_delay_ms(20);  //antirrebote
		
		writeUART('4');
		
		while ((PINB & (1 << PINB3)) == 0)   //While para evitar sumas indebidas
		{
			_delay_ms(10);
		}
		
	}
	
	else if(((PINB) & (1<<4)) == 0){   //Condicional que compara si se presionó el pulsador  5
		_delay_ms(20);  //antirrebote
		
		writeUART('5');
		
		while ((PINB & (1 << PINB4)) == 0)   //While para evitar sumas indebidas
		{
			_delay_ms(10);
		}
		
	}
	
	
}


ISR(INT0_vect) {
	if(((PIND) & (1<<DDD2)) == 0){     //Condicional que compara si se presionó el pulsador  6
		_delay_ms(20);  //antirrebote
		
		writeUART('6');
		
		while ((PIND & (1 << DDD2)) == 0)   //While para evitar mas pulsos
		{
			_delay_ms(10);
		}
	}
}


ISR(USART_RX_vect)
{
	receivedChar = UDR0; // Almacena el carácter recibido
	
	while(!(UCSR0A & (1<<UDRE0)));    //Mientras haya caracteres
	
}

