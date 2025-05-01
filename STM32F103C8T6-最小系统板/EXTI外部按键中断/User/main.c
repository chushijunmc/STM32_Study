#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "CountSensor.h"
#include "Encoder.h"

int16_t Num;

int main(void)
{
	OLED_Init();
	OLED_ShowString(2,3,"Booting.....");
	Delay_ms(500);
	OLED_Clear();
	LED_Init();
	CountSensor_Init();
	Encoder_Init();
	OLED_Clear();
	
	/*显示静态字符串*/
	
	
	OLED_ShowString(2, 1, "Count:");	//1行1列显示字符串Count
	
	while (1)
	{
		OLED_ShowNum(2, 7, CountSensor_Get(), 5);		//OLED不断刷新显示CountSensor_Get的返回值
		OLED_ShowSignedNum(3, 7, Num+=Encoder_Get(), 5);		//OLED不断刷新显示CountSensor_Get的返回值
	}
}
