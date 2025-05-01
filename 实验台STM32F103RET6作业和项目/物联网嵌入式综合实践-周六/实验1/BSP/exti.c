#include "includes.h"
#include "globalval.h"
#include "systick.h"  // 新增包含


// 添加全局变量LED控制变量定义
volatile uint32_t keyPressTime = 0;
volatile uint8_t keyActionFlag = 0;  // 0-无 1-单击 2-双击
volatile uint8_t blinkEnable = 0;    // 闪烁使能标志
// 蜂鸣器控制变量定义
volatile uint32_t beepPressTime = 0;
volatile uint8_t beepActionFlag = 0;
volatile uint8_t beepBlinkEnable = 0;
//LED调速变量定义
volatile LedSpeedMode ledSpeed = LED_SPEED_LOW;
volatile uint8_t speedChangeFlag = 0;
//蜂鸣器调速变量定义
volatile BeepSpeedMode beepSpeed = BEEP_SPEED_LOW;
volatile uint8_t beepSpeedChangeFlag = 0;
//关闭蜂鸣器变量定义
volatile uint8_t systemShutdownFlag = 0;

EXTI_InitTypeDef EXTI_InitStructure;

// 定时器3初始化（用于LED闪烁）

void exit_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 初始化KEY0(PA1)和KEY2(PA4)
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    // 配置PA1(KEY0)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置PA4(KEY2)
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // 配置KEY0中断(PA1)
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource1);
    EXTI_InitStructure.EXTI_Line = EXTI_Line1;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    // 配置KEY2中断(PA4)
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource4);
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    EXTI_Init(&EXTI_InitStructure);

    // 配置中断优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    // KEY0中断通道
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    // KEY2中断通道
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    NVIC_Init(&NVIC_InitStructure);

    /* PA5配置 */
    GPIO_InitTypeDef GPIO_InitStruct;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);
    
    // PA5配置为上拉输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct);

    // 配置EXTI线5
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource5);
    EXTI_InitStructure.EXTI_Line = EXTI_Line5;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTI_Init(&EXTI_InitStructure);

    // 配置中断优先级
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0E;
    NVIC_Init(&NVIC_InitStructure);

		/* PA6配置 */
    GPIO_InitTypeDef GPIO_InitStruct5;
    
    // PA6配置为上拉输入
    GPIO_InitStruct5.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStruct5.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct5);

    // 配置EXTI线6
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource6);
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTI_Init(&EXTI_InitStructure);

    // 配置中断优先级（与PA5同级）
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0E;
    NVIC_Init(&NVIC_InitStructure);
		
		 /* 新增PA7配置 */
    GPIO_InitTypeDef GPIO_InitStruct7;
    
    // PA7配置为上拉输入
    GPIO_InitStruct7.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStruct7.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStruct7);

    // 配置EXTI线7
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource7);
    EXTI_InitStructure.EXTI_Line = EXTI_Line7;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; 
    EXTI_Init(&EXTI_InitStructure);

    // 中断优先级配置（与其它按键同级）
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
    NVIC_Init(&NVIC_InitStructure);
		
    TIM3_Init();  // 初始化LED闪烁定时器
    TIM4_Init();  // 初始化蜂鸣器闪烁定时器
}
// 外部中断服务函数
void EXTI1_IRQHandler(void)
{
	   SysTick_Init();  // 初始化系统时钟
    static uint32_t lastPressTime = 0;
    
    if (EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        // 获取当前系统时间（需要实现GetSysTime函数）
        uint32_t currentTime = GetSysTime(); 
        
        // 消抖处理（20ms内只响应一次）
        if ((currentTime - lastPressTime) > 20)
        {
            // 检测双击时间窗口（300ms）
            if ((currentTime - keyPressTime) < 300)
            {
                keyActionFlag = 2;  // 双击
            }
            else
            {
                keyActionFlag = 1;  // 单击
                keyPressTime = currentTime;
            }
        }
        lastPressTime = currentTime;
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

void EXTI4_IRQHandler(void)
{
    static uint32_t lastBeepPressTime = 0;
    
    if (EXTI_GetITStatus(EXTI_Line4) == SET)
    {
        uint32_t currentTime = GetSysTime();
        
        if ((currentTime - lastBeepPressTime) > 20)
        {
            if ((currentTime - beepPressTime) < 300)
            {
                beepActionFlag = 2;
            }
            else
            {
                beepActionFlag = 1;
                beepPressTime = currentTime;
            }
        }
        lastBeepPressTime = currentTime;
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
}

/* 新增中断处理函数 */
void EXTI9_5_IRQHandler(void)
{
		static uint32_t lastPA5Press = 0, lastPA6Press = 0, lastPA7Press = 0;
    uint32_t now = GetSysTime();
	
	
    
    // 处理PA5（LED频率）
    if(EXTI_GetITStatus(EXTI_Line5) && (now - lastPA5Press) > 20)
    {
        ledSpeed = (ledSpeed + 1) % LED_SPEED_MAX;
        speedChangeFlag = 1;
        lastPA5Press = now;
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    
    // 处理PA6（蜂鸣器频率）
    if(EXTI_GetITStatus(EXTI_Line6) && (now - lastPA6Press) > 20)
    {
        beepSpeed = (beepSpeed + 1) % BEEP_SPEED_MAX;
        beepSpeedChangeFlag = 1;
        lastPA6Press = now;
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
		
		// PA7紧急停止处理
    if(EXTI_GetITStatus(EXTI_Line7) && (now - lastPA7Press) > 20) {
        systemShutdownFlag = 1;
        lastPA7Press = now;
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
}