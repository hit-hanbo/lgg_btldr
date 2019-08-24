#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"

#define  HiSTM_SPI_TX_OK     0x00
#define  HiSTM_SPI_TX_ERROR  0xFF

void HiSTM_SPI1_Init(void);
uint8_t HiSTM_SPI1_transmit_data(uint8_t data);
void HiSTM_Delay(uint32_t ms);



#endif
