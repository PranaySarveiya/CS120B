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


enum States {init, But1, wait, But2 } state;
void Tick() {
	switch(state) {	//Transitions
		case init : //Initial Transition
			state = (PINA & 0x01) ? But1 : init;
		 break;
		
		case But1 :
			state = (PINA & 0x01) ? But1 : wait;
		 break;
		
		case wait :
			state = (PINA & 0x01) ? But2 : wait;
		 break;
		
		case But2 : 
			state = (PINA & 0x01) ? But2 : init;
		 break;
		
		default :
			state = init;
		 break;
	}	

	switch(state) {	//State Actions
		case init :
			PORTB = 0x01;
		 break;
		
		case But1 :
			PORTB = 0x02;
		 break;

		case wait : 
		 break;

		case But2 :
			PORTB = 0x01;
		 break;
		
		default :
		 break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	state = init;
	while(1) {
		Tick();
	}	  

}






