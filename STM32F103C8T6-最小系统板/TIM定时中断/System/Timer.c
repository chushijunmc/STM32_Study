#include "stm32f10x.h"                  // Device header
#include "Delay.h"
/**
TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);//初始化时基单元
void TIM_SetAutoreload(TIM_TypeDef* TIMx, uint16_t Autoreload);//给自动重装器写入一个值
void TIM_SetCounter(TIM_TypeDef* TIMx, uint16_t Counter);//给计数器写值
void TIM_ARRPreloadConfig(TIM_TypeDef* TIMx, FunctionalState NewState);//自动重装器预装功能配置,某个TIM使能还是失能
void TIM_CounterModeConfig(TIM_TypeDef* TIMx, uint16_t TIM_CounterMode);//改变计数器的计数模式，选择新的计数器模式
void TIM_OC1Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC2Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC3Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_OC4Init(TIM_TypeDef* TIMx, TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);//选择时基单元
void TIM_OCStructInit(TIM_OCInitTypeDef* TIM_OCInitStruct);
void TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);//运行控制，第一选择计数器，第二使能还是失能
void TIM_ITConfig(TIM_TypeDef* TIMx, uint16_t TIM_IT, FunctionalState NewState);//中断输出控制
void TIM_InternalClockConfig(TIM_TypeDef* TIMx);//选择内部时钟，参数为选择那个时钟
void TIM_PrescalerConfig(TIM_TypeDef* TIMx, uint16_t Prescaler, uint16_t TIM_PSCReloadMode);//单独写预分频值，第一参数就是要写入预分频值，第二参数是写入的模式
void TIM_ITRxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_InputTriggerSource); //选择ITRx其他定时器的时钟，第一个参数选择ITRx其他定时器的时钟，第二个参数是选择接入哪个定时器
void TIM_TIxExternalClockConfig(TIM_TypeDef* TIMx, uint16_t TIM_TIxExternalCLKSource,uint16_t TIM_ICPolarity, uint16_t ICFilter); //选择TIx捕获通道的时钟，第二选择TIx具体的某个引脚，第三是选择输入的极性，第四选择滤波器
void TIM_ETRClockMode1Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,uint16_t ExtTRGFilter);//选择ETR通过外部时钟模式1输入的时钟，第二外部触发预分频器，第三是选择输入的极性，第四选择滤波器
void TIM_ETRClockMode2Config(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity, uint16_t ExtTRGFilter);//选择ETR通过外部时钟模式2输入的时钟
void TIM_ETRConfig(TIM_TypeDef* TIMx, uint16_t TIM_ExtTRGPrescaler, uint16_t TIM_ExtTRGPolarity,uint16_t ExtTRGFilter);//单独配置ETR引脚的预分频器、极性、滤波器等参数
uint16_t TIM_GetCounter(TIM_TypeDef* TIMx);获取当前计数器的值
uint16_t TIM_GetPrescaler(TIM_TypeDef* TIMx);获取当前预分频器的值
*/


/*STM32F103C8T6有TIM1,TIM2,TIM3,TIM4四个时钟，其中TIM1是高速时钟，TIM2,TIM3,TIM4是低速时钟*/

extern uint16_t	Num;

//定时器初始化
 void TimerInit(){
	 TIM_TimeBaseInitTypeDef TimeBaseInitStructure;
	 NVIC_InitTypeDef NVIC_InitStructure;
	 TIM_ICInitTypeDef TIM_ICInitStructure;

// 配置输入捕获通道（以TI1为例）
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; // 上升沿触发
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; // 直接映射到TI1
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; // 不分频
	TIM_ICInitStructure.TIM_ICFilter = 0x0; // 无滤波
	TIM_ICInit(TIM2, &TIM_ICInitStructure);//Slave Mode 

// 配置从模式为Reset，触发源为TI1
TIM_SelectInputTrigger(TIM2, TIM_TS_TI1FP1);
TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
	 
 //初始化TIM2，TIM2是属于低速定时器
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	 //选择内部时钟
	 TIM_InternalClockConfig(TIM2);
	 //配置时基单元
	 
	 //设置参数
	 TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV4; //时基单元滤波参数
	 TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up; //TIM计数模式，设置向上计数 /|/|/| 其他有向下计数和三种中央对其模式
	 TimeBaseInitStructure.TIM_Period=10000-1; //ARR自动重装器的值（周期），需要公式计算，到该值时会自动置0
	 TimeBaseInitStructure.TIM_Prescaler=7200-1; //PSC预分频器的值，需要公式计算,预分屏器和计数器有一个数偏差需要减1
	 //计时器定时频率=处理器时钟频率/(PSC+1)/(ARR+1)
	 TimeBaseInitStructure.TIM_RepetitionCounter=0; //重复计数器，只有高级定时器才生效，TIM2不需要
	 
	 	TIM_TimeBaseInit(TIM2, &TimeBaseInitStructure);
	 
	 	TIM_ClearFlag(TIM2, TIM_FLAG_Update);  //更新事件和更新中断是同时发生了，调用可以在TIM初始化前中断前
	 TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);//中断输出控制
	 /**
		TIM_IT_Update：定时器溢出/更新中断（计数器溢出时触发）。
		TIM_IT_CC1、TIM_IT_CC2、TIM_IT_CC3、TIM_IT_CC4：通道 1-4 的捕获/比较中断（用于 PWM、输入捕获等）。
		TIM_IT_COM：互补输出中断（用于高级定时器的互补 PWM 通道）。
		TIM_IT_Trigger：触发中断（定时器与其他外设同步时触发）。
		TIM_IT_Break：刹车中断（用于电机控制中的紧急停止信号检测）。
		第三参数是设置中断使能状态
	 */
	 
	 //到NVIC
	 
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断分组的方式，设置有几个抢占优先级和响应优先级，总共有四个组，第n组有n个抢占优先级，有4-n个响应优先级
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQn; //指定中断通道开启关闭 通道见IRQn_Type，请用GotoDefinition搜索文件stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //指定中断通道是使能还是失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2; //指定所选通道抢占优先级 ，这个值在0-15，值在NVIC_Priority_Table
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //指定所选通道响应优先级，这个值在0-15，值在NVIC_Priority_Table
	
	NVIC_Init(&NVIC_InitStructure);
	
	//TIM_SelectInputTrigger(TIM2, TIM_TS_ETRF);           // 触发源为ETR
	//TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Trigger);    // SMS=110
	
	TIM_Cmd(TIM2,ENABLE);
	 
 }
 
 void TIM2_IRQHandler(){
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)==SET){
			
			Num++;
			//Delay_s(1);
			TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
		
		}
 }
 