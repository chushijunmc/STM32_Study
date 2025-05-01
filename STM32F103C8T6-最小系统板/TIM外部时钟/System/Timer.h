#ifndef TIMER_H
#define TIMER_H


#include "stm32f10x.h"                  // Device header


//定时器初始化
 void Timer_Init();
 uint16_t Timer_GetCounter();
 
 #endif