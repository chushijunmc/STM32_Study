//Filename: led.c

#include "includes.h"
void LED(Int08U w, LEDState s);


void LEDInit(void)
{

	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOE, ENABLE);
	
	g.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	g.GPIO_Mode = GPIO_Mode_Out_PP;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &g);
	//GPIO_SetBits(GPIOB, GPIO_Pin_5);
	/*
	g.GPIO_Pin = GPIO_Pin_0;
	g.GPIO_Mode = GPIO_Mode_Out_PP;
	g.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &g);
	//GPIO_SetBits(GPIOE, GPIO_Pin_5);*/
	
	LED(0,LED_OFF);
	LED(1,LED_OFF);
}


void LED(Int08U w, LEDState s) //w-which(1or2), s-state(LED_ONorLED_OFF)
{
	switch(w)
	{
		case 0:
			if(s==LED_ON)
				//GPIOB->ODR &= ~(1uL<<5);
				GPIO_ResetBits(GPIOC,GPIO_Pin_13);
			else
				//GPIOB->ODR |= (1uL<<5);
			  GPIO_SetBits(GPIOC, GPIO_Pin_13);
			break;
		case 1:
			if(s==LED_ON)
				//GPIOE->ODR &= ~(1uL<<5);
				GPIO_ResetBits(GPIOC,GPIO_Pin_14);
			else
				//GPIOE->ODR |= (1uL<<5);
			  GPIO_SetBits(GPIOC, GPIO_Pin_14);
			break;
			case 2:
			if(s==LED_ON)
				//GPIOE->ODR &= ~(1uL<<5);
				GPIO_ResetBits(GPIOC,GPIO_Pin_15);
			else
				//GPIOE->ODR |= (1uL<<5);
			  GPIO_SetBits(GPIOC, GPIO_Pin_15);
			break;
		default:
			break;
	}	
}

