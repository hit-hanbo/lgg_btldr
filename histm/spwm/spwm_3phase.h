#ifndef SPWM_3PHASE_H_
#define SPWM_3PHASE_H_

#include "stm32f4xx.h"
#include "stm32f4xx_dma.h"
#include "timer.h"

void HiSTM_SPWM_3phase_init(void);
void HiSTM_SPWM_3phase_TIM_DMA_init(void);
void HiSTM_SPWM_3phase_cmd(FunctionalState NewState);

#endif

