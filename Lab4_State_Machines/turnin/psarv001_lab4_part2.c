/*      Author: psarv001
 *       *  Partner(s) Name:
 *        *      Lab Section:
 *         *      Assignment: Lab #  Exercise #
 *          *      Exercise Description: [optional - include for your own benefit]
 *           *
 *            *      I acknowledge all content contained herein, excluding template or example
 *             *      code, is my own original work.
 *              */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempC = 0x00;
enum States {init, chck, inc, dec, reset, wait} state;
void Tick() {
        switch(state) { //Transitions
                case init : //Initial Transition
			PORTC = 0x07;
			state = chck;
			
                 break;

                case chck :
			tempC = PORTC;
			if( (PINA & 0x01) && !(PINA & 0x02) && (tempC < 0x09) ) {
				state = inc;
			}
			else if( !(PINA & 0x01) && (PINA & 0x02) && (tempC > 0x00) ) {
				state = dec;	
			}
			else if( (PINA & 0x01) && (PINA & 0x02)) {
				state = reset;
			}
			else {
				state = chck;
			}
                 break;

                case inc :
		//	PORTC += 1;
			state = wait;
                 break;

                case reset :
		//	PORTC = 0;
			if(!(PINA & 0x01) && !(PINA & 0x02)) {
				state = chck;
			}
			else {
				state = reset;
			}
			
                 break;

                case dec :
		//	PORTC -= 1;
			state = wait;
                 break;

                case wait :
			if((PINA & 0x01) && (PINA & 0x02)) {
				state = reset;
			}
			else if( !(PINA & 0x01) && !(PINA & 0x02) ) {
				state = chck;
			}
			else {
				state = wait;
			}
                 break;

                default :
                 break;
        }

        switch(state) { //State Actions
                case init :
                 break;

                case chck :

                 break;

                case inc :
			PORTC = PORTC + 0x01;
                 break;

                case reset :
			PORTC = 0;
                 break;

                case dec :
			PORTC -= 1;
                 break;

                case wait :
                 break;

                default :
                 break;
        }
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRC = 0xFF; PORTC = 0x00; //output
    /* Insert your solution below */
	while(1) {
		Tick();
	}

}


