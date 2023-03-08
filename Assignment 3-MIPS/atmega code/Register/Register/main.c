/*
 * Register.c
 *
 * Created: 2/18/2023 11:29:10 AM
 * Author : anamul hoque
 */ 

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

#define WRITE_REG_	0x01
#define CLK_		0x02
#define RESET_		0x04
#define OUTPUT_		0x08

uint8_t REGISTOR[8] = {0};

int main(void)
{
	// Some pins of PORTC can not be used for I/O directly.
	// turn of JTAG to use them
	// o write a 1 to the JTD bit twice consecutively to turn it off
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	DDRA = 0xF0;	// A[0] - WriteReg, A[1] - CLK, A[2] - RESET
	DDRB = 0x00;	// B[3:0] - Write Data, B[7:4] - DstReg
	
	DDRC = 0xFF;	// C[3:0] - $1, C[7:4] - $2
	DDRD = 0x00;	// D[3:0] - SrcReg2, D[7:4] - SrcReg1
	
	
	uint8_t src, dst_data, last_control = 0, current_control;
	
	while (1)
	{
		src = PIND;
		dst_data = PINB;
		current_control = PINA;
		
		PORTC = (REGISTOR[(src&0x7)]<<4) | (REGISTOR[src>>4]);
		if (current_control&RESET_) {
			for (uint8_t i=0; i<8; i++) REGISTOR[i] = 0;
			_delay_ms(100);
			continue;
		}
		
		if ((current_control^last_control)&CLK_) {							// EDGE
			if ((last_control&CLK_) && (last_control&WRITE_REG_)) {	// NEGATIVE EDGE with WRITE INSTRUCTION
				REGISTOR[dst_data>>4] = (dst_data&0x7);
				PORTA = (dst_data<<4) & 0xf0;
			}
			_delay_ms(100);
		}
		
		last_control = current_control;
	}
}



