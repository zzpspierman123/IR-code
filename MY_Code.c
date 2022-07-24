#include "my_code.h"

//存ADC的采集值
uint16_t My_ADC_data;
//存二进制的转化值
uint8_t data_buff[9];
//装载温度
uint8_t temperature=0;
//计时输出温度
uint16_t Temp_count=0;
//存温度数据
uint16_t T_dat=0;
//#define change_start 1024

/*
 *开启定时器
*/
void MY_Init()
{
	
	 HAL_TIM_Base_Start_IT(&htim3);

	
}

/*
 *得到ADC的采集值、
 *将采集值转二进制
 *将二进制值进行编码输出
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
 *将一个12位的数变为8位
 *变为八位二进制后存入数组
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
		 T_dat=temperature;							  	// 12位数据发送完重新读取温度数据
   } 				  
 	data_buff[8]=(uint8_t)((T_dat&0x8000)>>15);	// 移位取出各位数据独立存储
 	T_dat=T_dat<<1 ;
  j++;	
}

/*
 *输出编码1
 *输出编码0
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
	
	//产生一个边沿，以免丢失最后一个数据
	SendOut = 1;
	delay_us(2);
	SendOut = 0;
	
} 


void temputure_show()
{
	if(Temp_count ==0)
	{		
			temperature = DS18B20_Get_Temp() / 10	;
			temperature=temperature|0x0E00;							  	// 12位数据发送完重新读取温度数据
			MY_Init ();																			//开启定时器
	}
			OLED_ShowNum (50,4,temperature,2,16);
}

//测试adc
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
