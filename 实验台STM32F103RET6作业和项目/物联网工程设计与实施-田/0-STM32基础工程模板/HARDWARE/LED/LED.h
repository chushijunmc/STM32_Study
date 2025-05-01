#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

//LED??
#define LED_R_GPIO_PIN              GPIO_Pin_13
#define LED_R_GPIO_PORT             GPIOC
#define LED_R_GPIO_CLK              RCC_APB2Periph_GPIOC

//LED??
#define LED_G_GPIO_PIN              GPIO_Pin_14
#define LED_G_GPIO_PORT             GPIOC
#define LED_G_GPIO_CLK              RCC_APB2Periph_GPIOC

//LED??
#define LED_Y_GPIO_PIN              GPIO_Pin_15
#define LED_Y_GPIO_PORT             GPIOC
#define LED_Y_GPIO_CLK              RCC_APB2Periph_GPIOC

#define LED_R_ON              GPIO_ResetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);//?
#define LED_R_OFF             GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);//?

#define LED_G_ON              GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);//?
#define LED_G_OFF             GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);//?

#define LED_Y_ON              GPIO_ResetBits(LED_Y_GPIO_PORT,LED_Y_GPIO_PIN);//?
#define LED_Y_OFF             GPIO_SetBits(LED_Y_GPIO_PORT,LED_Y_GPIO_PIN);//?

void LED_GPIO_Config(void);

#endif /* __LED_H */
