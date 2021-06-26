#ifndef __LED_H_
#define __LED_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define LED1_PIN GPIO_Pin_8
#define LED2_PIN GPIO_Pin_9
#define LED3_PIN GPIO_Pin_10

#define BEEP_PIN GPIO_Pin_10

#define LED1 PEout(8)
#define LED2 PEout(9)
#define LED3 PEout(10)
#define BEEP PBout(10)

void Init_LED(void);
void Init_BEEP(void);

#endif //__LED_H_
