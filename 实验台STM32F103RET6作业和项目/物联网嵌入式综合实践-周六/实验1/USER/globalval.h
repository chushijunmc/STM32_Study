/* globalval.h */
#ifndef __GLOBALVAL_H
#define __GLOBALVAL_H

#include "stm32f10x.h"

typedef enum {
    LED_SPEED_LOW = 0,
    LED_SPEED_MID,
    LED_SPEED_HIGH,
    LED_SPEED_MAX
} LedSpeedMode;

typedef enum {
    BEEP_SPEED_LOW = 0,
    BEEP_SPEED_MID,
    BEEP_SPEED_HIGH,
    BEEP_SPEED_MAX
} BeepSpeedMode;

extern volatile BeepSpeedMode beepSpeed;
extern volatile uint8_t beepSpeedChangeFlag;
extern volatile uint8_t systemShutdownFlag;
// LED控制相关
extern volatile uint32_t keyPressTime;
extern volatile uint8_t keyActionFlag;
extern volatile uint8_t blinkEnable;

// 蜂鸣器控制相关
extern volatile uint32_t beepPressTime;
extern volatile uint8_t beepActionFlag;
extern volatile uint8_t beepBlinkEnable;

//LED调速有关
extern volatile LedSpeedMode ledSpeed;
extern volatile uint8_t speedChangeFlag;

//蜂鸣器调速有关
extern volatile BeepSpeedMode beepSpeed;
extern volatile uint8_t beepSpeedChangeFlag;

#endif