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

unsigned char DoLock = 0x00;

enum States {init, lock, pressHash, releaseHash, unlock} state;
void Tick() {
	switch(state) {	//Transitions
		case init : //Initial Transition
			state = lock;
			PORTB = 0x00;
			DoLock = 0x00;
		  break;
		
		case lock :
			DoLock = 0x00;
			state = ( (PINA & 0x04) && !(PINA & 0x02) && !(PINA & 0x01) ) ? pressHash : lock;
		 break;
		
		case pressHash :
			if( (PINA & 0x04) && !(PINA & 0x02) && !(PINA & 0x01) ) {
				state = pressHash;
			}
			else if( !(PINA & 0x04) && !(PINA & 0x02) && !(PINA & 0x01) ) {
				state = releaseHash;
			}
			else {
				if(DoLock) {
					state = unlock;
				}
				else {
					state = init;
				}
			}
		 break;
		
		case releaseHash : 
			if( !(PINA & 0x04) && !(PINA & 0x02) && !(PINA & 0x01) ) {
				state = releaseHash;
			}
			else if( !(PINA & 0x04) && (PINA & 0x02) && !(PINA & 0x01) ) {
				if(DoLock) {
					state = lock;
				}
				else {
					state = unlock;
				}
			}
			else {
				if(DoLock) {
                                        state = unlock;
                                }
                                else {
                                        state = init;
                                }
			}
		 break;
		

		case unlock :
			if(PINA & 0x80) {
				state = lock;
			}
			else if((PINA & 0x04) && !(PINA & 0x02) && !(PINA & 0x01)) {
				state = pressHash;
				DoLock = 0x01;
				PORTB = 0x01;
			}
			else {
				state = unlock;
			}
		 break;
		
		default :
			state = init;
		 break;
	}	

	switch(state) {	//State Actions
		case init :
			PORTB = 0x00;
			//action done in transition
		 break;
		
		case lock :
			PORTB = 0x00;
		 break;

		case pressHash : 
		 break;

		case releaseHash :
		 break;
		
		case unlock :
			PORTB = 0x01;
		 break;

		default :
		 break;
	}

}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;	//input
	DDRB = 0xFF; PORTB = 0x00;	//output
    /* Insert your solution below */
	state = init;
	while(1) {
		Tick();
	
	}	  

}






