#include "stm32f10x.h" 
#include "usart.h"

void Delay(u32 count);

int main(void)
{
	
	Usart2_Init(9600); //串口2初始化函数
	USART2TxStr("串口2通信实验！\r\n");
	Uart4_Init(14400);
	UART4TxStr("串口4通信实验！\r\n");
	while(1)
	{
		USART2TxStr("寻卡失败\r\n");
	}	 
}
 
void Delay(u32 count)  //简单的延时函数
{
   u32 i=0;
   for(;i<count;i++);
}
