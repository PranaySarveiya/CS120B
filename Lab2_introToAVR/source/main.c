 /*	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	unsigned char tempDiff = 0x00;
	unsigned char overwrite = 0x00;
	unsigned char A = 0x00;
	unsigned char B = 0x00;
	unsigned char C = 0x00;
	unsigned char D = 0x00;

	unsigned char totalWeight = 0x00;

	while (1) {
		A = PINA;
		B = PINB;
		C = PINC;
		

		totalWeight = A + B + C;
		//PD0	
		if(A + B < A || A + C < A || B + C < B || totalWeight < (A + B) || totalWeight < (A + C) || totalWeight < (B + C) ) {
			//overwriting somewhere
			overwrite = 0x01;
			D = D | 0x01;
		}
		else {
			if(A + B + C > 140) {
				D = D | 0x01;
			}
			else {
				D = D & 0xFE;
			}
		}

		//PD1
		if( A > C ) {
			tempDiff = A - C;
		}
		else {
			tempDiff = C - A;
		}
		if(tempDiff > 80) {
			D = D | 0x02;
		}
		else {
			D = D & 0xFD;
		}
		
		//PD7 - PD2
		if(~overwrite) {
			totalWeight = totalWeight & 0xFC;
			D = D | totalWeight;
		}		
		PORTD = D;


	return 1;

	}
}













