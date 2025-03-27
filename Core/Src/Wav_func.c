/*
 * Wav_func.c
 *
 *  Created on: Mar 27, 2025
 *      Author: rafael
 */
#include "Wav_func.h"
#define TIMCLOCK		84000000
#define PRESCALAR 		84
uint32_t IC_VAL1=0;
uint32_t IC_VAL2=0;
uint32_t diff=0;
uint8_t is_Fist=0;
float frequency=0;

void set_sinoid(uint32_t *sine_value, int size)
{
	for(int i=0;i<size;i++)
	{
		sine_value[i]=((sin(i*2*PI/size)+1)*((0xFFF +1)/2));
	}
}
float get_sinoid(uint32_t *buffer,float * convValue, ADC_HandleTypeDef *hadc, int samples)
{
	float teste[samples];
	 for (int i = 0; i < samples; i++) {
	        HAL_ADC_Start(hadc);
	        HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	        buffer[i] = HAL_ADC_GetValue(hadc);
	        teste[i] = ((float)buffer[i] * 3.3 / 0xFFF);
	        convValue[i]=POWER_CONV*teste[i];
	        delay_us(50);
	 }

	 return convValue[samples - 1]; // Retorna o último valor convertido


}


void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		if(is_Fist== 0)
		{
			IC_VAL1= HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			is_Fist=1;
		}
		else
		{
			IC_VAL2 = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
			if(IC_VAL2> IC_VAL1)
			{
				diff  = IC_VAL2-IC_VAL1;
			}else if(IC_VAL1>IC_VAL2)
			{
				diff = (0xffff-IC_VAL1)+ IC_VAL2;
			}
			float refClock = TIMCLOCK/(PRESCALAR);
			frequency = refClock/diff;
			__HAL_TIM_SET_COUNTER(htim,0);
			is_Fist=0;
		}
	}

}


float get_frequency()
{
	return frequency;
}
float find_amp(float *convValue, int samples)
{
	float max=0;
    for (int i = 0; i < samples; i++) {
    	if(convValue[i]>max) {max= convValue[i];}

    }
    return max;
}

void print_F32_arr(float *convValue, int samples) {
    for (int i = 0; i < samples; i++) {
        printf("Num %d : %.2f\n", i, convValue[i]);
    }
}
