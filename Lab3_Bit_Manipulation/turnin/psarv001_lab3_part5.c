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

int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    
	DDRD = 0x00; PORTD = 0xFF;	//input
	DDRB = 0xFE; PORTB = 0x00;	//output	(B0 is set to input)
	DDRC = 0xFF; PORTC = 0x00;	//output
	
	unsigned char tempD = 0x00;
	unsigned char tempB = 0x00;
	unsigned char temp5 = 0x00;
	while(1) {
		tempD = PIND;
		if(tempD >= 0x23) {
			//B1 - 1
			tempB = tempB | 0x02;
		}
		else {
			temp5 = (tempD << 1) + (tempB & 0x01);
			tempB = (temp5 > 5)  ? (tempB | 0x04) : tempB;
		}
		
		PORTB = tempB;
		
		tempB = 0x00;
		temp5 = 0x00;
	}
	return 1;
}
