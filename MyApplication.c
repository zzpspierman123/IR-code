#include "my_code.h"

/*
 *串口测试  			ok
 *ADC测试					ok 
 *二进制转化			ok
 *引脚输出				ok
 *引脚编码输出		ok
 *定时器输出
*/


//测试ADC的采集转二进制和编码
#define ADC_check  0
//实战数据发送
#define Show_real  1



//主函数中while的函数调用
void RUN()
{
#if ADC_check 
	ADC_test();
#endif
	
#if Show_real	
	temputure_show();
#endif
	
	
}

//定时器中断回调函数
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if(htim->Instance==TIM3)
	{
				ADC_test();
	}
}
