/* systick.h */
#ifndef __SYSTICK_H
#define __SYSTICK_H
#include <stdint.h>

uint32_t GetSysTime(void);
void SysTick_Init(void);

#endif