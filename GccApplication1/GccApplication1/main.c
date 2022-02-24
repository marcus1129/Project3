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

#define F_CPU 16000000UL
#include <util/delay.h>


int main(void)
{
	_i2c_address = 0X78;
	I2C_Init();
    /* Replace with your application code */
    while (1) 
    {
    }
}

