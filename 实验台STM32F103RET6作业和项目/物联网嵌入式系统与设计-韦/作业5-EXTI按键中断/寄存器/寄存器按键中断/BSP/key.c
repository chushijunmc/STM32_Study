//Filename: key.c

#include "includes.h"

void KEYInit(void)
{
		RCC->APB2ENR |= (1uL<<2);     //使能GPIOA时钟
		RCC->APB2ENR |= (1uL<<0);     //AFIO Enable
		   
	  
    GPIOA->CRL &= ~(0xF << 4);  // 清除PA1配置位
    GPIOA->CRL |= (0x8 << 4);   // 输入模式(0b1000)	
		GPIOA->ODR |= (1uL << 1);
}


