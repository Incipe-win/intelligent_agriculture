#include "pwm.h"
#include "led.h"

/* * * * * * * * * * * * * * * * * *
 * @parm arr: TIM重装载计数值       *
 * @parm psc: 预分频系数            *
 * @parm plause: 初始化占空比设置   *
 * * * * * * * * * * * * * * * * * */
void TIM1_PWM_Init(u32 arr, u32 psc) {
  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_TIM1);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Pin = LED2_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  TIM_TimeBaseInitStructure.TIM_Period = arr;
  TIM_TimeBaseInitStructure.TIM_Prescaler = psc;
  TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);

  // PWM1模式
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  //输出极性
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  //互补输出极性
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_Low;
  //比较输出使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //比较互补输出使能
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;

  //指定空闲状态下的TIM输出比较的引脚状态。
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  //指定空闲状态下的TIM互补输出比较的引脚状态。
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Set;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);

  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM1, ENABLE);

  //使能PWM外围输出
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
  TIM_Cmd(TIM1, ENABLE);
}

void TIM2_PWM_Init(u32 arr, u32 psc) {
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

  GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_TIM2);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

  //初始化定时器1
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  //初始化TIM2 Channe3 PWM模式
  //选择定时器模式:TIM脉冲宽度调制模式2
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  //比较输出使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //输出极性:TIM输出比较极性低
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;

  //根据T指定的参数初始化外设TIM2 4OC1
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);

  //使能TIM2在CCR1上的预装载寄存器
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  // ARPE使能
  TIM_ARRPreloadConfig(TIM2, ENABLE);

  //使能TIM2
  TIM_Cmd(TIM2, ENABLE);
}

void TIM4_PWM_Init(u32 arr, u32 psc) {
  GPIO_InitTypeDef GPIO_InitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

  //初始化定时器1
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  //初始化TIM2 Channe3 PWM模式
  //选择定时器模式:TIM脉冲宽度调制模式2
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  //比较输出使能
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  //输出极性:TIM输出比较极性低
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_Pulse = 0;

  //根据T指定的参数初始化外设TIM2 4OC1
  TIM_OC2Init(TIM4, &TIM_OCInitStructure);

  //使能TIM2在CCR1上的预装载寄存器
  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);

  // ARPE使能
  TIM_ARRPreloadConfig(TIM4, ENABLE);

  //使能TIM2
  TIM_Cmd(TIM4, ENABLE);
}

void SERVO_Angle_Control(uint16_t Compare2) {
  TIM_SetCompare2(TIM4, Compare2); //设置通道2为可变的pwm
}

// 200 - (200 * 0.025) = 195 0°
//                       190
