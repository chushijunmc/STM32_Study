#include "stm32f10x.h"
#include "rtc.h"
#include "datetime.h"
#include "usart.h"
#include <stdio.h>

void Delay(u32 count);

DateTime current_time = {
    .year = 2025,
    .month = 4,
    .day = 15,
    .hour = 12,
    .minute = 0,
    .second = 0,
    .weekday = 2  // 可通过 calculate_weekday 自动算
};

int main(void)
{
	BEEP_GPIO_Config();
	Delay(100);
	GPIO_ResetBits(GPIOB,GPIO_Pin_9);//蜂鸣器关闭
	Delay(100);
	/*
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);//蜂鸣器关闭
		GPIO_SetBits(GPIOB,GPIO_Pin_9);//蜂鸣器打开
	*/
	Usart2_Init(9600); 
	USART2TxStr(" 串口 2 初始化完成 ! \r\n");
	USART2TxStr("正在准备初始化系统时钟 ....... ");
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//蜂鸣器打开
		Delay(100);
	SystemInit();          // 系统时钟初始化

	GPIO_ResetBits(GPIOB,GPIO_Pin_9);//蜂鸣器关闭
		USART2TxStr("完成 ! \r \n");
    Usart2_Init(9600);     // 初始化串口2，波特率9600
	USART2TxStr("正在准备初始化 RTC...... ");
	GPIO_SetBits(GPIOB,GPIO_Pin_9);//蜂鸣器打开
		Delay(100);
   while(RTC_Init()) { // RTC初始化，一定要初始化成功
        printf("RTC ERROR!\r\n");  
        Delay(800);
        printf("RTC Trying...\r\n");  
    }
    printf("RTC OK!!!\r\n");           // RTC初始
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);//蜂鸣器关闭
	USART2TxStr("完成 ! ");
	
	Usart2_Init(9600); //串口2初始化函数
	USART2TxStr("串 口 2 通 信 实 验 ! \r\n");
	//Uart4_Init(14400);
	//UART4TxStr("串口4通信实验！\r\n");
	    while (1) {
			GPIO_SetBits(GPIOB,GPIO_Pin_9);//蜂鸣器打开
			Delay(100);
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);//蜂鸣器关闭
			Delay(100);

				/*
        RTC_GetDateTime(&current_time);  // 获取当前时间

        // 打印当前时间（通过USART2）
        printf("%04u-%02u-%02u %02u:%02u:%02u Weekday:%u\r\n",
               current_time.year, current_time.month, current_time.day,
               current_time.hour, current_time.minute, current_time.second,
               current_time.weekday);

        datetime_increment(&current_time);  // 模拟时间加1秒
        RTC_SetDateTime(&current_time);     // 更新RTC时间

*/
    }
}
 


void Delay(u32 count)  //简单的延时函数
{
   u32 i=0;
   for(;i<count;i++);
}

// 重定向 printf 到 USART2
int fputc(int ch, FILE *f) {
    USART2TxChar(ch);
    return ch;
}
