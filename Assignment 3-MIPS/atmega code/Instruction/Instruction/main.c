/*
 * Instruction.c
 *
 * Created: 2/18/2023 11:30:52 AM
 * Author : anamul hoque
 */ 


#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint16_t INSTRUCTIONS[1<<8] = {
	0xb023, 0x1032, 0xb334, 0x2231, 0x3234, 0xd135, 0xa323, 0xb031, 0xb042,
	0x5334,
	0x0131,
	0x9531,
	0xe225,
	0xc352
};

uint16_t rotateBinary(uint16_t number){
	uint16_t res = 0;
	while(number>0){
		res=res<<1;
		res = res|(number & 1);
		number=number>>1;
	}
	return res;
}

int main(void)
{
	// Some pins of PORTC can not be used for I/O directly.
	// turn of JTAG to use them
	// o write a 1 to the JTD bit twice consecutively to turn it off
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	
	DDRB = 0x00;	// input pc
	
	// Instruction : D[7:0]C[7:0]
	DDRA = 0xFF;	// lower 8-bits of instruction
	DDRC = 0xFF;	// upper 8-bits of instruction
	
	uint8_t pc = -1;
	uint16_t instruction;
	/* Replace with your application code */
	while (1)
	{
		if (PINB != pc) {
			pc = PINB;
			instruction = INSTRUCTIONS[pc];
			PORTA = (uint8_t) instruction & 0xff;
			PORTC = (uint8_t) rotateBinary(instruction >> 8);
			//PORTC = (uint8_t) (instruction >> 8);
			_delay_ms(50);
		}
	}
}

