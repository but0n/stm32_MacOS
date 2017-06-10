#ifndef UART_H
#define UART_H

void uart_init(unsigned int pclk2, unsigned int bound);

void uart_sendData(unsigned char data);
void uart_sendStr(char * cmd);

void uart_int2char(unsigned int k);
void uart_short2char(unsigned short k);
unsigned char uart_Float2Char(float value);

void USART1_IRQHandler(void);

extern void jump2ISP();


#define UART_CR() do {\
    uart_sendData(0x0D);\
    uart_sendData(0x0A);\
} while(0)
#define UART_CLEAR() uart_sendStr("\033[H\033[J")


#endif
