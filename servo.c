

#include <avr/io.h>
#include "Datatypes.h"
#include "std_macros.h"
void init(double value){
	SET_BIT(DDRB,1);
	SET_BIT(TCCR1A,COM1A1);	
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,CS11);
	
	ICR1=10000-1;
	OCR1A=500*value;
}

void servo1(u8 ang)
{
	if(ang == 0)
	init(1);
	else{
			double temp =(double) ang*8/180;
			init(temp);
	}

	
}

void init2 (double value){
	SET_BIT(DDRB,1);
	SET_BIT(TCCR1A,COM1A1);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	SET_BIT(TCCR1B,WGM13);
	SET_BIT(TCCR1B,CS11);
	ICR1=10000-1;
	OCR1B=500*value;
}

void servo2(u8 ang)
{
	double temp =(double) ang*8/180;
	init2(temp);
}