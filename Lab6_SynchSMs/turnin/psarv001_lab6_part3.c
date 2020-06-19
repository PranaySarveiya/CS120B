#include <avr/io.h>
#ifdef _SIMULATE_
#include <avr/interrupt.h>
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




unsigned char i = 0x00;
unsigned char tempC = 7;
unsigned char tempA = 0x00;
enum States {init, chck, inc, dec, reset, waitInc, waitDec} state;
void Tick() {
	tempA = PINA;
        switch(state) { //Transitions
                case init : //Initial Transition
			state = chck;
			
                 break;

                case chck :
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
			state = waitInc;
                 break;

                case reset :
			if(!(~tempA & 0x01) && !(~tempA & 0x02)) {
				state = chck;
			}
			else {
				state = reset;
			}
			
                 break;

                case dec :
			state = waitDec;
                 break;
		
		case waitInc :
			if((~tempA & 0x01) && (~tempA & 0x02)) {
                                state = reset;
				i = 0;
                        }
			else if(i >= 10) {
                                state = inc;
                                i = 0;
                        }

			else if( (~tempA & 0x01) && !(~tempA & 0x02) && (tempC < 0x09) ) {
                                ++i;
                        }

			else if( !(~tempA & 0x01) && !(~tempA & 0x02) ) {
                                state = chck;
				i = 0;
                        }

		break;
		case waitDec :
			if((~tempA & 0x01) && (~tempA & 0x02)) {
                                state = reset;
				i = 0;
                        }
			else if(i >= 10) {
                                state = dec;
                                i = 0;
                        }

                        else if( !(~tempA & 0x01) && (~tempA & 0x02) && (tempC > 0x00) ) {
                                ++i;
                        }
			else if( !(~tempA & 0x01) && !(~tempA & 0x02) ) {
                                state = chck;
				i = 0;
                        }

		break;

                default :
                 break;
        }

        switch(state) { //State Actions
                case init :
			tempC= 7;
                 break;

                case chck :

                 break;

                case inc :
			tempC = tempC + 0x01;
                 break;

                case reset :
			tempC = 0x00;
                 break;

                case dec :
			tempC -= 0x01;

                 break;

                case waitInc :
                 break;

		case waitDec :
		 break;

                default :
                 break;
        }
	PORTC = tempC;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF; //input
	DDRC = 0xFF; PORTC = 0x00; //output
	DDRD = 0xFF; PORTD = 0x00;
    /* Insert your solution below */
	TimerSet(100);
	TimerOn();

	while(1) {
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;

}

