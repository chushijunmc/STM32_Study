#include "key.h"

//按键处初始化函数
void KEY_GPIO_Config(void)
{
	/*定义一个 GPIO_InitTypeDef 类型的结构体*/
	GPIO_InitTypeDef  GPIO_InitStruct;
	
	/*开启按键相关的 GPIO 外设时钟*/
	RCC_APB2PeriphClockCmd(KEY0_4_GPIO_CLK, ENABLE);
	
	/*选择要控制的KEY0~KEY4的 GPIO 引脚*/
	GPIO_InitStruct.GPIO_Pin = KEY0_GPIO_PIN|KEY1_GPIO_PIN|KEY2_GPIO_PIN|KEY3_GPIO_PIN|KEY4_GPIO_PIN;	
	/*设置引脚模式为上拉输入*/
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;	

	/*调用库函数，初始化 GPIO*/
	GPIO_Init(KEY0_4_GPIO_PORT, &GPIO_InitStruct);
}

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下
//5，KEY4按下
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3>KEY4!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0))
	{
		key_up=0;
		if(KEY0==0)return KEY0_PRES;
		else if(KEY1==0)return KEY1_PRES;
		else if(KEY2==0)return KEY2_PRES;
		else if(KEY3==0)return KEY3_PRES;
		else if(KEY4==0)return KEY4_PRES;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1)key_up=1; 	    
 	return 0;// 无按键按下
}
