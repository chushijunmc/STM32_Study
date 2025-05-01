//Filename: exti.c

#include "includes.h"

void EXTIKeyInit(void)
{
    // 配置EXTI映射
    AFIO->EXTICR[0] &= ~(0xF << 4);  // EXTI1 -> PA1
		AFIO->EXTICR[0] |= (0x0 << 4);   // 明确映射到PA1

	    // 配置下降沿触发
    EXTI->FTSR |= (1uL<<1) ;
	  EXTI->RTSR |= (1uL<<1);      
    EXTI->IMR |= (1uL<<1);

	
	NVIC_EnableIRQ(EXTI1_IRQn);  //Open EXTI1

	NVIC_SetPriority(EXTI1_IRQn,1);

}

// EXTI0中断服务函数
void EXTI1_IRQHandler(void) {
    if (EXTI->PR & (1<<1)) {
        // 检测PA1当前状态决定LED状态
        if (GPIOA->IDR & (1<<1)) {
              LED(1,LED_OFF);  // 按键释放→灭
        } else {
            LED(1,LED_ON);   // 按键按下→亮
        }
        EXTI->PR = (1<<1);          // 清除中断标志
    }
}
