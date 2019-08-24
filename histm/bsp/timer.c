#include "timer.h"

uint32_t HiSTM_system_ticks = 0;

/*    Configure TIM1 CH1, CH1N, CH2, CH2N
 *
 */
void HiSTM_Advance_TIM1_init(uint16_t ARR_1)
{
	TIM_TimeBaseInitTypeDef  TIM_Base_init_struct;
	TIM_BDTRInitTypeDef      TIM_BDTR_init_struct;
	TIM_OCInitTypeDef        TIM_OC_init_struct;
	GPIO_InitTypeDef         GPIO_Init_struct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	TIM_Base_init_struct.TIM_Prescaler = 1 - 1;
	TIM_Base_init_struct.TIM_ClockDivision = 0;
	TIM_Base_init_struct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_Base_init_struct.TIM_RepetitionCounter = 1;
	TIM_Base_init_struct.TIM_Period = ARR_1 - 1;
	TIM_TimeBaseInit(TIM1, &TIM_Base_init_struct);

	TIM_BDTR_init_struct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTR_init_struct.TIM_OSSIState = TIM_OSSIState_Disable;
	TIM_BDTR_init_struct.TIM_OSSRState = TIM_OSSRState_Disable;
	TIM_BDTR_init_struct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTR_init_struct.TIM_DeadTime =  0x30;
	TIM_BDTRConfig(TIM1, &TIM_BDTR_init_struct);

	TIM_OC_init_struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_init_struct.TIM_Pulse = 0;
	TIM_OC_init_struct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC_init_struct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OC_init_struct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_init_struct.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC_init_struct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC_init_struct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM1, &TIM_OC_init_struct);
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM1, &TIM_OC_init_struct);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM1, &TIM_OC_init_struct);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);

	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOAEN, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOBEN, ENABLE);
	GPIO_Init_struct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_Init_struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_Init_struct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);

	GPIO_Init_struct.GPIO_Pin = GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOB, &GPIO_Init_struct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource13, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource14, GPIO_AF_TIM1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM1);

	//  update event trigger output
	TIM_SelectOutputTrigger(TIM1, TIM_TRGOSource_Update);
}

/*    Configure TIM8 CH1, CH1N, CH2, CH2N, CH3, CH3N
 *
 */
void HiSTM_Advance_TIM8_init(uint16_t ARR_1)
{
	TIM_TimeBaseInitTypeDef  TIM_Base_init_struct;
	TIM_BDTRInitTypeDef      TIM_BDTR_init_struct;
	TIM_OCInitTypeDef        TIM_OC_init_struct;
	GPIO_InitTypeDef         GPIO_Init_struct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	TIM_Base_init_struct.TIM_Prescaler = 1 - 1;
	TIM_Base_init_struct.TIM_ClockDivision = 0;
	TIM_Base_init_struct.TIM_CounterMode = TIM_CounterMode_CenterAligned1;
	TIM_Base_init_struct.TIM_RepetitionCounter = 1;
	TIM_Base_init_struct.TIM_Period = ARR_1 - 1;
	TIM_TimeBaseInit(TIM8, &TIM_Base_init_struct);

	TIM_BDTR_init_struct.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;
	TIM_BDTR_init_struct.TIM_OSSIState = TIM_OSSIState_Disable;
	TIM_BDTR_init_struct.TIM_OSSRState = TIM_OSSRState_Disable;
	TIM_BDTR_init_struct.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
	TIM_BDTR_init_struct.TIM_DeadTime =  0x30;
	TIM_BDTRConfig(TIM8, &TIM_BDTR_init_struct);

	TIM_OC_init_struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OC_init_struct.TIM_Pulse = 0;
	TIM_OC_init_struct.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OC_init_struct.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OC_init_struct.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OC_init_struct.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OC_init_struct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OC_init_struct.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC1Init(TIM8, &TIM_OC_init_struct);
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM8, &TIM_OC_init_struct);
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM8, &TIM_OC_init_struct);
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable);

	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOAEN, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOBEN, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1ENR_GPIOCEN, ENABLE);

	GPIO_Init_struct.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init_struct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_struct.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_struct.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_Init_struct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_TIM8);

	GPIO_Init_struct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOB, &GPIO_Init_struct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_TIM8);

	GPIO_Init_struct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_Init_struct);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);

	//  update event trigger output
	TIM_SelectOutputTrigger(TIM8, TIM_TRGOSource_Update);
}


