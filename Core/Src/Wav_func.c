/*
 * Wav_func.c
 *
 *  Created on: Mar 27, 2025
 *      Author: rafael
 */
#include "Wav_func.h"


#define PI 						3.14159
#define POWER_CONV				354/3.3
#define SQUARE_ROOT_2   1.414213



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
	memset(teste,0,sizeof(teste));
	 for (int i = 0; i < samples; i++) {
	        HAL_ADC_Start(hadc);
	        HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
	        buffer[i] = HAL_ADC_GetValue(hadc);
	        teste[i] = ((float)buffer[i] * 3.3 / 0xFFF);
	        convValue[i]=teste[i];
	        delay_us(50);
	 }

	 return convValue[samples - 1]; // Retorna o último valor convertido
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
        printf("Num %d : %.2f\n\r", i, convValue[i]);
    }
}


float get_rms(float peak)
{
	return peak/SQUARE_ROOT_2;
}
