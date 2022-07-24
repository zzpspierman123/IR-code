#include "my_code.h"

//��ADC�Ĳɼ�ֵ
uint16_t My_ADC_data;
//������Ƶ�ת��ֵ
uint8_t data_buff[9];
//װ���¶�
uint8_t temperature=0;
//��ʱ����¶�
uint16_t Temp_count=0;
//���¶�����
uint16_t T_dat=0;
//#define change_start 1024

/*
 *������ʱ��
*/
void MY_Init()
{
	
	 HAL_TIM_Base_Start_IT(&htim3);

	
}

/*
 *�õ�ADC�Ĳɼ�ֵ��
 *���ɼ�ֵת������
 *��������ֵ���б������
*/
 void ADC_test()
{
	HAL_ADC_Start (&hadc1 );
	My_ADC_data = HAL_ADC_GetValue (&hadc1 );
	test_data (My_ADC_data);
	data_send ();
	Temp_count++;
	if(Temp_count>30000)
	{
		Temp_count=0;
		HAL_TIM_Base_Stop_IT(&htim3 );
	}
}

/*
 *��һ��12λ������Ϊ8λ
 *��Ϊ��λ�����ƺ��������
*/
void test_data(uint16_t data)
{
	static int j=17;
	HAL_GPIO_WritePin (GPIOF ,GPIO_PIN_9 ,GPIO_PIN_RESET );
	uint8_t  cnt = 0;
	data = data >> 4;
	
	for(cnt = 0; cnt < 8; cnt ++)
	{
		data_buff[7-cnt] =(data & 0x001);
		data = data >> 1;
	}
	
	if(j>=16)
   {
     j=0;
		 T_dat=temperature;							  	// 12λ���ݷ��������¶�ȡ�¶�����
   } 				  
 	data_buff[8]=(uint8_t)((T_dat&0x8000)>>15);	// ��λȡ����λ���ݶ����洢
 	T_dat=T_dat<<1 ;
  j++;	
}

/*
 *�������1
 *�������0
*/
void data_send()
{
		int i = 0;

	for(i = 0; i < 9; i ++)
	{
		if(0== data_buff[i])
		{
			SendOut = 1;
			delay_us(2);
			SendOut = 0;
			delay_us(3);
		}
		else
		{
		 	SendOut = 1;
			delay_us(2);
			SendOut = 0;
			delay_us(8);
		}	
	}
	
	//����һ�����أ����ⶪʧ���һ������
	SendOut = 1;
	delay_us(2);
	SendOut = 0;
	
} 


void temputure_show()
{
	if(Temp_count ==0)
	{		
			temperature = DS18B20_Get_Temp() / 10	;
			temperature=temperature|0x0E00;							  	// 12λ���ݷ��������¶�ȡ�¶�����
			MY_Init ();																			//������ʱ��
	}
			OLED_ShowNum (50,4,temperature,2,16);
}

//����adc
//void test_change()
//{			
//	HAL_GPIO_WritePin (GPIOF ,GPIO_PIN_9 ,GPIO_PIN_RESET );
//	static int i;
//	for(i=0;i<1024;i++)
//	{
//		printf ("%d\r\n",My_ADC_data);
//	}
//}

int fputc(int ch,FILE*f)
{
	HAL_UART_Transmit(&huart1,(uint8_t*)&ch,1,0xffff);
	return ch;
}
