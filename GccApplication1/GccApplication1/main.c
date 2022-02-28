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

union {
	unsigned char byte;
	// a structure with 8 single bit bit-field objects, overlapping the union member "byte"
	struct {
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
	};
} tempByte1, tempByte2;

union {
	unsigned char byte12;
	// a structure with 8 single bit bit-field objects, overlapping the union member "byte"
	struct {
		unsigned b0:1;
		unsigned b1:1;
		unsigned b2:1;
		unsigned b3:1;
		unsigned b4:1;
		unsigned b5:1;
		unsigned b6:1;
		unsigned b7:1;
		unsigned b8:1;
		unsigned b9:1;
		unsigned b10:1;
		unsigned b11:1;
	};
} finalByte;


int main(void)
{
	_i2c_address = 0X78;
	initSPI(MASTER);
	I2C_Init();
	InitializeDisplay();
	print_fonts();
	clear_display();
    while(1){
		int temp = 0b0000000100000000;
		tempByte1.byte = transmit('s');
		tempByte2.byte = transmit('s');
		finalByte.b0 = tempByte1.b0;
		finalByte.b1 = tempByte1.b1;
		finalByte.b2 = tempByte1.b2;
		finalByte.b3 = tempByte1.b3;
		finalByte.b4 = tempByte1.b4;
		finalByte.b5 = tempByte1.b5;
		finalByte.b6 = tempByte1.b6;
		finalByte.b7 = tempByte1.b7;
		finalByte.b8 = tempByte2.b0;
		finalByte.b9 = tempByte2.b1;
		finalByte.b10 = tempByte2.b2;
		finalByte.b11 = tempByte2.b3;
		
		int val = finalByte.b0 + finalByte.b1*2 + finalByte.b2*4 + finalByte.b3*8 + finalByte.b4*16 + finalByte.b5*32 + finalByte.b6*64 + finalByte.b7*128 + finalByte.b8*256 + finalByte.b9*512 + finalByte.b10*1024 + finalByte.b11*2048;
		int temperature = (int)((float)val*0.25);
		
		char skrr[4];
		sprintf(skrr, "%d", temperature);
		//sendCharXY(transmit('s'), 1, 0);
		if(skrr){
			sendStrXY(skrr, 0, 0);
		}
    }
}

