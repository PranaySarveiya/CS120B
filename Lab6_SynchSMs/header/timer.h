
volatile unsigned char TimerFlag = 0;

unsigned long avr_timer_M = 1;
unsigned long avr_timer_cntcurr = 0;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;
	avr_timer_cntcurr = avr_timer_M;
	SREG |= 0x08;
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

