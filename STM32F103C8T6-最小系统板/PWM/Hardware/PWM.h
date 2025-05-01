#ifndef _PWM_H
#define _PWN_H

void PWM_Init(void);
void PWM_SetCompare1(uint16_t Compare);
void PWM_SetFrequency(uint32_t freqHz);
void PWM_SetDutyCycle(float dutyCycle);
#endif
