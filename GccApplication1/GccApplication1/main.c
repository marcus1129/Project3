/*
 * GccApplication1.c
 *
 * Created: 2/24/2022 2:50:31 PM
 * Author : marcu
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>
#include "I2C.h"  //include library for i2c driver
#include "ssd1306.h" //include display driver
#include "./SPILib.h"

#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	_i2c_address = 0X78;
	
	initSPI(MASTER);
	I2C_Init();
	InitializeDisplay();
	print_fonts();
	clear_display();
	char temp = 1;
    while(1){
		temp = transmit('s');
		if(temp){
			sendCharXY(temp, 0, 0);
		}
    }
}

