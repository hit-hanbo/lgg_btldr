#ifndef SPWM_UNIPOLAR_H_
#define SPWM_UNIPOLAR_H_

#include "stm32f4xx.h"
#include "stm32f4xx_dma.h"
#include "timer.h"

#define  SPWM_UNIPOLAR_POINTS 400

void HiSTM_SPWM_unipolar_init(void);
void HiSTM_SPWM_unipolar_TIM_DMA_init(void);
void HiSTM_SPWM_unipolar_calculate(void);
void HiSTM_SPWM_unipolar_cmd(FunctionalState NewState);
void DMA2_Stream5_IRQHandler(void);


#endif

