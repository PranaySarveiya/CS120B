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

unsigned char tempA = 0x00;
unsigned char tempB = 0x00;
enum States {init, one, waitOne, two, waitTwo} state;
void Tick() {
	tempA = ~PINA;
        switch(state) { //Transitions
                case init : //Initial Transition
			tempB = 0x2A;
			state = one;
			
                 break;

                case one :
			state = tempA ? waitOne : one;
                 break;

                case waitOne :
			state = tempA ? waitOne : two;
                 break;

                case two :
			state = tempA ? waitTwo : two;
                 break;

                case waitTwo :
			state = tempA ? waitTwo : one;
                 break;

                default :
                 break;
        }

        switch(state) { //State Actions
                case init :
			tempB = 0x2A;
                 break;

                case one :
                 break;

                case waitOne :
		 	tempB = 0x15;
                 break;

                case two :
                 break;

                case waitTwo :
			tempB = 0x2A;
                 break;

                default :
                 break;
        }
	PORTB = tempB;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRB = 0xFF; PORTB = 0x00; //output
    /* Insert your solution below */
	while(1) {
		Tick();
	}

}

