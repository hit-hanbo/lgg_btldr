#include "dac.h"


void HiSTM_DAC_init(void)
{
	DAC_InitTypeDef  dac_init_struct;
	GPIO_InitTypeDef gpio_init_struct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	gpio_init_struct.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOA, &gpio_init_struct);

	dac_init_struct.DAC_Trigger = DAC_Trigger_T8_TRGO;
	dac_init_struct.DAC_WaveGeneration = DAC_WaveGeneration_None;
	dac_init_struct.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_Init(DAC_Channel_1, &dac_init_struct);
	DAC_Init(DAC_Channel_2, &dac_init_struct);

	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_Cmd(DAC_Channel_2, ENABLE);
}
