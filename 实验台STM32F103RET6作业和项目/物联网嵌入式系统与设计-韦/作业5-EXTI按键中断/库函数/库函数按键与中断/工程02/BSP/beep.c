//Filename: led.c

#include "includes.h"

void BEEPInit(void)
{

	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOB, ENABLE);
	
	g.GPIO_Pin = GPIO_Pin_9;
	g.GPIO_Mode = GPIO_Mode_Out_PP;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &g);
	//GPIO_SetBits(GPIOB, GPIO_Pin_5);
	
	//BEEP(BEEP_OFF);
	//BEEP(BEEP_OFF);
}


void BEEP(BEEPState s) //w-which(1or2), s-state(LED_ONorLED_OFF)
{

			if(s==BEEP_ON){
				//GPIOB->ODR &= ~(1uL<<5);
				GPIO_ResetBits(GPIOB,GPIO_Pin_9);}
			else{
				//GPIOB->ODR |= (1uL<<5);
			  GPIO_SetBits(GPIOB, GPIO_Pin_9);}


	
}

