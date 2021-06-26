#include "timer.h"
#include "dht11.h"
#include "oled.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern u8 temperature;
extern u8 humidity;
extern u8 flag;
extern u16 adcx;

void tim2_init(u16 arr, u16 psc) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM2, ENABLE);
}

/* * * * * * * * * * * * *
 *  通用定时器3中断初始化  *
 *  arr：自动重装值。     *
 *  psc：时钟预分频数     *
 * * * * * * * * * * * * */
void tim3_init(u16 arr, u16 psc) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  // 时钟使能
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

  //定时器TIM3初始化
  //设置在下一个更新事件装入活动的自动重装载寄存器周期的值
  TIM_TimeBaseStructure.TIM_Period = arr;
  //设置用来作为TIMx时钟频率除数的预分频值
  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  //设置时钟分割:TDTS = Tck_tim
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  // TIM向上计数模式
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  //根据指定的参数初始化TIMx的时间基数单位
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  //使能指定的TIM3中断,允许更新中断
  TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

  //中断优先级NVIC设置
  // TIM3中断
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  //先占优先级0级
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  //从优先级3级
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  // IRQ通道被使能
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  //初始化NVIC寄存器
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM3, ENABLE); //使能TIMx
}

void tim4_init(u16 arr, u16 psc) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

  TIM_TimeBaseStructure.TIM_Period = arr;
  TIM_TimeBaseStructure.TIM_Prescaler = psc;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);

  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  TIM_Cmd(TIM4, ENABLE);
}

void TIM2_IRQHandler(void) {
  if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

    OLED_ShowChinese(0, 0, 0, 16, 1);
    OLED_ShowChinese(17, 0, 1, 16, 1);
    if (temperature >= 10) {
      OLED_ShowNum(34, 0, temperature, 2, 16, 1);
    } else if (temperature < 10) {
      OLED_ShowNum(34, 0, temperature, 1, 16, 1);
    }
    OLED_ShowChinese(57, 0, 4, 16, 1);

    OLED_ShowChinese(0, 17, 2, 16, 1);
    OLED_ShowChinese(17, 17, 3, 16, 1);
    if (humidity >= 100) {
      OLED_ShowNum(34, 17, humidity, 3, 16, 1);
    } else if (humidity >= 10) {
      OLED_ShowNum(34, 17, humidity, 2, 16, 1);
    } else if (humidity < 10) {
      OLED_ShowNum(34, 17, humidity, 1, 16, 1);
    }
    OLED_ShowString(58, 17, (u8 *)"%", 16, 1);

    OLED_ShowChinese(0, 34, 6, 16, 1);
    OLED_ShowChinese(17, 34, 7, 16, 1);
    OLED_ShowNum(34, 34, adcx, 2, 16, 1);
    OLED_Refresh();
  }
}

void TIM3_IRQHandler(void) {
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    if (flag) {
      BEEP = !BEEP;
    }
  }
}
