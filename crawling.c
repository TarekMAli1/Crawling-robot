/*
 * crawling.c
 *
 * Created: 6/18/2022 7:26:04 PM
 *  Author: mega
 */ 
/*machine learning code*/
#include "crawling.h"
#include "Datatypes.h"
#include "servo.h"
#include <stdio.h>
 #include <stdlib.h>
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 
extern u8 volatile counter;

u8 currentStateCLK;																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																					
 u8 currentDir ;
 u8 lastStateCLK;

volatile u8 oldcounter;
volatile u8 currentcounter;
struct action{
	u8 value;
	};
	
struct states{
	struct action actions[NOofActions];
};

struct motors{
	u8 Servo1;
	u8 Servo2;
	};

struct motors  MappedActions[9];

void initFunction(){
	for (int i=0;i<3;i++)
	{
		MappedActions[i].Servo1=0; MappedActions[i].Servo2=i*90;
	}
	for (int i=3;i<6;i++)
	{
		MappedActions[i].Servo1=90; MappedActions[i].Servo2=(i-3)*90;
	}
	for (int i=6;i<9;i++)
	{
		MappedActions[i].Servo1=180; MappedActions[i].Servo2=(i-6)*90;
	}
}
float random_e(){
	//srand(time(NULL));
	float r = (float) (rand() / RAND_MAX);
	return r;
}
int random_action(int max){
	//srand(time(NULL));
	int r = rand() % max;
	return r;
}
struct states Q_table[NOofstates];
										//* Qtable intialization */
void Q_tableInit()
{
	for(int i=0;i<NOofstates;i++){
		for (u8 j=0;j<NOofActions;j++)
		{
			Q_table[i].actions[j].value=0;
		}
	}
}

s8 get_max(u8 currentState)
{
	s8 max = -100;
	for(u8 i=0;i<NOofActions;i++){
		if (max<Q_table[currentState].actions[i].value){
			max= Q_table[currentState].actions[i].value;
		}
	}
	return max;
}
/*greedy function that returns next state*/ 
u8 greedy(u8 currentState)
{
	u8 optimalAction;
    int eps=random_action(10);
    if(eps < epsilon)
    {
    /*  Q_table[s1_state][s2_state].actions[0][3].value=-5;
        Q_table[s1_state][s2_state].actions[0][4].value=-6;
        Q_table[s1_state][s2_state].actions[1][1].value=-9;
        Q_table[s1_state][s2_state].actions[2][2].value=-1;
        Q_table[s1_state][s2_state].actions[2][6].value=-10;*/
    s8 max = -100;
		for(u8 i=0;i<NOofActions;i++){
			if (max<Q_table[currentState].actions[i].value){
				max= Q_table[currentState].actions[i].value;
				optimalAction= i;
			}
		}
    }
    else{
        optimalAction=random_action(NOofActions);
    }
	return optimalAction;
}

/*update qtable using the by the reward*/ 

void update_Qtable(u8 currentState,u8 currentAction){//has error
	/*TD(S,A)= reward + gama.maxQ(st+1,A)-Q(st,At) */
	s8 reward=(currentcounter-oldcounter)/2;
	if(reward==0) reward=-5;
	s8 TD, oldQval;
    s8 max = get_max(currentState);
	oldQval= Q_table[currentState].actions[currentAction].value;
	TD = reward+(gama*max)-oldQval;
	Q_table[currentState].actions[currentAction].value= oldQval+alpha*TD ;
}



void learning()
{
	Q_tableInit();
	initFunction();
	int episodes = 4000;
	u8 any= random_action(8);
	u8 servo1_init=MappedActions[any].Servo1;
	u8 servo2_init=MappedActions[any].Servo2;
	servo1(servo1_init);
	servo2(servo2_init);
	while(episodes > 0)	
	{
		u8 opti;
		opti = greedy(any);
		u8 s1_action = MappedActions[opti].Servo1;
		u8 s2_action = MappedActions[opti].Servo2;
		servo1(opti);
		servo2(s2_action);
		update_Qtable(any, opti);
		any = opti;
		servo1(1);
		episodes--;
	
	}
}
int main (void)
{
	dec();
	learning();
	while(1){
		
		
		};

}



ISR(INT0_vect)
{
	currentStateCLK = PIND &(1<<PIND2);
	oldcounter = counter;

	if (currentStateCLK != lastStateCLK  && currentStateCLK == 0){
		PORTC = 0X00;

		if ( (PIND & (1 << PIND3)) != currentStateCLK) {
			counter -=2;
			currentDir =1;
			PORTC |=(1<<PC0);
			PORTC &=~(1<<PC1);

		} else {
			// Encoder is rotating CW so increment
			counter +=2;
			currentDir =0;
			PORTC |=(1<<PC1);
			PORTC &=~(1<<PC0);

		}
		
	}
	currentcounter = counter;
}


