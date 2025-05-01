#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f10x.h"

#define BEEP_GPIO_PIN              GPIO_Pin_9
#define BEEP_GPIO_PORT             GPIOB
#define BEEP_GPIO_CLK              RCC_APB2Periph_GPIOB

#define BEEP_TOGGLE    {BEEP_GPIO_PORT->ODR ^= BEEP_GPIO_PIN;}//蜂鸣器状态翻转

#define BEEP_ON         GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);//蜂鸣器关闭
#define BEEP_OFF        GPIO_SetBits(BEEP_GPIO_PORT,BEEP_GPIO_PIN);//蜂鸣器打开

void BEEP_GPIO_Config(void); //蜂鸣器初始化函数

#endif /*__BEEP_H */