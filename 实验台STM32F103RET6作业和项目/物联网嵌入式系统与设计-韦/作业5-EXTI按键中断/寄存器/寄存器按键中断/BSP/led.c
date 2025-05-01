//Filename: led.c

#include "includes.h"

//#define  GPIOB_ODR   *(unsigned int *)0x40010C0C

void LEDInit(void)
{
	
	//????????
	RCC->APB2ENR = 0x0000001D;  //0b0000 0000 0000 0000 0000 0000 0001 1101 IOPC = 1,IOPB=1,IOPA=1,AFIO=1;
	/*RCC->APB1RSTR = 0x00000000; //0b0000 0000 0000 0000 0000 0000 0000 0000 AFIORST = 1;*/
	//???GPIOC?13,14,15??
	GPIOC->CRH = 0x33300000; //0b0011 0011 0011 0000 0000 0000 0000 0000 CNF15,14,13 = 00 MODE15,14,13 = 11;
	GPIOB->CRH = 0x33300000; //0b0011 0011 0011 0000 0000 0000 0000 0000 CNF15,14,13 = 00 MODE15,14,13 = 11;
	GPIOA->CRH = 0x33300000; //0b0011 0011 0011 0000 0000 0000 0000 0000 CNF15,14,13 = 00 MODE15,14,13 = 11;

}

void LED(Int08U w, LEDState s) //w-which(1or2), s-state(LED_ONorLED_OFF)
{
	switch(w)
	{
		case 0:
			if(s==LED_ON)
				//GPIOC_Pin13_?????
				GPIOC->BRR = 0x00002000; 
			/*(1uL<<13)*/

			else
				//GPIOC_Pin13_?????
			  GPIOC->BSRR = 0x00002000;
			/*(1uL<<13);*/
			  //GPIOB_ODR |= (1uL<<5);
			break;
		case 1:
			if(s==LED_ON)
				//GPIOC_Pin14_?????
			  GPIOC->BRR = 0x00004000;
			/*(1uL<<14);*/	
			else
				//GPIOC_Pin14_?????
				//GPIOE->ODR |= (1uL<<5);
			  GPIOC->BSRR = 0x00004000;
			/* (1uL<<14);*/
		case 2:
			if(s==LED_ON)
				//GPIOC_Pin15_?????
				//GPIOE->ODR &= ~(1uL<<5);
			  GPIOC->BRR = 0x00008000;
			/* (1uL<<15);	*/
			else
				//GPIOC_Pin15_?????
			  GPIOC->BSRR = 0x00008000;
			/*(1uL<<15);*/
			break;
		default:
			break;
	}	
}



/*
	RCC->APB2ENR = 0x00000010; //0b 0000 0000 0000 0000 0000 0000 0001 0000 IOPC=1 初始化GPIOC
	GPIOC->CRH = 0x00100000;  //0b 0000 0000 0001 0000 0000 0000 0000 0000 CNF13=0b00,MODE13=Ob01
	GPIOC->CRH = ~0xFF1FFFFF;//0b 1111 1111 0001 1111 1111 1111 1111 1111 用作掩码
	*/
