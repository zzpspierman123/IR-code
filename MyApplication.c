#include "my_code.h"

/*
 *���ڲ���  			ok
 *ADC����					ok 
 *������ת��			ok
 *�������				ok
 *���ű������		ok
 *��ʱ�����
*/


//����ADC�Ĳɼ�ת�����ƺͱ���
#define ADC_check  0
//ʵս���ݷ���
#define Show_real  1



//��������while�ĺ�������
void RUN()
{
#if ADC_check 
	ADC_test();
#endif
	
#if Show_real	
	temputure_show();
#endif
	
	
}

//��ʱ���жϻص�����
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		if(htim->Instance==TIM3)
	{
				ADC_test();
	}
}
