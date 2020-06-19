/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */

//Lab Demo Link: https://drive.google.com/drive/folders/1-IhSoWyiV-spzctLEzXCWhHcxvtyhEQe?usp=sharing

#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0;

unsigned long avr_timer_M = 1;
unsigned long avr_timer_cntcurr = 0;

void TimerOn() {
        TCCR1B = 0x0B;
        OCR1A = 125;
        TIMSK1 = 0x02;
        TCNT1 = 0;
        avr_timer_cntcurr = avr_timer_M;
        SREG |= 0x80;
}

void TimerOff() {
        TCCR1B = 0x00;
}

void TimerISR() {
        TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
        avr_timer_cntcurr--;
        if(avr_timer_cntcurr == 0) {
                TimerISR();
                avr_timer_cntcurr = avr_timer_M;
        }
}

void TimerSet(unsigned long M) {
        avr_timer_M = M;
        avr_timer_cntcurr = avr_timer_M;
}



unsigned char threeLEDs;


enum States_1 {light_1} state_1;
unsigned char i = 0;
void ThreeLEDsSM() {
	switch(state_1) { //Transitions
		case light_1 :
			state_1 = light_1;
		
		break;
		default :
			state_1 = light_1;
		break;
	}
	switch(state_1) { // Actions
		case light_1 :
			if(i == 3) {
				threeLEDs = 0x01;
			}
			else if(i == 6) {
				threeLEDs = 0x02;
			}
			else if(i == 9) {
				threeLEDs = 0x04;
				i = 0;
			}
				++i;
		break;
		default :

		break;
	}

}

unsigned char blinkingLED;
enum States_2 {light_2} state_2;
unsigned char j = 0;
void BlinkingLEDSM() {
	switch(state_2) {
		case light_2 :
			state_2 = light_2;
		break;
		default :
		break;
	}

	switch(state_2) {
		case light_2 :
			if(j == 10) {
				blinkingLED = (blinkingLED == 0) ? 0x08 : 0x00;
				j = 0;
			}
				++j;
		break;
		default :
		break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	TimerSet(100);
	TimerOn();

	state_1 = light_1;
	state_2 = light_2;
    while (1) {
	ThreeLEDsSM();
	BlinkingLEDSM();
	PORTB = blinkingLED | threeLEDs;
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}
