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

/* Replace with your library code */
int initSPI(char role){
	sei();
	if(role == MASTER){
		DDRB = (1<<PB2)|(1<<PB1)|(1<<PB0); //Sets ss-not, MOSI and SCK to be outputs
		PORTB = (1<<PB0);
		SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<SPR1); //Initiates control register
		return 1;
	}
	else if(role == SLAVE){
		DDRB = (1<<PB3); //Sets MISO as output
		PORTB = (1<<PB0); //Sets clock to pull high
		SPCR = (1<<SPE)|(1<<CPOL); //Initiates control register
		return 1;
	}
	return 0;
}

char transmit(char transmitionCode){
	if((DDRB & 0b00000111) == 0b00000111){ //If this is a master
		PORTB &= 0b11111110; //Sets !ss = 0
		SPDR = transmitionCode;
		while((SPSR & 0b10000000) != 0b10000000){} //Waits for transmition to finish
		PORTB |= 0b00000001; //Sets !ss = 1
		return SPDR;
	}
	return 0;
}

ISR(SPI_STC_vect){
	
}
