#include "spwm_calculator.h"
#include "arm_common_tables.h"

/*
 *     HiSTM SPWM calculate library
 *     by. LinGunGun
 *     2019.7.29
 * */

/* SPWM parameters */
uint16_t HiSTM_SPWM_sin_freq = 50;
uint16_t HiSTM_SPWM_Mr = 500;
float32_t HiSTM_SPWM_Ma = 0.8;


/* TIM parameters */
uint32_t HiSTM_TIM_CLK = 90000000;
uint16_t HiSTM_TIM_ARR_1;

/* Sine table holder */
uint16_t HiSTM_SPWM_Table_C[1000] = { 0 };

uint16_t HiSTM_SPWM_Table_UVW[1500] = { 0 };

void HiSTM_SPWM_bipolar_calculate(void)
{
	uint16_t i;

	HiSTM_TIM_ARR_1 = HiSTM_TIM_CLK / HiSTM_SPWM_sin_freq / HiSTM_SPWM_Mr;
	for(i=0; i<HiSTM_SPWM_Mr; i++)
	{
		HiSTM_SPWM_Table_C[i] = (1 + HiSTM_SPWM_Ma*arm_sin_f32(2*pi* i/HiSTM_SPWM_Mr)) * (HiSTM_TIM_ARR_1) / 2;
	}
}

void HiSTM_SPWM_3phase_calculate(void)
{
	uint16_t i;

	HiSTM_TIM_ARR_1 = HiSTM_TIM_CLK / HiSTM_SPWM_sin_freq / HiSTM_SPWM_Mr;
	for(i=0; i<HiSTM_SPWM_Mr; i++)
	{
		HiSTM_SPWM_Table_UVW[3*i    ] = (1.0 + HiSTM_SPWM_Ma*arm_sin_f32(2*pi* ((float32_t)i/HiSTM_SPWM_Mr          ))) * (HiSTM_TIM_ARR_1) / 2;
		HiSTM_SPWM_Table_UVW[3*i + 1] = (1.0 + HiSTM_SPWM_Ma*arm_sin_f32(2*pi* ((float32_t)i/HiSTM_SPWM_Mr + 2.0/3.0))) * (HiSTM_TIM_ARR_1) / 2;
		HiSTM_SPWM_Table_UVW[3*i + 2] = (1.0 + HiSTM_SPWM_Ma*arm_sin_f32(2*pi* ((float32_t)i/HiSTM_SPWM_Mr - 2.0/3.0))) * (HiSTM_TIM_ARR_1) / 2;
	}
	return;
}
