#include "stm32f10x.h"                  // Device header


/*
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
配置输出比较模块

void TIM_OC1PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC2PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC3PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
void TIM_OC4PreloadConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPreload);
配置CCR寄存器的预装功能

void TIM_OC1FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC2FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC3FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
void TIM_OC4FastConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCFast);
配置快速使能的

void TIM_ClearOC1Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC2Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC3Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
void TIM_ClearOC4Ref(TIM_TypeDef* TIMx, uint16_t TIM_OCClear);
外部事件清除REF信号

void TIM_OC1PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity); //单独设置输出比较极性
void TIM_OC1NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);//高级定时器的互补通道设置
void TIM_OC2PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC2NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC3PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);
void TIM_OC3NPolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCNPolarity);
void TIM_OC4PolarityConfig(TIM_TypeDef* TIMx, uint16_t TIM_OCPolarity);

void TIM_CCxCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCx);
void TIM_CCxNCmd(TIM_TypeDef* TIMx, uint16_t TIM_Channel, uint16_t TIM_CCxN);//单独设置使能参数

void TIM_SetCompare1(TIM_TypeDef* TIMx, uint16_t Compare1);
void TIM_SetCompare2(TIM_TypeDef* TIMx, uint16_t Compare2);
void TIM_SetCompare3(TIM_TypeDef* TIMx, uint16_t Compare3);
void TIM_SetCompare4(TIM_TypeDef* TIMx, uint16_t Compare4);//单独更改CCR寄存器的函数

void TIM_CtrlPWMOutputs(TIM_TypeDef* TIMx, FunctionalState NewState); //仅限高级定时器使用，使用高级定时器输出PWM时需要调用该函数使能主输出，否则PWM将不能输出
*/
void PWM_Init(void){

	GPIO_InitTypeDef GPIO_InitStructure;
	 TIM_TimeBaseInitTypeDef TimeBaseInitStructure;

		TIM_OCInitTypeDef TIM_OCInitStructure;
	
		
	//引脚重定义
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);//将TIM2引脚部分重映射，PA0转到PA15，详情看引脚定义表和参考手册
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);//PA15解除JTAG恢复普通GPIO口
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //使用复用推挽输出，才能使用定时器控制引脚，将输出控制权交给片上外设
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	
	

 //初始化TIM2，TIM2是属于低速定时器
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	 //选择内部时钟
	 TIM_InternalClockConfig(TIM2);
	 //配置时基单元
	 
	 //设置参数
	  TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//时基单元滤波参数
	 TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//TIM计数模式，设置向上计数 /|/|/| 其他有向下计数和三种中央对其模式
	 TimeBaseInitStructure.TIM_Period=3000-1; //ARR自动重装器的值（周期），需要公式计算，到该值时会自动置0
	 TimeBaseInitStructure.TIM_Prescaler=720-1; //PSC预分频器的值，需要公式计算,预分屏器和计数器有一个数偏差需要减1
	 //计时器定时频率=处理器时钟频率/(PSC+1)/(ARR+1)
	 TimeBaseInitStructure.TIM_RepetitionCounter=0; //重复计数器，只有高级定时器才生效，TIM2不需要
	 
	 	TIM_TimeBaseInit(TIM2, &TimeBaseInitStructure);
	 
	 	TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //更新事件和更新中断是同时发生了，调用可以在TIM初始化前中断前

		TIM_ARRPreloadConfig(TIM2, ENABLE); // 启用ARR预装载
    TIM_ARRPreloadConfig(TIM2, ENABLE); // 启用 ARR 预装载缓冲
    TIM_PrescalerConfig(TIM2, TimeBaseInitStructure.TIM_Prescaler, TIM_PSCReloadMode_Update);   // 启用 PSC 预装载缓冲（某些型号支持）

