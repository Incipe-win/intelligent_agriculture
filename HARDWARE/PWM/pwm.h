#ifndef __PWM_H_
#define __PWM_H_

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

void TIM1_PWM_Init(u32 arr, u32 psc);
void TIM2_PWM_Init(u32 arr, u32 psc);
void TIM4_PWM_Init(u32 arr, u32 psc);
void TIM8_PWM_Init(u32 arr, u32 psc);
void SERVO_Angle_Control(uint16_t Compare1);

#endif // __PWM_H_
