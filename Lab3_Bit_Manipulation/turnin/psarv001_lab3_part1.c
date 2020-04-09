/*	Author: psarv001
 *  Partner(s) Name: 
 *	Lab Section:
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

unsigned char GetBit (unsigned char x, unsigned char k) {
	return ( (x & (0x01 << k) ) != 0 );
}


int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    
	DDRA = 0x00; PORTA = 0xFF;	//input
	DDRA = 0x00; PORTB = 0xFF;	//input
	DDRC = 0xFF; PORTC = 0x00;	//output

	//unsigned char A = PINA;
	//unsigned char B = PINB;
	unsigned char tmpCount = 0x00;
	unsigned char i = 0x00;
	while (1) {
		for(i = 0; i < 8; ++i) {
			tmpCount = tmpCount + GetBit(PINA, i);
			tmpCount = tmpCount + GetBit(PINB, i);
		}		
		PORTC = tmpCount;
		tmpCount = 0x00;
	}
	return 1;
}
