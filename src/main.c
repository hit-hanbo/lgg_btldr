#include "main.h"
typedef  void (*pFunction)(void);

uint8_t str1[100], str2[100];

/*
 *         main program
 * */
int main(void)
{
	uint32_t tick_start = 0;
	uint32_t tick_elips = 0;
	pFunction p_app = NULL;

	/* MCU init */
	HiSTM_SysTick_init();

	/* bsp init */
	HiSTM_SPI1_Init();
	HiSTM_SCP_init();
	HiSTM_SCP_clear(0x0000);
	bsp_HiSTM_LED_init();
	bsp_HiSTM_button_init_IT();

	HiSTM_SCP_display_string(0,0,"LGG bootloader",HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF,0x0000);
	HiSTM_SCP_display_string(0,80,"press A->DFU",HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF,0x0000);
	HiSTM_SCP_display_string(0,100,"press B->pause",HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF,0x0000);


	tick_start = HiSTM_get_system_ticks();
	/* wait user to select mode */
	while(tick_elips < 8000)
	{
		tick_elips = HiSTM_get_system_ticks() - tick_start;
		sprintf(str1, "%d", (uint8_t)(8-tick_elips/1000));
		HiSTM_SCP_display_string(0,40,str1,HiSTM_SCP_CHARMODE_NOOVERLYING,0xFFFF,0x0000);
	}

	/* prepare to jump to APP */
	/* 1. disable global IRQ */
	SysTick->CTRL &= ~(1 << 0);
	__disable_irq();
	SPI_DeInit(SPI1);
	RCC_DeInit();

	/* 2. set MSP*/
	__set_MSP(*(volatile uint32_t*)0x08010000);

	/* 3. jump to APP, bye-bye*/
	p_app = (void(*)())*(volatile uint32_t *)(0x08010000 + 4);
	SCB->VTOR = 0x08010000;
	p_app();


	return 0;
}

