#ifndef BTLDR_H_
#define BTLDR_H_

#include "stdlib.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "arm_math.h"
#include "usart.h"

typedef  void (*pFunction)(void);

void jump_to_application(uint32_t app_addr);

#endif

