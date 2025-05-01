//Filename: led.c

#include "includes.h"
void LED(Int08U w, LEDState s);

//初始化LED灯
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
	LED(2,LED_OFF);
}


//指定LED灯切换状态Int08U w代表第一第二第三，LEDState s代表开启关闭LED，LED_ON和LED_OFF在其他变量中有枚举代表开启关闭
void LED(Int08U w, LEDState s)
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
//三个LED灯同时亮灭切换
void LED_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15) == 0)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);					//则设置PA1引脚为高电平
		LCD_Show_Chinese16x16(80,160,"灯：关");
	}
	else													//否则，即当前引脚输出高电平
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15);					//则设置PA1引脚为低电平
		LCD_Show_Chinese16x16(80,160,"灯：开");
	}
}

