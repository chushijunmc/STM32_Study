#include "beep.h"

void BEEP_GPIO_Config(void)
{
	/*定义一个 GPIO_InitTypeDef 类型的结构体*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/*开启蜂鸣器相关的 GPIO 外设时钟*/
	RCC_APB2PeriphClockCmd(BEEP_GPIO_CLK, ENABLE);
	
	/*选择要控制的 GPIO 引脚*/
	GPIO_InitStruct.GPIO_Pin = BEEP_GPIO_PIN;	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;	
	/*设置引脚速率为 50MHz */
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	/*调用库函数，初始化 GPIO*/
	GPIO_Init(BEEP_GPIO_PORT, &GPIO_InitStruct);

}