//Filename: main.c

#include "includes.h"

void Delay(Int32U);

int main(void)
{
	LEDInit();
	LED(0,LED_OFF);
	LED(1,LED_OFF);
	LED(2,LED_OFF);

	for(;;)
	{
		LED(0,LED_ON);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_s(3);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		LED(2,LED_OFF);
		Delay_s(1);
		LED(0,LED_ON);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_s(3);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		Delay_s(1);
		LED(0,LED_ON);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_s(7);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		LED(2,LED_OFF);
		Delay_s(1);
		LED(0,LED_ON);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_s(2);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		LED(2,LED_OFF);
		Delay_s(1);
		LED(0,LED_ON);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_s(2);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		LED(2,LED_OFF);
		Delay_s(1);
		LED(0,LED_ON);
		LED(1,LED_ON);
		LED(2,LED_OFF);
		Delay_s(5);
		LED(0,LED_OFF);
		LED(1,LED_OFF);
		LED(2,LED_OFF);
		Delay_s(1);
	}
}

void Delay(Int32U u)
{
	volatile Int32U i,j;
	for(i=0;i<u;i++)
		for(j=0;j<12000;j++);
}

