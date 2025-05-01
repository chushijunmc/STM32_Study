#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "CountSensor.h"
#include "Encoder.h"
#include "Timer.h"
extern uint16_t Num;

int main(void)
{
	OLED_Init();
	OLED_ShowString(2,3,"Booting.....");
	Delay_ms(500);
	OLED_Clear();
	LED_Init();
	Timer_Init();
	/*
	CountSensor_Init();
	Encoder_Init();*/
	OLED_Clear();
	
	/*显示静态字符串*/
	
	
	OLED_ShowString(2, 1, "Count:");	//1行1列显示字符串Count
		OLED_ShowString(3, 1, "CNT:");	//1行1列显示字符串Count
	while (1)
	{
		OLED_ShowNum(2, 7,Num, 5);
		OLED_ShowNum(3, 7,Timer_GetCounter(), 5);

		//时基单元需要预分频就可以遮挡几下刷新
	}
}
