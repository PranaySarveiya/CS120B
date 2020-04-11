 /*	Pranay Sarveiya
 *	Lab Section: 025
 *	Assignment: Lab #1  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *	(Challenge) An amusement park kid ride cart has three seats, with 8-bit weight sensors connected to ports A, B, and C (measuring from 0-255 kilograms). Set PD0 to 1 if the cart's total passenger weight exceeds the maximum of 140 kg. Also, the cart must be balanced: Set port PD1 to 1 if the difference between A and C exceeds 80 kg.  The remaining 6 bits on D should display an approximation of the total combined weight, accuratew within 3 kg.
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

//If the weight goes over the maximum 255 and circles back to zero, I set the approximate weight to be 0 to indicate an error

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0x00; PORTB = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	

	unsigned char tmpA = 0x00;
	unsigned char tmpB = 0x00;
	unsigned char tmpC = 0x00;
	unsigned char tmpD = 0x00;
	unsigned char tmpSum = 0x00;
	while(1) {
		tmpA = PINA;
		tmpB = PINB;
		tmpC = PINC;
		tmpSum = tmpA + tmpB + tmpC;
		if( !((tmpA + tmpB < tmpA) | (tmpA + tmpC < tmpA) | (tmpB + tmpC < tmpB) | (tmpSum < tmpA + tmpB) | (tmpSum < tmpA + tmpC) | (tmpSum < tmpB + tmpC)) ) {
			//no overwrite
			tmpD = tmpD | (tmpSum & 0xFC);
			if(tmpSum > 140) {
				//Set PD0
				tmpD = tmpD | 0x01;
			}	

		}
		else {
			tmpD = tmpD | 0x01;
			
	
		}
		if(tmpA >tmpC) {
			if(tmpA - tmpC > 80) {
				tmpD = tmpD | 0x02;
			}
		}
		else {
			if(tmpC - tmpA > 80) {
				tmpD = tmpD | 0x02;
			}
		}
	PORTD = tmpD;


        tmpA = 0x00;
        tmpB = 0x00;
        tmpB = 0x00;
        tmpD = 0x00;
        tmpSum = 0x00;

	}
}

