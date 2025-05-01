#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "LED.h"
#include "CountSensor.h"
#include "Encoder.h"
//#include "Timer.h"
#include "PWM.h"
uint16_t Num;
uint16_t i;			//定义for循环的变量
int main(void)
{


	
	OLED_Init();
	OLED_ShowString(2,3,"Booting.....");
	Delay_ms(500);
	OLED_Clear();
	LED_Init();
	//TimerInit();
	PWM_Init();
	OLED_Clear();
	
    PWM_SetFrequency(1);  // 1kHz 频率
    PWM_SetDutyCycle(10.0f); // 30% 占空比
	
	OLED_ShowString(1, 6, "PWM");	//1行1列显示字符串Count
	while (1){
		for (i = 0; i <= 3000; i++){
		PWM_SetFrequency(i);  // 切换到 2kHz
			//PWM_SetCompare1(i);			//依次将定时器的CCR寄存器设置为0~100，PWM占空比逐渐增大，LED逐渐变亮
			Delay_ms(1);				//延时1ms
			OLED_ShowString(2, 1, "HIGH");	
			OLED_ShowNum(2, 7,i, 5);
		}
		for (i = 0; i <= 3000; i++){
		PWM_SetFrequency(3000-i);  // 切换到 2kHz
			//PWM_SetCompare1(100-i);	//依次将定时器的CCR寄存器设置为100~0，PWM占空比逐渐减小，LED逐渐变暗
			Delay_ms(1);				//延时1ms
			OLED_ShowString(2, 1, "LOW ");	
			OLED_ShowNum(2, 7,3000-i, 5);
		}
	
	}
		
		
		//执行一次，注释while(1)可用
		Delay_s(1);
		OLED_Clear();
		TIM_DeInit(TIM2);
		OLED_ShowString(2,5,"THE END");  


}
