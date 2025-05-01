#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 

extern u16 USART1_RX_STA;         		//接收状态标记
extern u16 USART2_RX_STA;         		//接收状态标记
extern u16 USART3_RX_STA;         		//接收状态标记
extern u16 UART4_RX_STA;         		//接收状态标记
extern u16 UART5_RX_STA;         		//接收状态标记

extern char USART1_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
extern char USART2_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern unsigned char USART3_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.
extern unsigned char UART4_RX_BUF[USART_REC_LEN];
extern char UART5_RX_BUF[USART_REC_LEN];

extern unsigned char Flag_Usart1_Receive;
extern unsigned char Flag_Usart2_Receive;
extern unsigned char Flag_Usart3_Receive;
extern unsigned char Flag_Uart4_Receive;
extern unsigned char Flag_Uart5_Receive;

void Usart1_Init(u32 bound);//串口1初始化函数
void USART1TxChar(char ch);
void USART1TxData(unsigned char *pt);
void USART1TxData_hex(unsigned char *pt,unsigned char len);
void USART1TxStr(char *pt);
void CLR_Buf1(void);     //清除串口1接收缓存

void Usart2_Init(u32 bound); //串口2初始化函数
void USART2TxChar(int ch) ; 
void USART2TxData(unsigned char *pt);
void USART2TxData_hex(unsigned char *pt,unsigned char len);
void USART2TxStr(char *pt);
void CLR_Buf2(void);     //清除串口2接收缓存

void Usart3_Init(u32 bound); //串口3初始化函数
void USART3TxChar(int ch); 
void USART3TxData(unsigned char *pt);
void USART3TxData_hex(unsigned char *pt,unsigned char len);
void USART3TxStr(char *);
void CLR_Buf3(void);     //清除串口3接收缓存

void Uart4_Init(u32 bound);//串口标准接口初始化
void UART4TxChar(int ch); 
void UART4TxData(unsigned char *pt);
void UART4TxData_hex(unsigned char *pt,unsigned char len);
void UART4TxStr(char *pt);
void CLR_Buf4(void);     //清除串口接收缓存

void Uart5_Init(u32 bound);//串口标准接口初始化
void UART5TxChar(int ch); 
void UART5TxData(unsigned char *pt);
void UART5TxData_hex(unsigned char *pt,unsigned char len);
void UART5TxStr(char *pt);
void CLR_Buf5(void);     //清除串口接收缓存

#endif /* __USART_H */
