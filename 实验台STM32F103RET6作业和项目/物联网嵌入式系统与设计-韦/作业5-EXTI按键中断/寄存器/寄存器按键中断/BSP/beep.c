//Filename: beep.c

#include "includes.h"

void BEEPInit(void)
{
	RCC->APB2ENR |= (1uL<<3); //PB Clock
	GPIOB->CRH |= (1uL<<4);
	GPIOB->CRH &=~(7uL<<1);  //PB9 Output 10MHz, Push-Pull
	
	GPIOB->ODR &= ~(1uL<<9); //Close BEEP
}

void BEEP(BEEPState s)
{
	if(s==BEEP_ON){
				//GPIOC_Pin13_?????
				//GPIOC->BRR = 0x00002000; 
				GPIOB->BRR |=(1uL<<9);
				//GPIOB->BRR &=~(1uL<<9);
			/*(1uL<<13)*/
	}
			else{
				//GPIOC_Pin13_?????
			 GPIOB->ODR |=(1uL<<9);
				//GPIOB->ODR &=~(1uL<<9);
			/*(1uL<<13);*/
			  //GPIOB_ODR |= (1uL<<5);
	}
}
