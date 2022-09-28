/*
 * Rotary.h
 *
 * Created: 6/16/2022 11:01:43 PM
 *  Author: ELNOOR
 */ 


#ifndef ROTARY_H_
#define ROTARY_H_

//define port where encoder is connected
#define ROTPORT PORTB
#define ROTDDR DDRB
#define ROTPIN PINB
//define rotary encoder pins
#define ROTPA 2
#define ROTPB 3
#define ROTPBUTTON 4

void Rotary_vInit();




#endif /* ROTARY_H_ */