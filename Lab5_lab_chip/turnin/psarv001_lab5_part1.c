
	/*	Author: psarv001
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Demo link: https://drive.google.com/drive/folders/193VjlynCshF18LRWjBj55B2omuUOmQii?usp=sharing

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
	
	unsigned char temp = 0x00;
	unsigned char tempC = 0x00;
	
	while(1) {
		temp = ~PINA & 0x0F;
		if(temp == 0) {
			tempC = 0x40;
		}
		else if (temp <= 2) {
			//C5
			tempC = 0x60;
			
		}
		
		else if(temp <= 4) {
			//C4
			tempC = 0x70;
                }
		
		else if(temp <= 6) {
			//C3
			tempC = 0x38;
                }

		else if(temp <= 9) {
			//C2
			tempC = 0x3C;
                }
	
		else if(temp <= 12) {
			//C1
			tempC = 0x3E;
                }

		else if(temp <= 15) {
			//C0
			tempC = 0x3F;
                }
		else {
			//Error
			
		}


		PORTC = tempC;
		temp = 0x00;
		tempC = 0x00;




	}
	return 1;
}

