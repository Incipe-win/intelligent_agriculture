#include "MqttKit.h"
#include "adc.h"
#include "bmp.h"
#include "delay.h"
#include "dht11.h"
#include "esp8266.h"
#include "exti.h"
#include "key.h"
#include "led.h"
#include "oled.h"
#include "onenet.h"
#include "pwm.h"
#include "stm32f4xx.h"
#include "sys.h"
#include "timer.h"
#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

u8 temperature = 0;
u8 humidity = 0;
u8 flag = 0;
u16 adcx = 0;

const char *topics[] = {"/incipe/sub"};
const char *sub_topics = "/incipe/pub";

void Hardware_Init(void) {

  delay_init(168);

  tim2_init(4999, 7199);
  tim3_init(2499, 7199);
  Usart1_Init(115200);
  Usart2_Init(115200);
  Usart3_Init(9600);

  UsartPrintf(USART_DEBUG, " Hardware init OK\r\n");

  Init_LED();
  Init_BEEP();
  Init_KEY();
  EXTI_Config();
  Adc_Init();

  TIM4_PWM_Init(199, 7199); //(199+1)*(7199+1)/168*10^6
                            //上面一行求出0.02s,即20ms

  OLED_Init();
  OLED_ColorTurn(0);   // 0正常显示，1 反色显示
  OLED_DisplayTurn(0); // 0正常显示 1 屏幕翻转显示
}

int main(void) {
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

  unsigned short timeCount = 0; //发送间隔变量
  unsigned char *dataPtr = NULL;
  char pub_buf[80];

  Hardware_Init(); //初始化外围硬件
  ESP8266_Init();
  while (OneNet_DevLink()) //接入OneNET
    delay_ms(500);
  // DHT11初始化
  OneNet_Subscribe(topics, 1);

  while (DHT11_Init()) {
    ;
  }
  while (1) {

    //一秒执行一次 100 / 25 = 40
    if (timeCount % 40 == 0) {
      DHT11_Read_Data(&temperature, &humidity); //读取温湿度值
      if (temperature > 30 || humidity > 95) {
        flag = 1;
      } else {
        flag = 0;
      }
      adcx = Get_Adc_Average(ADC_Channel_0, 20);
      UsartPrintf(USART3, "temperature: %d, humidity: %d, illumination:%d\r\n",
                  temperature, humidity, adcx);
    }
    // 5秒发送一次数据  5000 / 25 = 200
    if (++timeCount >= 200) {
      memset(pub_buf, 0, sizeof(pub_buf));
      sprintf(pub_buf, "{\"Hum\":%d, \"Temp\":%d, \"Light\": %d}", temperature,
              humidity, adcx);
      UsartPrintf(USART_DEBUG, "OneNet_Publish\r\n");
      OneNet_Publish(sub_topics, pub_buf);
      timeCount = 0;
      ESP8266_Clear();
    }
    dataPtr = ESP8266_GetIPD(3);
    if (dataPtr != NULL)
      OneNet_RevPro(dataPtr);
    delay_ms(10);
  }
}
