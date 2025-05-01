#include "stm32f10x.h"                  // Device header
#include "LED.h"

uint16_t CountSensor_Count;				//全局变量，用于计数
void CountSensor_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructrue;
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE); //启动GPIOB外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);  //启动AFIO外设
	/***
	AFIO：即 Alternate function I/O，复用功能 IO。
	它主要有两个功能，一是配置引脚的复用功能重定向（本文略），
	二是配置中断引脚选择器（本质上也是复用功能配置，
	只不过配置的不是引脚的复用，而是中断通道的复用），
	这里使用的是后者。
	*/
	
	GPIO_InitStructrue.GPIO_Mode = GPIO_Mode_IPU; //上拉出入，默认高电平模式
	GPIO_InitStructrue.GPIO_Pin = GPIO_Pin_14;  //设置为Pin14
	GPIO_InitStructrue.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructrue);
	
	//GPIO_AFIODeInit(); //取消初始化备用函数（重新映射、事件控制以及EXTI配置）将寄存器设置为其默认重置值
	
	
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);   //选择用作EXTI线的GPIO引脚，执行AFIO第14个数据选择器，接到GPIOB对应PB14引脚
	
	
	/**执行AFIO第14个数据选择器，接到GPIOB对应PB14引脚
					EXTI14
						|						
		-----------------
	 /    /            \
	 -------------------
				|  
			B14
	*/
	
	
	/**开始初始化EXTI**/
	EXTI_InitStructure.EXTI_Line=EXTI_Line14;  //配置的中断线，选择EXTI第14中断线
	EXTI_InitStructure.EXTI_LineCmd=ENABLE;  //指定选择中断线的新状态
	EXTI_InitStructure.EXTI_Mode=EXTI_Mode_Interrupt; //设置外部中断线模式，是中断模式（目前设置EXTI_Mode_Interrupt）或者事件模式（EXTI_Mode_Event）
	EXTI_InitStructure.EXTI_Trigger=EXTI_Trigger_Rising_Falling;//指定触发信号的有效边沿，设置下降沿触发进入NVIC触发中断
	/**
	EXTI_Trigger_Rising 上升沿触发
  EXTI_Trigger_Falling 下降沿触发
  EXTI_Trigger_Rising_Falling 上升沿下降沿都触发
	*/
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置中断分组的方式，设置有几个抢占优先级和响应优先级，总共有四个组，第n组有n个抢占优先级，有4-n个响应优先级
	
	NVIC_InitStructure.NVIC_IRQChannel=EXTI15_10_IRQn; //指定中断通道开启关闭 通道见IRQn_Type，请用GotoDefinition搜索文件stm32f10x.h
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; //指定中断通道是使能还是失能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; //指定所选通道抢占优先级 ，这个值在0-15，值在NVIC_Priority_Table
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; //指定所选通道响应优先级，这个值在0-15，值在NVIC_Priority_Table
	
	NVIC_Init(&NVIC_InitStructure);
	
}


uint16_t CountSensor_Get(void)
{
	return CountSensor_Count;
}
//中断函数无需调用，自动执行,请确保函数名正确，不能有任何差异，否则中断函数将不能进入,前往startup_stm32f10x_md.s中查看中断向量表函数名
void EXTI15_10_IRQHandler(void)
{

	//EXTI_GetITStatus(EXTI_LineX,SET)检查指定的EXTI的中断标志位是否为SET,RESET
	
	if(EXTI_GetITStatus(EXTI_Line14)==SET){

		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_14) == 0)
		{
			Delay_ms(100);
			LED2_Turn();
			CountSensor_Count ++;					//计数值自增一次
		}else{
			Delay_ms(100);
			LED2_Turn();
		}
		
		
		//EXTI_ClearITPendingBit(EXTI_LineX)清除中断标志位，否则中断标志位置1会不断跳到中断函数卡住在中断函数里
		EXTI_ClearITPendingBit(EXTI_Line14);
	}
	

}