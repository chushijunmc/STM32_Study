#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

// 串口2初始化
void Usart2_Init(uint32_t bound);

// 串口2发送单个字符
void USART2TxChar(int ch);

// 串口2发送字符串
void USART2TxStr(char *pt);

#endif
