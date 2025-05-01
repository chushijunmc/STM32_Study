#include "stm32f10x.h"
#include "delay.h"

 /*void Delay(u32 count)
 {
   u32 i=0;
   for(;i<count;i++);
 }*/
 int main(void)
 {	
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);    //使能GPIOC端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;			    //PC13|PC14|PC15 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
  GPIO_Init(GPIOC, &GPIO_InitStructure);			     //初始化GPIOC
  	
  while(1)
	{
		GPIO_SetBits(GPIOC,GPIO_Pin_13);					//设置端口位
		GPIO_SetBits(GPIOC,GPIO_Pin_14);	
		GPIO_SetBits(GPIOC,GPIO_Pin_15);
		delay_ms(300);
		GPIO_ResetBits(GPIOC,GPIO_Pin_13);					//设置端口位
		GPIO_ResetBits(GPIOC,GPIO_Pin_14);	
		GPIO_ResetBits(GPIOC,GPIO_Pin_15);
		delay_ms(300);
	}
}
