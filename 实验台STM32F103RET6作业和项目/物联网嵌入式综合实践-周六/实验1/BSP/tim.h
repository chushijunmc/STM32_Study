#ifndef _TIM_H
#define _TIM_H

#include "globalval.h"


void TIM3_IRQHandler(void);
void TIM3_Init(void);
void TIM4_Init(void);
void TIM3_SpeedConfig(LedSpeedMode mode);
void TIM4_SpeedConfig(BeepSpeedMode mode);
#endif
