/*
 *     histm library for Unipolar SPWM signal generation
 *
 * */

#ifdef SPWM_UNIPOLAR
	#include "spwm_table.h"
#else
	#define SPWM_table_unipolar_50Hz 0
#endif

#include "spwm_unipolar.h"

/* Parameters */


void HiSTM_SPWM_unipolar_init(void)
{
	HiSTM_Advance_TIM1_init(2500);
	HiSTM_SPWM_unipolar_TIM_DMA_init();
}

void HiSTM_SPWM_unipolar_TIM_DMA_init(void)
{
	DMA_InitTypeDef   dma_init_struct;
	NVIC_InitTypeDef  nvic_init_struct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	/* DMA common config */
	dma_init_struct.DMA_BufferSize = SPWM_UNIPOLAR_POINTS;
	dma_init_struct.DMA_Channel = DMA_Channel_6;
	dma_init_struct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	dma_init_struct.DMA_Mode = DMA_Mode_Normal;

	/* DMA data transfer config */
	dma_init_struct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init_struct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	TIM_DMAConfig(TIM1, TIM_DMABase_CCR1, TIM_DMABurstLength_1Transfer);
	TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);

	/* DMA address config */
	dma_init_struct.DMA_PeripheralBaseAddr = (uint32_t)&TIM1->DMAR;
	dma_init_struct.DMA_Memory0BaseAddr = (uint32_t)SPWM_table_unipolar_50Hz;

	/* DMA FIFO config */
	dma_init_struct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma_init_struct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;

	/* DMA Priority */
	dma_init_struct.DMA_Priority = DMA_Priority_High;
	DMA_Init(DMA2_Stream5, &dma_init_struct);

	/* DMA interrupt */
	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);
	DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TC);

	nvic_init_struct.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 1;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

}

void HiSTM_SPWM_unipolar_calculate(void)
{

}

void HiSTM_SPWM_unipolar_cmd(FunctionalState NewState)
{

}

//void DMA2_Stream5_IRQHandler(void)
//{
//	if(DMA_GetITStatus(DMA2_Stream5, DMA_IT_TC) == SET)
//	{
//		DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TC);
//		//  switch SPWM output channel
//
//
//	}
//}

