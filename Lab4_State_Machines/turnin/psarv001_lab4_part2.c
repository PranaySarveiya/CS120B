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


enum States {init, chck, inc, dec, reset} state;
void Tick() {
	switch(state) {	//Transitions
		case init : //Initial Transition
			state = chck;
			PORTC = 0x07;
		 break;
		
		case chck :
			if( (PINA & 0x01) && !(PINA & 0x02) && PORTC < 9) {
				state = inc;
			}
			else if( (PINA & 0x01) && (PINA & 0x02)) {
				state = reset;
			}
			else if( (PINA & 0x02) && !(PINA & 0x01) && PORTC > 0) {
				state = dec;
			}
			else {
				state = chck;
			}
		 break;
		
		case inc :
			state = chck;
		 break;
		
		case reset : 
			state = chck;
		 break;
		
		case dec :
			state = chck;
		 break;

		default :
			state = init;
		 break;
	}	

	switch(state) {	//State Actions
		case init :
			//PORTC = 0x07;
		 break;
		
		case chck :
		 break;

		case inc : 
			PORTC += 1;
		 break;

		case reset :
			PORTC = 0;
		 break;
		
		case dec :
			PORTC -= 1;
		 break;

		default :
		 break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	//input
	DDRC = 0xFF; PORTC = 0x00;	//output
    /* Insert your solution below */
	state = init;
	while(1) {
		Tick();
	
	}	  

}






