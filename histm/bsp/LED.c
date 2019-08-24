#include "LED.h"

/* extern parameters */

void bsp_HiSTM_LED_init(void)
{
	GPIO_InitTypeDef  gpio_init_struct;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	gpio_init_struct.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_10;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &gpio_init_struct);
	GPIOB->ODR |= (1 << 2) | (1 << 10);
}

