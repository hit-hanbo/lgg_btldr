#ifndef BTLDR_H_
#define BTLDR_H_

#include "stdlib.h"
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_flash.h"
#include "arm_math.h"
#include "usart.h"

typedef  void (*pFunction)(void);

#define BTLDR_ERR_FLASH_BUSY            0xFF
#define BTLDR_ERR_FLASH_NO_PREMISSION   0xFE

void jump_to_application(uint32_t app_addr);
uint8_t __btldr_erase(uint32_t sector);
uint8_t __btldr_write_byte(uint32_t address, uint8_t* data, uint32_t length);
void btldr_loop(void);

#endif

