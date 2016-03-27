/*************************************************************************************
* Test-program for Olimex “STM32-H103”, header board for “STM32F103RBT6”.
* After program start green LED (LED_E) will blink.
*
* Program has to be compiled with optimizer setting "-O0".
* Otherwise delay via while-loop will not work correctly.
*************************************************************************************/
#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
int main(int argc, char *argv[])
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 	u32 delay;
/* GPIOC Periph clock enable */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOF, ENABLE);
/* Configure PC12 to mode: slow rise-time, pushpull output */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; // GPIO No. 12
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; // slow rise time
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // push-pull output
	GPIO_Init(GPIOF, &GPIO_InitStructure); // GPIOC init
	while(1)
	{
		/* make some float calculations */
		float x = 42, y = 23, z = 7;
		int i = 0;
		for ( i = 0; i < 6; i++ )
		{
			z = (x*y)/z;
		};
		/* GPIO PC12 set, pin=high, LED_E off */
		GPIOF->BSRR = GPIO_BSRR_BS6;
		/*GPIO_WriteBit(GPIOC,GPIO_Pin_12,Bit_SET);*/
		/* delay --> compiler optimizer settings must be "-O0" */
		delay=500000;
		while(delay)
			delay--;
		/* GPIO PC12 reset, pin=low, LED_E on */
		GPIOF->BSRR = GPIO_BSRR_BR6;
		/*GPIO_WriteBit(GPIOC,GPIO_Pin_12,Bit_RESET);*/
		/* delay --> compiler optimizer settings must be "-O0" */
		delay=500000;
		while(delay)
			delay--;
	}
}