/*    Configure SysTick timer for 1kHz interrupt as system ticks
 *
 */
void HiSTM_SysTick_init(void)
{
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_4);
	SysTick->CTRL |= (1 << 1);
	NVIC_EnableIRQ(SysTick_IRQn);
	HiSTM_system_ticks = 0;
	SysTick->LOAD = 18000;
	SysTick->CTRL |= (1 << 0);
}


/*    IRQHandler for SysTick IRQn
 *
 */
void SysTick_Handler(void)
{
	HiSTM_system_ticks ++;
}

/*    Get current system ticks
 *
 */
uint32_t HiSTM_get_system_ticks(void)
{
	return HiSTM_system_ticks;
}

/*    a delay function (blocked)
 *
 */
void HiSTM_Delay(uint32_t ms)
{
	uint32_t tick_start = HiSTM_get_system_ticks();
	while(HiSTM_get_system_ticks() - tick_start < ms)
	{

	}
}

void HiSTM_Delay_ticks(uint32_t ms)
{
	uint32_t systick_val = ms * 25000;
	//  disable systick
	SysTick->CTRL &= ~(1 << 0);
	SysTick->VAL = 0;
	//  set value
	SysTick->LOAD = systick_val;
	//  enable systick
	SysTick->CTRL |= (1 << 0);
	//  wait for delay
	while(SysTick->VAL != 0);
}

/*    Configure TIM2 as TRGO timer
 *
 */
void HiSTM_General_TIM2_init(uint16_t ARR)
{
	TIM_TimeBaseInitTypeDef  TIM_Base_init_struct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_Base_init_struct.TIM_Period = ARR - 1;
	TIM_Base_init_struct.TIM_Prescaler = 100 - 1;
	TIM_Base_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_Base_init_struct.TIM_RepetitionCounter = 0;
	TIM_Base_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_Base_init_struct);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	TIM_SelectOutputTrigger(TIM2, TIM_TRGOSource_Update);
}

void HiSTM_slave_TIM9_init(void)
{
	TIM_TimeBaseInitTypeDef tim_base_init_struct;
	NVIC_InitTypeDef		nvic_init_struct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, ENABLE);
	tim_base_init_struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim_base_init_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	tim_base_init_struct.TIM_Period = 100;
	tim_base_init_struct.TIM_Prescaler = 0x0000;
	tim_base_init_struct.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM9, &tim_base_init_struct);
	TIM_SelectMasterSlaveMode(TIM9, TIM_MasterSlaveMode_Enable);
	TIM_SelectSlaveMode(TIM9, TIM_SlaveMode_External1);
	TIM_SelectInputTrigger(TIM9, TIM_TS_ITR0);

	TIM_ITConfig(TIM9, TIM_IT_Update, ENABLE);
	TIM_ClearITPendingBit(TIM9, TIM_IT_Update);

	nvic_init_struct.NVIC_IRQChannel = TIM1_BRK_TIM9_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = ENABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 6;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

	TIM9->CR1 |= (1 << 0);
}

void HiSTM_slave_TIM9_set_period(uint16_t arr_1)
{
	TIM9->ARR = arr_1 - 1;
}

void TIM1_BRK_TIM9_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM9, TIM_IT_Update) == SET)
	{
		TIM_ClearITPendingBit(TIM9, TIM_IT_Update);
		//  do something
	}
}

