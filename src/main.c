#include "stm32f10x.h"

#define NVIC_GROUPING	3

#define ISP_ADDR		0x1FFFF000

void delay_ms(unsigned int t) {
	SysTick->LOAD = 9000 * t;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x01;
	for(unsigned int tmp = SysTick->CTRL;(tmp&0x01)&&(!(tmp&SysTick_CTRL_COUNTFLAG));tmp = SysTick->CTRL);
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

void delay_us(unsigned int t) {
	SysTick->LOAD = 9 * t;
	SysTick->VAL = 0;
	SysTick->CTRL = 0x01;
	for(unsigned int tmp = SysTick->CTRL;(tmp&0x01)&&(!(tmp&SysTick_CTRL_COUNTFLAG));tmp = SysTick->CTRL);
	SysTick->CTRL = 0;
	SysTick->VAL = 0;
}

void jump2ISP() {
	__set_MSP(*(unsigned int *)ISP_ADDR);
	((void (*)(void))*((unsigned int *)(ISP_ADDR + 4)))();
}

int main() {
	NVIC_SetPriorityGrouping(0x07 - NVIC_GROUPING);
	uart_init(72, 115200);
	while(1);
}
