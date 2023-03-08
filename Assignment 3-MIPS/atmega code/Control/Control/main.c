/*
 * Control.c
 *
 * Created: 2/18/2023 11:23:51 AM
 * Author : anamul hoque
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

uint16_t CONTROL_ROM[1<<4] = {0x230, 0x628, 0x430, 0x630, 0xE30, 0x5A8, 0xC30, 0x604, 0x602, 0x028, 0x448, 0x428, 0x030, 0x830, 0x228, 0x001};
	
uint8_t rotateBinary(uint8_t number){
	uint8_t res = 0;
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
	
	DDRB = 0x0F; // B[7:4] - Opcode Input
	
	// Control Unit Bits : C[3:0]D[7:0]
	// C[alu_op[3], mem_to_reg[1]] D[mem_read[1], mem_write[1], reg_write[1], reg_dst[1], alu_src[1], branch_neq[1], branch[1], jump[1]]
	DDRC = 0xFF;
	DDRD = 0xFF;
	
	
	uint8_t opcode = ~0;
	
	while (1)
	{
		if (opcode != (0x0F & rotateBinary(PINB >> 4))) {
			opcode = (0x0F & rotateBinary(PINB >> 4));
			PORTD = CONTROL_ROM[opcode];
			PORTC = ((CONTROL_ROM[opcode] >> 8) & 0x0F);
			_delay_ms(50);
		}
	}
}


