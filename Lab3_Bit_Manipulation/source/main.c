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

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {	//x: 8 bit value, k: bit position to set, b: set bit to this (1 or 0)
	return ( b ? (x | (0x01 << k) ) : (x & ~(0x01 << k) )  );
}

int main(void) {
    /* Insert DDR and PORT initializations */

    /* Insert your solution below */
    
	DDRA = 0x00; PORTA = 0xFF;	//input
	DDRC = 0xFF; PORTC = 0x00;	//output
	
	unsigned char tempA = 0x00;
	unsigned char tempC = 0x00;
	
	while(1) {
		tempA = PINA & 0x0F;
		if(tempA >= 1) {
			tempC = SetBit(tempC, 5, 1);
		}
		if(tempA >= 3) {
                        tempC = SetBit(tempC, 4, 1);
                }
		if(tempA >= 5) {
                        tempC = SetBit(tempC, 3, 1);
                }
		if(tempA >= 7) {
                        tempC = SetBit(tempC, 2, 1);
                }
		if(tempA >= 10) {
                        tempC = SetBit(tempC, 1, 1);
                }
		if(tempA >= 13) {
                        tempC = SetBit(tempC, 0, 1);
                }
		
		if(tempA <= 4) {
			tempC = SetBit(tempC, 6, 1);
		}
		
		PORTC = tempC;
		tempA = 0x00;
		tempC = 0x00;




	}
	return 1;
}
