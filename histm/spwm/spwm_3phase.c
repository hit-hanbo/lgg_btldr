/*
 *     histm library for 3phase SPWM signal generation
 *
 * */
#include "spwm_3phase.h"

/* Parameters */
extern uint16_t HiSTM_TIM_ARR_1;
extern uint16_t HiSTM_SPWM_Table_C[1000];
extern uint16_t HiSTM_SPWM_Mr;
extern uint16_t HiSTM_SPWM_Table_UVW[3000];


void HiSTM_SPWM_3phase_init(void)
{
	HiSTM_Advance_TIM1_init(HiSTM_TIM_ARR_1);
	HiSTM_SPWM_3phase_TIM_DMA_init();
}

void HiSTM_SPWM_3phase_TIM_DMA_init(void)
{
	DMA_InitTypeDef  dma_init_struct;
	NVIC_InitTypeDef nvic_init_struct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	/* DMA common config */
	dma_init_struct.DMA_BufferSize = HiSTM_SPWM_Mr * 3;
	dma_init_struct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	dma_init_struct.DMA_Channel = DMA_Channel_6;
	dma_init_struct.DMA_Mode = DMA_Mode_Circular;

	/* DMA data transfer config */
	dma_init_struct.DMA_MemoryBurst = DMA_MemoryBurst_INC4;
	dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init_struct.DMA_PeripheralBurst = DMA_PeripheralBurst_INC4;
	dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	TIM_DMAConfig(TIM1, TIM_DMABase_CCR1, TIM_DMABurstLength_3Transfers);
	TIM_DMACmd(TIM1, TIM_DMA_Update, ENABLE);

	/* DMA address config */
	dma_init_struct.DMA_PeripheralBaseAddr = (uint32_t)&TIM1->DMAR;
	dma_init_struct.DMA_Memory0BaseAddr = (uint32_t)HiSTM_SPWM_Table_C;

	/* DMA FIFO config */
	dma_init_struct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma_init_struct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;

	/* DMA Priority */
	dma_init_struct.DMA_Priority = DMA_Priority_VeryHigh;
	DMA_Init(DMA2_Stream5, &dma_init_struct);

	/* DMA interrupt */
	DMA_ITConfig(DMA2_Stream5, DMA_IT_TC, ENABLE);
	DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TC);
	nvic_init_struct.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = DISABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

}

void HiSTM_SPWM_3phase_cmd(FunctionalState NewState)
{
	if(NewState != ENABLE)
	{
		//  disable TIM1
		TIM1->CR1 &= ~(1 << 0);
		TIM1->CNT  = 0x00000000;
		//  disable DMA
		DMA2_Stream5->CR &= ~(1 << 0);
	}
	else
	{
		//  enable DMA
		DMA2_Stream5->NDTR = HiSTM_SPWM_Mr * 3;
		DMA2_Stream5->M0AR = (uint32_t)HiSTM_SPWM_Table_UVW;
		DMA2_Stream5->PAR = (uint32_t)&TIM1->DMAR;
		DMA2_Stream5->CR |= (1 << 0);
		//  enable TIM1
		TIM1->ARR  = HiSTM_TIM_ARR_1 - 1;
		TIM1->CNT  = 0x00000000;
		TIM1->CR1 |= (1 << 0);
	}
}

