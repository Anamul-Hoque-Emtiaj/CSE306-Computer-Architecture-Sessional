/*
 * Instruction.c
 *
 * Created: 2/18/2023 11:30:52 AM
 * Author : anamul hoque
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// Some pins of PORTC can not be used for I/O directly.
	// turn of JTAG to use them
	// o write a 1 to the JTD bit twice consecutively to turn it off
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRA = 0x00;	// input 
	DDRB = 0xFF;  //out
	DDRC = 0b11111100;	// clk reset 
	uint8_t inst = 0;
	while (1)
	{
		if(PINC & 0x01)
		{
			inst = PINA;
			
		}
		else if(PINC & 0x02)
		{
			inst = 0;
		}
		PORTB = inst;
		_delay_ms(2000);
	}
}

