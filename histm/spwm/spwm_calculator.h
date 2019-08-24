#ifndef SPWM_CALCULATOR_H_
#define SPWM_CALCULATOR_H_

/* header file for: spwm_calculator.c */

#include "arm_math.h"
#include "stm32f4xx.h"

#define pi 3.1415927

void HiSTM_SPWM_bipolar_calculate(void);
void HiSTM_SPWM_3phase_calculate(void);


#endif

