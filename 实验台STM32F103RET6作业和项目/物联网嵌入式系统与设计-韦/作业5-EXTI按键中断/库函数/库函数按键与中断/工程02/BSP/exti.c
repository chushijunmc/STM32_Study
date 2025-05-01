#include "includes.h"


EXTI_InitTypeDef EXTI_InitStructure;

void exit_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;

    /* 1. 使能GPIOE和AFIO时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	    /* 2. 用KEY2即PA5，配置PA5为上拉输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 3. 将PA1映射到EXTI9 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);

    /* 4. 配置EXTI9为上下沿触发 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling; // 上下沿触发
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* 5. 配置NVIC（优先级和中断使能） */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn; // EXTI9~5共享中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F; // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
		    /* 5. 配置NVIC（优先级和中断使能） */
   /* NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; // EXTI4中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F; // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);*/
}

unsigned char EXIT_Flag = 0;

/*
void EXTI4_IRQHandler(void)
{
      if (EXTI_GetITStatus(EXTI_Line9)==SET) // 检查是否是EXTI9触发
    {
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)
			{
			Delay_ms(300);
			LED(0,LED_OFF);
			LED(1,LED_OFF);
			LED(2,LED_OFF);
			BEEP(BEEP_ON);
			}else{
			Delay_ms(300);
			LED(0,LED_ON);
				LED(1,LED_ON);
				LED(2,LED_ON);
				BEEP(BEEP_OFF);
			}

   
    }
		EXTI_ClearITPendingBit(EXTI_Line5); // 清除中断标志
}
*/


void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line5)==SET) // 检查是否是EXTI9触发
    {
			if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0)
			{
			Delay_ms(300);
			LED(0,LED_OFF);
			LED(1,LED_OFF);
			LED(2,LED_OFF);
			BEEP(BEEP_OFF);
			EXTI_ClearITPendingBit(EXTI_Line5); // 清除中断标志
			}else{
			Delay_ms(300);
			LED(0,LED_ON);
				LED(1,LED_ON);
				LED(2,LED_ON);
				BEEP(BEEP_ON);
				EXTI_ClearITPendingBit(EXTI_Line5); // 清除中断标志
			}

   
    }
		
}
