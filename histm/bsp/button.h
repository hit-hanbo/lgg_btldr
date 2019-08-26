#ifndef BUTTON_H_
#define BUTTON_H_

#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "scp.h"
#include "btldr.h"

#define  BSP_HiSTM_BTN_A_PORT   GPIOC
#define  BSP_HiSTM_BTN_A_PIN    GPIO_Pin_13

#define  BSP_HiSTM_BTN_B_PORT   GPIOC
#define  BSP_HiSTM_BTN_B_PIN    GPIO_Pin_14

#define  BSP_HiSTM_BTN_C_PORT   GPIOC
#define  BSP_HiSTM_BTN_C_PIN    GPIO_Pin_15

#define  BSP_HiSTM_BTN_D_PORT   GPIOD
#define  BSP_HiSTM_BTN_D_PIN    GPIO_Pin_2

void bsp_HiSTM_button_init_IT(void);


#endif

