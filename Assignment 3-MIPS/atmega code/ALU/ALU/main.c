/*
 * ALU.c
 *
 * Created: 2/18/2023 11:17:36 AM
 * Author : anamul hoque
 */ 

#include <avr/io.h>
#define F_CPU 1000000 // Clock Frequency
#include <util/delay.h>


int main(void)
{
	// Some pins of PORTC can not be used for I/O directly.
	// turn of JTAG to use them
	// o write a 1 to the JTD bit twice consecutively to turn it off
	MCUCSR = (1<<JTD);  MCUCSR = (1<<JTD);
	DDRA = 0x1F;				// ALUOp A[7:5]
	DDRB = 0x00;				// A[3:0], B[7:4]
	DDRC = 0x8f;				// C[7] - Zero Flag | C[3:0] - Output

	uint8_t control_bits;
	uint8_t in1, in2, out;

//	while (1)



out = 0;
while (1)
	{
			
		control_bits = (PINA >> 5) & 0x07;

		in1 = PINB & 0x0f;
		in2 = (PINB & 0xf0) >> 4;

		if(control_bits == 0) {
			out = in1 & in2;
			} else if(control_bits == 1){
			out = in1 | in2;
			} else if(control_bits == 2) {
			out = in1 + in2;
			} else if(control_bits == 3) {
			out = in1 - in2;
			} else if(control_bits == 4) {
			out = ~(in1 | in2);
			} else if(control_bits == 6) {
			out = in1 << in2;
			} else if(control_bits == 7) {
			out = in1 >> in2;
		}

		out = out & 0x0f;
		if(!out) {
			out = out | 0x80;
		}

		PORTC = out;
		
	}
}



