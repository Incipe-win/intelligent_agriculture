#include "uart.h"
#include "esp8266.h"
#include "led.h"
#include "sys.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

extern u8 flag;

/*
************************************************************
*	函数名称：	Usart1_Init
*
*	函数功能：	串口1初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA9		RX-PA10
************************************************************
*/
void Usart1_Init(unsigned int baud) {

  GPIO_InitTypeDef gpioInitStruct;
  USART_InitTypeDef usartInitStruct;
  NVIC_InitTypeDef nvicInitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

  // PA9	TXD
  gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
  gpioInitStruct.GPIO_OType = GPIO_OType_PP;
  gpioInitStruct.GPIO_Pin = GPIO_Pin_9;
  gpioInitStruct.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOA, &gpioInitStruct);

  // PA10	RXD
  gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
  gpioInitStruct.GPIO_OType = GPIO_OType_PP;
  gpioInitStruct.GPIO_Pin = GPIO_Pin_10;
  gpioInitStruct.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOA, &gpioInitStruct);

  usartInitStruct.USART_BaudRate = baud;
  usartInitStruct.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;                         //无硬件流控
  usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收和发送
  usartInitStruct.USART_Parity = USART_Parity_No;             //无校验
  usartInitStruct.USART_StopBits = USART_StopBits_1;          // 1位停止位
  usartInitStruct.USART_WordLength = USART_WordLength_8b;     // 8位数据位
  USART_Init(USART1, &usartInitStruct);

  USART_Cmd(USART1, ENABLE); //使能串口

  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //使能接收中断

  nvicInitStruct.NVIC_IRQChannel = USART1_IRQn;
  nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
  nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
  NVIC_Init(&nvicInitStruct);
}

/*
************************************************************
*	函数名称：	Usart2_Init
*
*	函数功能：	串口2初始化
*
*	入口参数：	baud：设定的波特率
*
*	返回参数：	无
*
*	说明：		TX-PA2		RX-PA3
************************************************************
*/
void Usart2_Init(unsigned int baud) {

  GPIO_InitTypeDef gpioInitStruct;
  USART_InitTypeDef usartInitStruct;
  NVIC_InitTypeDef nvicInitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);

  // PA2	TXD
  gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
  gpioInitStruct.GPIO_OType = GPIO_OType_PP;
  gpioInitStruct.GPIO_Pin = GPIO_Pin_5;
  gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &gpioInitStruct);

  // PA3	RXD
  gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
  gpioInitStruct.GPIO_OType = GPIO_OType_PP;
  gpioInitStruct.GPIO_Pin = GPIO_Pin_6;
  gpioInitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOD, &gpioInitStruct);

  usartInitStruct.USART_BaudRate = baud;
  usartInitStruct.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;                         //无硬件流控
  usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收和发送
  usartInitStruct.USART_Parity = USART_Parity_No;             //无校验
  usartInitStruct.USART_StopBits = USART_StopBits_1;          // 1位停止位
  usartInitStruct.USART_WordLength = USART_WordLength_8b;     // 8位数据位
  USART_Init(USART2, &usartInitStruct);

  USART_Cmd(USART2, ENABLE); //使能串口

  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE); //使能接收中断

  nvicInitStruct.NVIC_IRQChannel = USART2_IRQn;
  nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
  nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  nvicInitStruct.NVIC_IRQChannelSubPriority = 0;
  NVIC_Init(&nvicInitStruct);
}

void Usart3_Init(unsigned int baud) {
  GPIO_InitTypeDef gpioInitStruct;
  USART_InitTypeDef usartInitStruct;
  NVIC_InitTypeDef nvicInitStruct;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART1);

  // PA9	TXD
  gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
  gpioInitStruct.GPIO_OType = GPIO_OType_PP;
  gpioInitStruct.GPIO_Pin = GPIO_Pin_8;
  gpioInitStruct.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOD, &gpioInitStruct);

  // PA10	RXD
  gpioInitStruct.GPIO_Mode = GPIO_Mode_AF;
  gpioInitStruct.GPIO_OType = GPIO_OType_PP;
  gpioInitStruct.GPIO_Pin = GPIO_Pin_9;
  gpioInitStruct.GPIO_Speed = GPIO_Fast_Speed;
  GPIO_Init(GPIOD, &gpioInitStruct);

  usartInitStruct.USART_BaudRate = baud;
  usartInitStruct.USART_HardwareFlowControl =
      USART_HardwareFlowControl_None;                         //无硬件流控
  usartInitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; //接收和发送
  usartInitStruct.USART_Parity = USART_Parity_No;             //无校验
  usartInitStruct.USART_StopBits = USART_StopBits_1;          // 1位停止位
  usartInitStruct.USART_WordLength = USART_WordLength_8b;     // 8位数据位
  USART_Init(USART3, &usartInitStruct);

  USART_Cmd(USART3, ENABLE); //使能串口

  USART_ITConfig(USART3, USART_IT_RXNE, ENABLE); //使能接收中断

  nvicInitStruct.NVIC_IRQChannel = USART3_IRQn;
  nvicInitStruct.NVIC_IRQChannelCmd = ENABLE;
  nvicInitStruct.NVIC_IRQChannelPreemptionPriority = 0;
  nvicInitStruct.NVIC_IRQChannelSubPriority = 2;
  NVIC_Init(&nvicInitStruct);
}

/*
************************************************************
*	函数名称：	Usart_SendString
*
*	函数功能：	串口数据发送
*
*	入口参数：	USARTx：串口组
*				str：要发送的数据
*				len：数据长度
*
*	返回参数：	无
*
*	说明：
************************************************************
*/
void Usart_SendString(USART_TypeDef *USARTx, unsigned char *str,
                      unsigned short len) {

  unsigned short count = 0;

  for (; count < len; count++) {
    USART_SendData(USARTx, *str++); //发送数据
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
      ; //等待发送完成
  }
}

/*
************************************************************
*	函数名称：	UsartPrintf
*
*	函数功能：	格式化打印
*
*	入口参数：	USARTx：串口组
*				fmt：不定长参
*
*	返回参数：	无
*
*	说明：
************************************************************
*/
void UsartPrintf(USART_TypeDef *USARTx, char *fmt, ...) {

  unsigned char UsartPrintfBuf[296];
  va_list ap;
  unsigned char *pStr = UsartPrintfBuf;

  va_start(ap, fmt);
  vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap); //格式化
  va_end(ap);

  while (*pStr != 0) {
    USART_SendData(USARTx, *pStr++);
    while (USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET)
      ;
  }
}

void USART3_IRQHandler(void) {
  u8 res;
  if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) {
    res = USART_ReceiveData(USART3);
    if (res == '1') {
      LED1 = 0;
    } else if (res == '2') {
      LED1 = 1;
    } else if (res == '3') {
      BEEP = 1;
    } else if (res == '4') {
      BEEP = 0;
      flag = 0;
    }
    while (USART_GetFlagStatus(USART3, USART_FLAG_TC) != SET)
      ;
  }
}
