 /*	Pranay Sarveiya
 *	Lab Section: 025
 *	Assignment: Lab #1  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *	Extend the previous program to still write the available spaces number, but only to PC3..PC0, and to set PC7 to 1 if the lot is full.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char GetBit(unsigned char x, unsigned char k) {
	return ( (x & (0x01 << k) ) != 0 );
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xff; PORTC = 0x00;
    /* Insert your solution below */
	unsigned char cntavail = 0x04;
	unsigned char i = 0x00;
	unsigned tempA = 0x00;
	while (1) {
		tempA = PINA;
		for(i = 0; i < 4; ++i) {
			cntavail -= GetBit(tempA, i);
		}

		if(cntavail == 0x00) {
			cntavail = cntavail | 0x80;
		}
		PORTC = cntavail;
		cntavail = 0x04;
	}
	return 0;

}
