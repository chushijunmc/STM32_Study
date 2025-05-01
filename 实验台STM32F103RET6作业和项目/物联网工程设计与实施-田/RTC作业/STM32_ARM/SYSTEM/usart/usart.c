#include "usart.h"
#include "stm32f10x.h"

void Usart2_Init(u32 bound) {
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 1. 打开时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   // GPIOA 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);  // USART2 时钟

    // 2. 配置 PA2（TX）为复用推挽输出，PA3（RX）为浮空输入
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;               // TX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;         // 复用推挽
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;               // RX
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;   // 浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 3. 初始化 USART2
    USART_InitStructure.USART_BaudRate = bound;                                // 波特率
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                // 8位数据
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                     // 1位停止位
    USART_InitStructure.USART_Parity = USART_Parity_No;                         // 无奇偶校验
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; // 无硬件流控
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;            // 发送+接收
    USART_Init(USART2, &USART_InitStructure);

    // 4. 开启接收中断（如果不接收数据可以注释）
    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 5. 使能 USART2
    USART_Cmd(USART2, ENABLE);
}

// 发送单个字符
void USART2TxChar(int ch) {
    USART_SendData(USART2, (u8)ch);
    while (USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
}

// 发送字符串
void USART2TxStr(char *pt) {
    while (*pt) {
        USART2TxChar(*pt++);
    }
}
