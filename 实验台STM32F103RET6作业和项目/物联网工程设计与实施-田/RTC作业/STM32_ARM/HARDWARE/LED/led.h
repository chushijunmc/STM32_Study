#ifndef __LED_H
#define __LED_H

#include "stm32f10x.h"

//LEDºìÉ«
#define LED_R_GPIO_PIN              GPIO_Pin_13
#define LED_R_GPIO_PORT             GPIOC
#define LED_R_GPIO_CLK              RCC_APB2Periph_GPIOC

//LEDÂÌÉ«
#define LED_G_GPIO_PIN              GPIO_Pin_14
#define LED_G_GPIO_PORT             GPIOC
#define LED_G_GPIO_CLK              RCC_APB2Periph_GPIOC

//LED»ÆÉ«
#define LED_Y_GPIO_PIN              GPIO_Pin_15
#define LED_Y_GPIO_PORT             GPIOC
#define LED_Y_GPIO_CLK              RCC_APB2Periph_GPIOC

#define LED_R_ON              GPIO_ResetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);//ÁÁ
#define LED_R_OFF             GPIO_SetBits(LED_R_GPIO_PORT,LED_R_GPIO_PIN);//Ãð

#define LED_G_ON              GPIO_ResetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);//ÁÁ
#define LED_G_OFF             GPIO_SetBits(LED_G_GPIO_PORT,LED_G_GPIO_PIN);//Ãð

#define LED_Y_ON              GPIO_ResetBits(LED_Y_GPIO_PORT,LED_Y_GPIO_PIN);//ÁÁ
#define LED_Y_OFF             GPIO_SetBits(LED_Y_GPIO_PORT,LED_Y_GPIO_PIN);//Ãð


#define  LED_R_TOGGLE  {LED_R_GPIO_PORT->ODR ^= LED_R_GPIO_PIN;}//ºìÉ«LED×´Ì¬·­×ª
#define  LED_G_TOGGLE  {LED_G_GPIO_PORT->ODR ^= LED_G_GPIO_PIN;}//ÂÌÉ«LED×´Ì¬·­×ª
#define  LED_Y_TOGGLE  {LED_Y_GPIO_PORT->ODR ^= LED_Y_GPIO_PIN;}//»ÆÉ«LED×´Ì¬·­×ª

void LED_GPIO_Config(void); //LED³õÊ¼»¯º¯Êý

#endif /* __LED_H */