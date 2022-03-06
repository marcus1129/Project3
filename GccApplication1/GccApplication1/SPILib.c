/*
 * SPILib.c
 *
 * Created: 2/24/2022 2:56:10 PM
 * Author : Marcus Korre
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include "./SPILib.h"
#include <string.h>

/* Replace with your library code */

void slaveSelect(char* state){
	if(strcmp(state, "HIGH") == 0){
		PORTB |= (1<<PB0);
	}
	else if(strcmp(state, "LOW") == 0){
		PORTB = !(1<<PB0);
	}
		
}

int initSPI(char role){
	sei();
	if(role == MASTER){
		DDRB = (1<<PB2)|(1<<PB1)|(1<<PB0); //Sets ss-not, MOSI and SCK to be outputs
		slaveSelect(HIGH);
		SPCR = (1<<SPE)|(1<<MSTR); //Initiates control register
		return 0;
	}
	else if(role == SLAVE){
		DDRB = (1<<PB3); //Sets MISO as output
		PORTB = (1<<PB0); //Sets clock to pull high
		SPCR = (1<<SPE); //Initiates control register
		return 0;
	}
	return 1;
}

char transmit(char transmitionCode){
	if((DDRB & 0b00000111) == 0b00000111){ //If this is a master
		if((PORTB & 0b00000001) == 0b00000001){ //If !ss is set to high
			return 0;
		}
		SPDR = transmitionCode;
		while((SPSR & 0b10000000) != 0b10000000){} //Waits for transmition to finish
		return SPDR;
	}
	return 1;
}

ISR(SPI_STC_vect){
	
}
