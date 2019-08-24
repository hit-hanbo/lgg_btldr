#ifndef LED_H_
#define LED_H_

#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

#define  BSP_HiSTM_LED_R_PORT  GPIOB
#define  BSP_HiSTM_LED_R_PIN   GPIO_Pin_2
#define  BSP_HiSTM_LED_G_PORT  GPIOB
#define  BSP_HiSTM_LED_G_PIN   GPIO_Pin_10

#define  HiSTM_LED_R_ON        BSP_HiSTM_LED_R_PORT->ODR &= ~(BSP_HiSTM_LED_R_PIN)
#define  HiSTM_LED_R_OFF       BSP_HiSTM_LED_R_PORT->ODR |=  (BSP_HiSTM_LED_R_PIN)
#define  HiSTM_LED_R_TOGGLE    BSP_HiSTM_LED_R_PORT->ODR ^=  (BSP_HiSTM_LED_R_PIN)
#define  HiSTM_LED_G_ON        BSP_HiSTM_LED_G_PORT->ODR &= ~(BSP_HiSTM_LED_G_PIN)
#define  HiSTM_LED_G_OFF       BSP_HiSTM_LED_G_PORT->ODR |=  (BSP_HiSTM_LED_G_PIN)
#define  HiSTM_LED_G_TOGGLE    BSP_HiSTM_LED_G_PORT->ODR ^=  (BSP_HiSTM_LED_G_PIN)


void bsp_HiSTM_LED_init(void);

#endif

