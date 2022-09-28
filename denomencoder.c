/*
 * denomencoder.c
 *
 * Created: 19/06/2022 22:25:01
 *  Author: DELL
 */ 


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "Datatypes.h"

u8 volatile counter = 0;
u8 currentStateCLK;
extern u8 lastStateCLK;

void dec(void)
{
	DDRD &=~ (1<<2)|(1<<3);
	DDRC = 0xFF;
	PORTC = 0xFF;
	EIMSK|=(1<<INT0);
	EICRA|=(1<<ISC00);
	sei();
	lastStateCLK = PIND &(1<<PIND2);
}
