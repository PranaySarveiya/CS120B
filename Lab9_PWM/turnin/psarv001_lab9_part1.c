/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */



//Lab Demo Link : https://drive.google.com/drive/folders/1Dx8XPjNVeveRlQ864RmOknijaXU2rkV7?usp=sharing



#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void set_PWM(double frequency) {
	static double current_frequency;


	if(frequency != current_frequency) {
		if(!frequency) {
			TCCR3B &= 0x08;
		}
		else {
			TCCR3B |= 0x03;
		}
		if(frequency < 0.954) {
			OCR3A = 0xFFFF;
		}
		else if(frequency > 32150) {
			OCR3A = 0x0000;
		}
		else {
			OCR3A = (short) (8000000 / (128 * frequency)) - 1;
		}
		TCNT3 = 0;
		current_frequency = frequency;
	}
	
}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}


unsigned char tmpA;
unsigned char tmpB;
enum States {init, one, two, three} state;
void Tick() {
	tmpA = ~PINA;
	switch(state) {	//Transitions
		case init :
			if(tmpA == 0x00 || tmpA == 0x03 || tmpA == 0x06 || tmpA == 0x05) {
				state = init;
			}
			else if(tmpA == 0x01) {
				PWM_on();
				set_PWM(261.63);
				state = one;
			}
			else if(tmpA == 0x02) {
				PWM_on();
				set_PWM(293.66);
				state = two;
			}
			else if(tmpA == 0x04) {
				PWM_on();
				set_PWM(329.63);
				state = three;
			}
		break;
		case one :
			if(tmpA == 0x01) {
				state = one;
			}
			else {
				PWM_off();
				state = init;
			}
		break;
		case two :
			if(tmpA == 0x02) {
				state = two;
			}
			else {
				PWM_off();
				state = init;
			}
		break;
		case three :
			if(tmpA == 0x04) {
				state = three;
			}
			else {
				PWM_off();
				state = init;
			}
		break;
		
		default :
		break;
		
	}

	switch(state) { //State Actions
		case init : 
			//speaker off
		break;
		case one :
			//speaker C4
		break;
		case two :
			//speaker D4
		break;
		case three :
			//Speaker E4
		break;

	}
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	PWM_off();
	
	
    while (1) {
	Tick();	
    }
    return 1;
}
