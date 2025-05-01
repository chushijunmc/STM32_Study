//Filename: main.c
/**
实训台节点
*/
#include "includes.h"

void Delay(Int32U);

int main(void)
{
	BEEPState(BEEP_ON);
	exit_Init();
	BSPInit();
	Delay_ms(200);
	BEEP(BEEP_OFF);
	while(1)
	{
		LED(0,LED_ON);
		LED(1,LED_OFF);
		LED(2,LED_OFF);
		Delay_ms(250);

		LED(0,LED_OFF);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_ms(250);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		LED(2,LED_ON);
		Delay_ms(250);
	}
}

void Delay(Int32U u)
{
	volatile Int32U i,j;
	for(i=0;i<u;i++)
		for(j=0;j<12000;j++);
}

