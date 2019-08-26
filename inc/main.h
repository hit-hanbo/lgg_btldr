#ifndef MAIN_H_
#define MAIN_H_

/*  include file for  **main.c**  */

/* compiler headers */
#include "stdio.h"
#include "stdlib.h"

/* stm32 spl headers */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"

/* histm headers */
#include "adc.h"
#include "dac.h"
#include "timer.h"
#include "scp.h"
#include "LED.h"
#include "button.h"
#include "btldr.h"
#include "usart.h"

/* debug interface */
#include "stm32f4xx_usart.h"


/* static functions */
void HiSTM_USART_Init(void);

#endif


