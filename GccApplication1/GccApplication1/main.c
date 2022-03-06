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
#include <math.h>
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
	char skrr[20];
	int temperature = 0;
	int totalByte;
	int* slaveOutput = (int*)calloc(2, sizeof(int));
	int* tempBytes = (int*)calloc(3, sizeof(int));
	int midBitsMask = 0b00000111;
	int highestBitsMask = 0b01111000;
	int lowestBitsMask = 0b11111000;
	int offSet = 256;
	float resoLution = 0.25;
    while(1){
		slaveSelect(LOW);
		for(int i = 0; i < 2; i++){
			slaveOutput[i] = transmit('s');
		}
		slaveSelect(HIGH);
		tempBytes[0] = (slaveOutput[0] & midBitsMask) << 5;
		tempBytes[1] = (slaveOutput[0] & highestBitsMask) >> 3;
		tempBytes[2] = (slaveOutput[1] & lowestBitsMask) >> 3;
		tempBytes[0] |= tempBytes[2];
		tempBytes[1] *= offSet;
		totalByte = tempBytes[1] + tempBytes[0];
		temperature = (int)((float)totalByte*resoLution);

		sprintf(skrr, "%d", temperature);
		clear_display();
		sendStrXY(skrr, 0, 0);
		_delay_ms(1000);
    }
}