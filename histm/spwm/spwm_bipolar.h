#ifndef SPWM_BIPOLAR_H_
#define SPWM_BIPOLAR_H_

#include "stm32f4xx.h"
#include "stm32f4xx_dma.h"
#include "timer.h"

#define  SPWM_BIPOLAR_POINTS 400

void HiSTM_SPWM_bipolar_init(void);
void HiSTM_SPWM_bipolar_TIM_DMA_init(void);
void HiSTM_SPWM_bipolar_cmd(FunctionalState NewState);
void decrease_f(void);

#endif
