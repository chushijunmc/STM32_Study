#include "includes.h"

void KEYInit(void)
{
	GPIO_InitTypeDef g;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO,ENABLE);
	
	g.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7 ; //KEY0,KEY1,KEY2,KEY3,KEY4分别对于PA1,PA4,PA5,PA6,PA7
	g.GPIO_Mode = GPIO_Mode_IPU;  //上拉输入模式
	g.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_Init(GPIOA,&g);
	
	//GPIO_SetBits(GPIOA,GPIO_Pin_1);
}
