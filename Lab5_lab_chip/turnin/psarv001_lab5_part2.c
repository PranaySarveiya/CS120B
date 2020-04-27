/*      Author: psarv001
 *       *  Partner(s) Name:
 *        *      Lab Section:
 *         *      Assignment: Lab #  Exercise #
 *          *      Exercise Description: [optional - include for your own benefit]
 *           *
 *            *      I acknowledge all content contained herein, excluding template or example
 *             *      code, is my own original work.
 *              */

//Demo Link: https://drive.google.com/drive/folders/193VjlynCshF18LRWjBj55B2omuUOmQii?usp=sharing

#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char tempC = 0x00;
unsigned char tempA = 0x00;
enum States {init, chck, inc, dec, reset, wait} state;
void Tick() {
	tempA = PINA;
        switch(state) { //Transitions
                case init : //Initial Transition
			PORTC = 0x07;
			state = chck;
			
                 break;

                case chck :
			tempC = PORTC;
			if( (~tempA & 0x01) && !(~tempA & 0x02) && (tempC < 0x09) ) {
				state = inc;
			}
			else if( !(~tempA & 0x01) && (~tempA & 0x02) && (tempC > 0x00) ) {
				state = dec;	
			}
			else if( (~tempA & 0x01) && (~tempA & 0x02)) {
				state = reset;
			}
			else {
				state = chck;
			}
                 break;

                case inc :
		//	PORTC += 0x01;
			state = wait;
                 break;

                case reset :
		//	PORTC = 0x00;
			if(!(~tempA & 0x01) && !(~tempA & 0x02)) {
				state = chck;
			}
			else {
				state = reset;
			}
			
                 break;

                case dec :
		//	PORTC -= 0x01;
			state = wait;
                 break;

                case wait :
			if((~tempA & 0x01) && (~tempA & 0x02)) {
				state = reset;
			}
			else if( !(~tempA & 0x01) && !(~tempA & 0x02) ) {
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
			PORTC = 0x00;
                 break;

                case dec :
			PORTC -= 0x01;
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

