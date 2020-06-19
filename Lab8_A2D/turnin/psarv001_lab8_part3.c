/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Lab Demo Link: https://drive.google.com/drive/folders/1Dx8XPjNVeveRlQ864RmOknijaXU2rkV7?usp=sharing

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */

	ADC_init();
	unsigned short x = ADC;
	unsigned short max = 0;
	
	unsigned char tmpB;
	unsigned char tmpD;
    	while (1) {
		x = ADC;
		tmpD = (char) (x >> 8);
		tmpB = (char) x;

		//get max light
		if(x > max) {
			max = x;
		}
		if(x >= max / 2) {
			PORTD = tmpD;
			PORTB = tmpB;
		}
		else {
			PORTD = 0;
			PORTB = 0;
		}
    	}	
  	return 1;
}
