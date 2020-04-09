 /*	Lab Section: 025
 *	Assignment: Lab #1  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *	Garage open at night-- A garage door sensor connects to PA0 (1 means door open), and a light sensor connects to PA1 (1 means light is sensed). Write a program that illuminates an LED connected to PB0 (1 means illuminate) if the garage door is open at night.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	//unsigned char temp_input = 0x00;
	unsigned char tmpA = 0x00;
	while (1) {
		tmpA = PINA & 0x03;
		if(tmpA == 0x01) {
			PORTB = 0x01;
		}
		else {
			PORTB = 0x00;
		}
	}
}
