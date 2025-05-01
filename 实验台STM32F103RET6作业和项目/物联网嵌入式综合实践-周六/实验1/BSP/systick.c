/* systick.c */
#include "systick.h"
#include "stm32f10x.h"

static volatile uint32_t sysTick = 0;

uint32_t GetSysTime(void) 
{
    return sysTick; // 返回毫秒数
}

void SysTick_Handler(void) 
{
    sysTick++;
}

void SysTick_Init(void)
{
    SysTick_Config(SystemCoreClock / 1000); // 1ms中断
    NVIC_SetPriority(SysTick_IRQn, 0);      // 最高优先级
}