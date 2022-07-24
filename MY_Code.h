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

//������ʼ��
void MY_Init(void);
//��������while��������
void RUN(void);
//ADC�ɼ�������
void ADC_test(void);
	//���ɼ�ֵ������֤
	void test_change(void);
	//���ɼ�ֵתΪ�����ƴ������
	void test_data(uint16_t data);
	//�������Ƶ�����������
	void data_send(void);
//�¶����
void temputure_show(void);
//�����ض���
int fputc(int ch,FILE*f);






#endif

