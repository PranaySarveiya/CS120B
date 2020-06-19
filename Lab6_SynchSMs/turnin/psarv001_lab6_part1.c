#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif
//Lab 6 Demo Link: https://drive.google.com/drive/folders/1qAWmOnhMSmQwG7-r69FYCVQe1Nfm-jUF?usp=sharing
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

unsigned char tmpB;
unsigned char i = 0x00;
enum States {init, lights} state;
void TickFct_ThreeLeds() {
	switch(state) {	//Transitions
		case init :
			state = lights;
		break;
		case lights :
			if(i == 1) {
				state = lights;
				tmpB = 0x01;
			}
			else if(i == 2) {
				tmpB = 0x02;
			}
			else if(i == 3) {
				tmpB = 0x04;
				i = 0;
			}
		break;
		
		default :
		break;
	}

	switch(state) {	//State Actions
		case init :
			i = 0;
		break;
		case lights :
			++i;
		break;

		default :
		break;
	}	
	PORTB = tmpB;

}




int  main() {
	DDRB = 0xFF;	PORTB = 0x00;
	TimerSet(1000);
	TimerOn();

	while(1) {
		TickFct_ThreeLeds();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}
