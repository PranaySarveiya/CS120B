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

unsigned char tmpB = 0x00;
unsigned char i = 0x00;
enum State {init, LED, pause, pause2, LED2} state;
void TickFct_ThreeLeds() {
	switch(state) {	//Transitions
		case init :
			tmpB = 0;
			i = 0;
			state = LED;
		break;
		case LED :
			if(!(~PINA & 0x01) && i == 1) {
				tmpB = 0x01;
				state = LED;
			}
			else if(!(~PINA & 0x01) && i == 4) {
				tmpB = 0x02;
				state = LED;
			}
			else if(!(~PINA & 0x01) && i == 7) {
				tmpB = 0x04;
				state = LED;
			}
			else if(!(~PINA & 0x01) && i == 10) {
                                tmpB = 0x02;
                                state = LED;
                        }
			else if(!(~PINA & 0x01) && i == 12) {
                                i = 0;
                        }
			else if(~PINA & 0x01) {
				state = pause;
			}
			else {
				state = LED;
			}

		break;
		case pause :
			state = (~PINA & 0x01) ? pause : pause2;
		break;
		case pause2 :
			state = !(~PINA & 0x01) ? pause2 : LED2;
		break;
		case LED2 :
			if((~PINA & 0x01) && i == 1) {
                                tmpB = 0x01;
                                state = LED2;
                        }
                        else if((~PINA & 0x01) && i == 4) {
                                tmpB = 0x02;
                                state = LED2;
                        }
                        else if((~PINA & 0x01) && i == 7) {
                                tmpB = 0x04;
                                state = LED2;
                        }
			else if((~PINA & 0x01) && i == 10) {
                                tmpB = 0x02;
                                state = LED2;
                        }
			else if((~PINA & 0x01) && i == 12) {
				i = 0;
			}
			else if(!(~PINA & 0x01)) {
				state = LED;
				i = 0;
			}
			else {
				state = LED2;
			}

		break;
		default :
		break;
	}

	switch(state) {	//State Actions
		case init :
		break;
		case LED :
			++i;
		break;
		case pause :
		break;
		case pause2 :
		break;
		case LED2 :
			++i;
		break;
		default :
		break;
	}	
	PORTB = tmpB;

}


void main() {
	const unsigned long timerPeriod = 100;
	
	DDRA = 0x00; 	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	TimerSet(timerPeriod);
	TimerOn();

	state = init;

	while(1) {
		TickFct_ThreeLeds();
	
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return;
}
