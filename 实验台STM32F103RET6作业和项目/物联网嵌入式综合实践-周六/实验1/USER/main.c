//Filename: main.c
/**
实训台节点
*/
#include "includes.h"
#include "exit.h"
#include "globalval.h"
#include "systick.h"
#include "led.h"

extern volatile uint32_t keyPressTime;
extern volatile uint8_t keyActionFlag;  // 0-无 1-单击 2-双击
extern volatile uint8_t blinkEnable;    // 闪烁使能标志

void Delay(Int32U);

// 主循环中添加处理
int main(void)
{
	
    SystemInit();
    exit_Init();
		LEDInit();
		BEEPInit();
    SysTick_Init();  // 初始化系统时钟
		Lcd_Init();				//初始化LCD
	BACK_COLOR=BLACK;		//背景为黑色
	POINT_COLOR=WHITE;	//画笔为黄色
	LCD_Clear(BLACK);
	LCD_Show_Chinese16x16(120,20,"实验"); //显示 中文字符串
	LCD_ShowString(160,20,"1");
	//LCD_ShowString(80,80,"This is a test!");//显示英文字符串
	LCD_Show_Chinese16x16(80,80,"初始化完成！");
		BEEP(BEEP_OFF);

    while(1)
    {
         // 处理LED控制
        if(keyActionFlag)
        {
            if(keyActionFlag == 1)       // 单击切换
            {
                blinkEnable = 0;
                TIM_Cmd(TIM3, DISABLE);
                LED_Turn();
							LCD_Show_Chinese16x16(80,200,"　　　　　　　　　　　　　　");
            }
            else if(keyActionFlag == 2)  // 双击闪烁
            {
                blinkEnable = 1;
                TIM_Cmd(TIM3, ENABLE);
							LCD_Show_Chinese16x16(80,200,"灯频率：默认");
            }
            keyActionFlag = 0;
        }
        
        // 处理蜂鸣器控制
        if(beepActionFlag)
        {
            if(beepActionFlag == 1)      // 单击切换
            {
                beepBlinkEnable = 0;
                TIM_Cmd(TIM4, DISABLE);
                BEEP_Turn();
							LCD_Show_Chinese16x16(80,220,"　　　　　　　　　　　　　　");
            }
            else if(beepActionFlag == 2) // 双击闪烁
            {
                beepBlinkEnable = 1;
                TIM_Cmd(TIM4, ENABLE);
							LCD_Show_Chinese16x16(80,220,"声频率：默认");
            }
            beepActionFlag = 0;
        }
				
				 // LED频率处理
        if(speedChangeFlag) {
            TIM3_SpeedConfig(ledSpeed);
            // 状态指示（可选）
            LED(0, (ledSpeed==0)?LED_ON:LED_OFF);
            LED(1, (ledSpeed==1)?LED_ON:LED_OFF);
            LED(2, (ledSpeed==2)?LED_ON:LED_OFF);
            speedChangeFlag = 0;
					if(ledSpeed==0){
						LCD_Show_Chinese16x16(80,200,"灯频率：低　");
					}else if(ledSpeed==1){
						LCD_Show_Chinese16x16(80,200,"灯频率：中　");
					}else if(ledSpeed==2){
						LCD_Show_Chinese16x16(80,200,"灯频率：高　");
					}
        }
        
        // 蜂鸣器频率处理
        if(beepSpeedChangeFlag) {
            TIM4_SpeedConfig(beepSpeed);
            // 状态指示（可选）
            BEEP((beepSpeed==0)?BEEP_OFF:BEEP_ON);
            beepSpeedChangeFlag = 0;
					if(beepSpeed==0){
						LCD_Show_Chinese16x16(80,220,"声频率：低　");
					}else if(beepSpeed==1){
						LCD_Show_Chinese16x16(80,220,"声频率：中　");
					}else if(beepSpeed==2){
						LCD_Show_Chinese16x16(80,220,"声频率：高　");
					}
        }
				
				 // 紧急停止处理（最高优先级）
        if(systemShutdownFlag) {
            // 关闭所有定时器
            TIM_Cmd(TIM3, DISABLE);
            TIM_Cmd(TIM4, DISABLE);
            
            // 关闭所有LED
            LED(0, LED_OFF);
            LED(1, LED_OFF);
            LED(2, LED_OFF);
            
            // 关闭蜂鸣器
            BEEP(BEEP_OFF);
            
            // 重置所有状态
            blinkEnable = 0;
            beepBlinkEnable = 0;
            systemShutdownFlag = 0;
					
						LCD_Clear(BLACK);
						LCD_Show_Chinese16x16(120,20,"实验"); //显示 中文字符串
						LCD_ShowString(160,20,"1");
						LCD_Show_Chinese16x16(80,80,"初始化完成！");

        }
    }
}

void Delay(Int32U u)
{
	volatile Int32U i,j;
	for(i=0;i<u;i++)
		for(j=0;j<12000;j++);
}

