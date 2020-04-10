 /*	Lab Section:
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

//If the weight goes over the maximum 255 and circles back to zero, I set the approximate weight to be 0 to indicate an error
unsigned char GetBit (unsigned char x, unsigned char k) {
	return ( (x & (0x01 << k) ) != 0 );
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0x00; PORTC = 0xFF;
    /* Insert your solution below */
	
	unsigned char tmpA = 0x00;
	unsigned char i = 0x00;
	unsigned char countavail = 0x00;
	
	while(1) {
		tmpA = PINA;
		for(i = 0; i < 4; ++i) {
			countavail += GetBit(tmpA, i);
		}
		PORTC = countavail;
		countavail = 0x00;
	}
	

}
