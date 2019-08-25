#include "adc.h"
#include "stdlib.h"

uint16_t ADC_sample_regular[16] = { 0 };

void HiSTM_ADC_Init(void)
{
	ADC_InitTypeDef  ADC_Init_struct;
	ADC_CommonInitTypeDef ADCC_init_struct;
	DMA_InitTypeDef  DMA_Init_Struct;
	GPIO_InitTypeDef GPIO_Init_Struct;
	NVIC_InitTypeDef nvic_init_struct;

	/* enable clks */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

	/* gpio configure */
	/* chanel 0 ~ 3 */
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init_Struct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_Struct);

	/* channel 10 ~ 15 */
	GPIO_Init_Struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |\
			GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_Init_Struct.GPIO_Mode = GPIO_Mode_AN;
	GPIO_Init(GPIOC, &GPIO_Init_Struct);

	/* configure ADC1 DMA */
	DMA_Init_Struct.DMA_Channel = DMA_Channel_0;
	DMA_Init_Struct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_Init_Struct.DMA_Mode = DMA_Mode_Circular;
	DMA_Init_Struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_Init_Struct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_Init_Struct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_Init_Struct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
	DMA_Init_Struct.DMA_Memory0BaseAddr = (uint32_t)ADC_sample_regular;
	DMA_Init_Struct.DMA_BufferSize = 16;
	DMA_Init_Struct.DMA_Priority = DMA_Priority_High;
	DMA_Init_Struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_Init_Struct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_Init_Struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_Init_Struct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(DMA2_Stream0, &DMA_Init_Struct);

	DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE);
	DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TC);

	nvic_init_struct.NVIC_IRQChannel = DMA2_Stream0_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 0;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

	/* start DMA */
	DMA_Cmd(DMA2_Stream0, ENABLE);

	/* configure ADC common */
	ADCC_init_struct.ADC_DMAAccessMode = ADC_DMAAccessMode_1;
	ADCC_init_struct.ADC_Mode = ADC_Mode_Independent;
	ADCC_init_struct.ADC_Prescaler = ADC_Prescaler_Div4;
	ADCC_init_struct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
	ADC_CommonInit(&ADCC_init_struct);

	ADC_Init_struct.ADC_Resolution = ADC_Resolution_12b;
	ADC_Init_struct.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_Init_struct.ADC_ScanConvMode = ENABLE;
	ADC_Init_struct.ADC_ContinuousConvMode = DISABLE;
	ADC_Init_struct.ADC_NbrOfConversion = 16;
	ADC_Init_struct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_Init_struct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;
	ADC_Init(ADC1, &ADC_Init_struct);
	ADC1->CR2 &= ~(1 << 11);

	/* configure ADC regular channel */
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 2 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 3 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 4 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 5 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 6 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 7 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 8 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 9 , ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 10, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 11, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 12, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 13, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 14, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_12, 15, ADC_SampleTime_15Cycles);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_13, 16, ADC_SampleTime_15Cycles);

	ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
	ADC_DMACmd(ADC1, ENABLE);

	/* configure ADC injected channel */


	/* start ADC & regular channel */
	ADC_Cmd(ADC1, ENABLE);
}


void DMA2_Stream0_IRQHandler(void)
{
	if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0) == SET)
	{
		DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);

	}
}