/**
TIM_OCMode_Timing	不改变引脚电平，仅触发事件	定时触发中断/DMA定时器计时到特定值时触发操作（如更新数据、启动 ADC 采样）。不直接驱动 GPIO，适用于需要精确时间基准的场景。
TIM_OCMode_Active	强制有效电平	初始化高电平初始化时强制引脚为高电平（如启动电机）。在特定条件下锁定输出状态。
TIM_OCMode_Inactive	强制无效电平	初始化低电平初始化时强制引脚为低电平（如关闭 LED）。系统故障时安全关闭输出。
TIM_OCMode_Toggle	匹配时翻转电平	方波生成生成固定频率的方波信号（如驱动蜂鸣器）。创建简单的时钟信号。
TIM_OCMode_PWM1	计数器 < CCR → 有效电平	常规 PWM 控制,生成标准 PWM 信号（控制 LED 亮度、电机速度）。占空比 = CCR / (ARR + 1)。
TIM_OCMode_PWM2	计数器 ≥ CCR → 有效电平	反向 PWM 控制,需要反向 PWM 逻辑的场景（如低电平激活的外设）。占空比 = (ARR + 1 - CCR) / (ARR + 1)。
*/
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;  //设置输出比较的工作模式。取值：PWM 模式（如 TIM_OCMode_PWM1/PWM2）：生成 PWM 信号。Toggle 模式（TIM_OCMode_Toggle）：比较匹配时翻转输出电平。Active/Inactive 模式：强制输出高/低电平。冻结模式（TIM_OCMode_Frozen）：不响应比较事件。
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High; //设置主输出通道的极性。TIM_OCPolarity_High：有效电平为高。TIM_OCPolarity_Low：有效电平为低。决定 PWM 的有效电平（如高电平有效或低电平有效）。
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable; //设置主输出通道的使能状态。
	//TIM_OCInitStructure.TIM_OutputNState=TIM_OutputState_Enable; //设置互补输出通道的使能状态（仅高级定时器 TIM1/TIM8 有效）。
	TIM_OCInitStructure.TIM_Pulse=10; //设置设置捕获比较寄存器（CCR）的值，决定 PWM 占空比或比较事件的触发点。
	//TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Reset; //设置主输出在空闲状态（定时器停止时）的电平（仅 TIM1/TIM8 有效）。用途：系统故障时安全控制（如紧急停止电机）。
	//TIM_OCInitStructure.TIM_OCNIdleState=TIM_OCIdleState_Reset; //设置互补输出在空闲状态的电平（仅 TIM1/TIM8 有效）。
	//TIM_OCInitStructure.TIM_OCNPolarity=TIM_OCPolarity_Low;//设置互补输出通道的极性（仅 TIM1/TIM8 有效）。
	
	
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	
	TIM_Cmd(TIM2,ENABLE);
	
}

void PWM_SetCompare1(uint16_t Compare)
{
	TIM_SetCompare1(TIM2, Compare);		//设置CCR1的值
}

void PWM_SetFrequency(uint32_t freqHz) {
    uint32_t timerClock = 72000000;  // TIM2 时钟频率（假设 72MHz）
    if (freqHz == 0) return;

    // 计算 ARR 和 PSC
    uint32_t period = timerClock / freqHz;
    uint16_t psc = (uint16_t)((period - 1) / 0x10000);
    uint16_t arr = (uint16_t)(period / (psc + 1)) - 1;

    // 限制范围
    psc = (psc > 0xFFFF) ? 0xFFFF : psc;
    arr = (arr > 0xFFFF) ? 0xFFFF : arr;

    // 配置 PSC 和 ARR
    TIM_PrescalerConfig(TIM2, psc, TIM_PSCReloadMode_Update);  // 使用 Update 模式
    TIM_SetAutoreload(TIM2, arr);
    
    // 如果仍有问题，手动触发更新事件
   // TIM2->EGR |= TIM_EGR_UG;  // 直接操作寄存器触发更新
}

void PWM_SetDutyCycle(float dutyCycle) {
    dutyCycle = (dutyCycle > 100.0f) ? 100.0f : (dutyCycle < 0.0f) ? 0.0f : dutyCycle;
    uint16_t ccr = (uint16_t)((TIM2->ARR + 1) * dutyCycle / 100.0f);
    TIM_SetCompare1(TIM2, ccr);
}