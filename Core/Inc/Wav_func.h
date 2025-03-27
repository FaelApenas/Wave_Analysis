#ifndef WAV_FUNC_H
#define WAV_FUNC_H

#include "main.h"

void set_sinoid(uint32_t *sine_value, int size);

float get_sinoid(uint32_t *buffer,float * convValue, ADC_HandleTypeDef *hadc, int samples);
float find_amp(float *convValue, int samples);
void print_F32_arr(float *convValue, int samples);



float get_frequency();

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);

#endif
