#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

//KEY0~KEY4的GPIO端口和时钟
#define KEY0_4_GPIO_PORT    GPIOA
#define KEY0_4_GPIO_CLK     RCC_APB2Periph_GPIOA

//KEY0
#define KEY0_GPIO_PIN    GPIO_Pin_1
//KEY1
#define KEY1_GPIO_PIN    GPIO_Pin_4
//KEY2
#define KEY2_GPIO_PIN    GPIO_Pin_5
//KEY3
#define KEY3_GPIO_PIN    GPIO_Pin_6
//KEY4
#define KEY4_GPIO_PIN    GPIO_Pin_7

#define KEY0    GPIO_ReadInputDataBit(KEY0_4_GPIO_PORT, KEY0_GPIO_PIN)//读取KEY0
#define KEY1    GPIO_ReadInputDataBit(KEY0_4_GPIO_PORT, KEY1_GPIO_PIN)//读取KEY1
#define KEY2    GPIO_ReadInputDataBit(KEY0_4_GPIO_PORT, KEY2_GPIO_PIN)//读取KEY2
#define KEY3    GPIO_ReadInputDataBit(KEY0_4_GPIO_PORT, KEY3_GPIO_PIN)//读取KEY3
#define KEY4    GPIO_ReadInputDataBit(KEY0_4_GPIO_PORT, KEY4_GPIO_PIN)//读取KEY4

#define KEY0_PRES 1	//KEY0按下
#define KEY1_PRES	2	//KEY1按下
#define KEY2_PRES	3	//KEY2按下
#define KEY3_PRES	4	//KEY3按下
#define KEY4_PRES	5	//KEY4按下

void KEY_GPIO_Config(void);
u8 KEY_Scan(u8);  	//按键扫描函数				

#endif /* __KEY_H */
