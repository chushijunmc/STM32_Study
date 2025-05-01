#include "includes.h"
#include "globalval.h"
#include "systick.h"


void TIM3_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    
    // 定时器配置为500ms周期
    TIM_InitStructure.TIM_Prescaler = 7200 - 1;     // 72MHz/7200 = 10kHz
    TIM_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_InitStructure.TIM_Period = 5000 - 1;        // 10kHz/5000 = 2Hz
    TIM_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM3, &TIM_InitStructure);
    
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0E;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0E;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_Cmd(TIM3, DISABLE);  // 初始不启动
}

// TIM4初始化（蜂鸣器闪烁）
void TIM4_Init(void)
{
    TIM_TimeBaseInitTypeDef t;
    NVIC_InitTypeDef n;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    
    t.TIM_Prescaler = 7200 - 1;      // 10kHz
    t.TIM_Period = 2000 - 1;         // 200ms
    t.TIM_CounterMode = TIM_CounterMode_Up;
    t.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &t);
    
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    
    n.NVIC_IRQChannel = TIM4_IRQn;
    n.NVIC_IRQChannelPreemptionPriority = 0x0D;
    n.NVIC_IRQChannelSubPriority = 0x0D;
    n.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&n);
    
    TIM_Cmd(TIM4, DISABLE);
}



// 定时器3中断服务函数（用于LED闪烁）
void TIM3_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
    {
        LED_Turn();  // 每次中断切换LED状态
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}

void TIM4_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM4, TIM_IT_Update))
    {
        BEEP_Turn();
        TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
    }
}

// 定时器重新配置函数
void TIM3_SpeedConfig(LedSpeedMode mode)
{
    TIM_TimeBaseInitTypeDef t;
    
    // 保持时钟源不变
    uint16_t prescaler = 7200 - 1; // 10kHz
    
    switch(mode) {
        case LED_SPEED_LOW:   // 1Hz (1000ms)
            t.TIM_Period = 10000 - 1;
            break;
        case LED_SPEED_MID:  // 2Hz (500ms)
            t.TIM_Period = 5000 - 1;
            break;
        case LED_SPEED_HIGH: // 5Hz (200ms)
            t.TIM_Period = 2000 - 1;
            break;
        default:
            return;
    }
    
    t.TIM_Prescaler = prescaler;
    t.TIM_CounterMode = TIM_CounterMode_Up;
    t.TIM_ClockDivision = TIM_CKD_DIV1;
    
    TIM_TimeBaseInit(TIM3, &t);
    TIM_SetCounter(TIM3, 0); // 重置计数器
}

void TIM4_SpeedConfig(BeepSpeedMode mode)
{
    TIM_TimeBaseInitTypeDef t;
    
    uint16_t prescaler = 7200 - 1; // 保持与TIM3相同的时钟源
    
    switch(mode) {
        case BEEP_SPEED_LOW:  // 1Hz
            t.TIM_Period = 10000 - 1;
            break;
        case BEEP_SPEED_MID:  // 4Hz
            t.TIM_Period = 2500 - 1;
            break;
        case BEEP_SPEED_HIGH: // 10Hz
            t.TIM_Period = 1000 - 1;
            break;
        default:
            return;
    }
    
    t.TIM_Prescaler = prescaler;
    t.TIM_CounterMode = TIM_CounterMode_Up;
    t.TIM_ClockDivision = TIM_CKD_DIV1;
    
    TIM_TimeBaseInit(TIM4, &t);
    TIM_SetCounter(TIM4, 0);
}
