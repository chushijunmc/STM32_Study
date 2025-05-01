//Filename: led.c

#include "includes.h"

//#define  GPIOB_ODR   *(unsigned int *)0x40010C0C

void LEDInit(void)
{
	
	//初始化使能寄存器
	RCC->APB2ENR = 0x00000010;  //0b0000 0000 00110000 00000000 00010000 IOPC = 1;
	//初始化GPIOC的13,14,15管脚
	GPIOC->CRH = 0x33300000; //0b0011 0011 0011 0000 0000 0000 0000 0000 CNF15,14,13 = 00 MODE15,14,13 = 11;
	

}

void LED(Int08U w, LEDState s) //w-which(1or2), s-state(LED_ONorLED_OFF)
{
	switch(w)
	{
		case 0:
			if(s==LED_ON)
				//GPIOC_Pin13_设置高电位
				GPIOC->BRR = 0x00002000; 
			/*(1uL<<13)*/

			else
				//GPIOC_Pin13_设置低电位
			  GPIOC->BSRR = 0x00002000;
			/*(1uL<<13);*/
			  //GPIOB_ODR |= (1uL<<5);
			break;
		case 1:
			if(s==LED_ON)
				//GPIOC_Pin14_设置高电位
			  GPIOC->BRR = 0x00004000;
			/*(1uL<<14);*/	
			else
				//GPIOC_Pin14_设置低电位
				//GPIOE->ODR |= (1uL<<5);
			  GPIOC->BSRR = 0x00004000;
			/* (1uL<<14);*/
		case 2:
			if(s==LED_ON)
				//GPIOC_Pin15_设置高电位
				//GPIOE->ODR &= ~(1uL<<5);
			  GPIOC->BRR = 0x00008000;
			/* (1uL<<15);	*/
			else
				//GPIOC_Pin15_设置低电位
			  GPIOC->BSRR = 0x00008000;
			/*(1uL<<15);*/
			break;
		default:
			break;
	}	
}

