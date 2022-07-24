#ifndef MY_CODE
#define MY_CODE

#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "sys.h"
#include "delay.h"
#include "stdio.h"
#include "ds18b20.h"
#include "i2c.h"
#include "oled.h"

#define SendOut PBout(13)

//函数初始化
void MY_Init(void);
//主函数中while函数调用
void RUN(void);
//ADC采集处理函数
void ADC_test(void);
	//将采集值进行验证
	void test_change(void);
	//将采集值转为二进制存进数组
	void test_data(uint16_t data);
	//将二进制的数组进行输出
	void data_send(void);
//温度输出
void temputure_show(void);
//串口重定向
int fputc(int ch,FILE*f);






#endif

