#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "rtc.h"


/************************************************
 //STM32F103ZE核心板
 
 串口实验 
	本实验,STM32通过串口1和上位机对话，STM32在收到上位机发过来的字符串(以回车换
	行结束)后，	原原本本的返回给上位机。下载后，D0闪烁，提示程序在运行，同时每
	隔一定时间，通过串口1输出一段信息到电脑
************************************************/


 int main(void)
 {		
 	u16 t;  
	u16 len;	
	u16 times=0;
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	uart_init(115200);	 //串口初始化为115200
	 printf("正在准备初始化 串口...... ");
	 printf("完成!!!\r\n"); 
 	LED_Init();			     //LED端口初始化
	KEY_Init();          //初始化与按键连接的硬件接口
	RTC_Init();
	 
	
	
		delay_ms(100);
	 printf("正在准备初始化系统时钟......  ");
	 SystemInit();  
	 printf("完成!!!\r\n"); 
	 printf("正在准备初始化 RTC...... ");
   while(RTC_Init()) { // RTC初始化，一定要初始化成功
        printf("失败!\r\n");  
        delay_ms(800);
        printf("检查RTC是否损坏\r\n");  
    }
    printf("完成!!!\r\n");           
	 
	 	RTC_Set(2025,4,16,12,00,00);  //设置时间	
 	while(1)
	{
		 RTC_Get(); // 更新日历结构体
        // 通过串口输出时间信息
        printf("Date: %04d-%02d-%02d Time: %02d:%02d:%02d Week:%d\r\n", 
               calendar.w_year, calendar.w_month, calendar.w_date,
               calendar.hour, calendar.min, calendar.sec, calendar.week);
        delay_ms(1000); // 延时1秒
		
			if(times%5000==0)
			{
				printf("\r\n串口实验 显示时间日期\r\n");
			}
			  
		}
		 
 }

