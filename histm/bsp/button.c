#include "button.h"
#include "arm_math.h"

extern uint8_t no_jump_flag;

void bsp_HiSTM_button_init_IT(void)
{
	GPIO_InitTypeDef  gpio_init_struct;
	EXTI_InitTypeDef  exti_init_struct;
	NVIC_InitTypeDef  nvic_init_struct;

	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB2PeriphClockCmd(RCC_APB2Periph_EXTIT, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	gpio_init_struct.GPIO_Pin = BSP_HiSTM_BTN_A_PIN;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_2MHz;

	GPIO_Init(BSP_HiSTM_BTN_A_PORT, &gpio_init_struct);
	gpio_init_struct.GPIO_Pin = BSP_HiSTM_BTN_B_PIN;
	GPIO_Init(BSP_HiSTM_BTN_B_PORT, &gpio_init_struct);
	gpio_init_struct.GPIO_Pin = BSP_HiSTM_BTN_C_PIN;
	GPIO_Init(BSP_HiSTM_BTN_C_PORT, &gpio_init_struct);
	gpio_init_struct.GPIO_Pin = BSP_HiSTM_BTN_D_PIN;
	GPIO_Init(BSP_HiSTM_BTN_D_PORT, &gpio_init_struct);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource2);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource14);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource15);

	exti_init_struct.EXTI_Line = EXTI_Line2 | EXTI_Line13 | EXTI_Line14 | EXTI_Line15;
	exti_init_struct.EXTI_LineCmd = ENABLE;
	exti_init_struct.EXTI_Mode = EXTI_Mode_Interrupt;
	exti_init_struct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&exti_init_struct);

	EXTI_ClearITPendingBit(EXTI_Line2);
	EXTI_ClearITPendingBit(EXTI_Line13);
	EXTI_ClearITPendingBit(EXTI_Line14);
	EXTI_ClearITPendingBit(EXTI_Line15);

	nvic_init_struct.NVIC_IRQChannel = EXTI2_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 5;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);
	nvic_init_struct.NVIC_IRQChannel = EXTI15_10_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 5;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

}

void EXTI2_IRQHandler(void)
{
	EXTI_ClearITPendingBit(EXTI_Line2);
	/* key D callback */
}

void EXTI15_10_IRQHandler(void)
{
	/* key A callback */
	if(EXTI_GetITStatus(EXTI_Line13))
	{
		EXTI_ClearITPendingBit(EXTI_Line13);
		//  do something
		no_jump_flag = 1;
	}
	/* key B callback */
	else if(EXTI_GetITStatus(EXTI_Line14))
	{
		EXTI_ClearITPendingBit(EXTI_Line14);
		//  do something
		SysTick->CTRL ^= (1 << 0);
		no_jump_flag ^= 1;
	}
	/* key C callback */
	else if(EXTI_GetITStatus(EXTI_Line15))
	{
		EXTI_ClearITPendingBit(EXTI_Line15);
		//  do something
	}
}

