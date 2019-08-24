#ifndef TIMER_H_
#define TIMER_H_

#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "misc.h"


/* Options */
#define  HISTM_TIM1_PWM1_SET(X)   TIM1->CCR1 = X;
#define  HISTM_TIM1_PWM2_SET(X)   TIM1->CCR2 = X;


/* GPIO define */

void HiSTM_Advance_TIM1_init(uint16_t ARR_1);
void HiSTM_SysTick_init(void);
void HiSTM_Delay(uint32_t ms);
void HiSTM_General_TIM2_init(uint16_t ARR);
void SysTick_Handler(void);
void HiSTM_slave_TIM9_init(void);
void HiSTM_slave_TIM9_set_period(uint16_t arr_1);

uint32_t HiSTM_get_system_ticks(void);


#endif
