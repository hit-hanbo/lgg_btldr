#ifndef USART_H_
#define USART_H_

#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

#define TXERR_txDMA_BUSY  0xFF

/* functions */
void HiSTM_USART1_init(void);
uint8_t HiSTM_USART1_tramsmit(uint8_t* data, uint16_t length);


#endif

