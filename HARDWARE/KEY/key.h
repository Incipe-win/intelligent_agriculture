#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "sys.h"

#define KEY1_PIN GPIO_Pin_4
#define KEY2_PIN GPIO_Pin_5
#define KEY3_PIN GPIO_Pin_6
/*库函数*/
// #define KEY0 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_4)  // PE4
// #define KEY1 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_5)  // PE3
// #define KEY2 GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_6)  // PE2
// #define WK_UP GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) // PA0

/*位带操作*/
#define KEY0 PEin(4) // PE4
#define KEY1 PEin(5) // PE3
#define KEY2 PEin(6) // P32
// #define WK_UP PAin(0) // PA0

void Init_LED(void);
void Init_KEY(void);
void Init_BEEP(void);

#endif //__KEY_H_
