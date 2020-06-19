/*	Author: lab
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
unsigned char i = 0;
unsigned char soundOn = 0;
double arr[8] = {261.63,293.66,329.63,349.23,392.00,440.00,493.88,523.25};
enum States {init, up, down, on, off} state;
void Tick() {
	tmpA = ~PINA;
	switch(state) {	//Transitions
		case init :
			if(tmpA == 0x01 && soundOn && i < 7) {
				state = up;
				++i;
				set_PWM(arr[i]);
			}
			else if(tmpA == 0x02 && soundOn && i > 0) {
				state = down;
				--i;
				set_PWM(arr[i]);
			}
			else if(tmpA == 0x04 && !soundOn) {
				state = on;
			}
			else if(tmpA == 0x04 && soundOn) {
				state = off;
			}
			else {
				state = init;
			}
		break;

		case up :
			state = (tmpA == 0x01) ? up : init;
		break;
		case down :
			state = (tmpA == 0x02) ? down : init;
		break;
		case on :
			if(tmpA == 0x04) {
				state = on;
			}
			else {
				state = init;
				soundOn = !soundOn;

			}
		break;
		case off :
			if(tmpA == 0x04) {
				state = off;
			}
			else {
				state = init;
				soundOn = !soundOn;
			}
		break;
		default :
		break;
	}

	switch(state) { //State Actions
		case init :
			
		break;
		case up :
			
		break;
		case down :

		break;
		case off :
			PWM_off();
		break;
		case on :
			PWM_on();
			set_PWM(arr[i]);
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
	PWM_off();
	
	state = init;
    while (1) {
	Tick();	
    }
    return 1;
}
