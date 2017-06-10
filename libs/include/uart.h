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

#define CMD_MAX_LENGTH	32
#define pop		gCmdCache[top--]
#define push(s)	gCmdCache[++top] = s
#define clrCache()	{\
	while (top > -1) {\
		pop = '\0';\
	}\
}
#define STACK_OVERFLOW	(top == CMD_MAX_LENGTH - 1)

//	decode
#define TOKEN_START		'$'
#define TOKEN_SEND		'S'
#define TOKEN_LEARN		'L'
#define TOKEN_OFFSET	0x01
#define CMD_NUM_MAX		'8'
#define CMD_NUM_MIN		'1'
#define ISLEGAL_NUM(k)	(((k) >= CMD_NUM_MIN) && ((k) <= CMD_NUM_MAX))

#endif
