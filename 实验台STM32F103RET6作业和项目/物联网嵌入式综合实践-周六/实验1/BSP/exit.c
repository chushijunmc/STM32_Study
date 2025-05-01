#include "includes.h"


EXTI_InitTypeDef EXTI_InitStructure;

void exit_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

    NVIC_InitTypeDef NVIC_InitStructure;

    /* 1. 使能GPIOE和AFIO时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

	    /* 2. 配置PC9为上拉输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_Init(GPIOC, &GPIO_InitStructure);
    /* 2. 配置PE9为上拉输入 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* 3. 将PE9映射到EXTI9 */
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource9);

    /* 4. 配置EXTI9为上下沿触发 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line9|EXTI_Line4;
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
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn; // EXTI9~5共享中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F; // 抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F; // 子优先级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
}

unsigned char EXIT_Flag = 0;


void EXTI4_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) // 检查是否是EXTI9触发
    {
			EXTI_ClearITPendingBit(EXTI_Line9); // 清除中断标志
			
			//EXIT_Flag++;
			if((EXIT_Flag++)%2){
				LED(0,LED_OFF);
				LED(1,LED_OFF);
			}else{
				LED(0,LED_ON);
				LED(1,LED_ON);
			}
        

        
    }
}

void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line9) != RESET) // 检查是否是EXTI9触发
    {
			EXTI_ClearITPendingBit(EXTI_Line9); // 清除中断标志
			
			//EXIT_Flag++;
			if((EXIT_Flag++)%2){
				LED(0,LED_OFF);
				LED(1,LED_OFF);
			}else{
				LED(0,LED_ON);
				LED(1,LED_ON);
			}
        

        
    }
}
