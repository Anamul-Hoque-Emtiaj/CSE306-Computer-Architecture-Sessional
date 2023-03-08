/*
 * PC.c
 *
 * Created: 2/27/2023 10:34:27 PM
 * Author : anamul hoque
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRA = 0xFE; //input
    DDRB = 0x01; //output
	PORTB = 0x00;
    
    while (1) 
    {
		PORTB = PINA;
		_delay_ms(1000);
    }
}

