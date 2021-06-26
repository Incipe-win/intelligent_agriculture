#ifndef __UART_H_
#define __UART_H_
#include "misc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "stm32f4xx_usart.h"

#define USART_DEBUG USART1

void Usart1_Init(unsigned int baud);
void Usart2_Init(unsigned int baud);
void Usart3_Init(unsigned int baud);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str,
                      unsigned short len);
void UsartPrintf(USART_TypeDef *USARTx, char *fmt, ...);

#endif // __UART_H_
