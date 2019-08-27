#include "main.h"

uint8_t bl_status = 0;
/*
 *         main program
 * */
int main(void)
{
	uint32_t tick_start = 0;
	uint32_t tick_elips = 0;

	/* MCU init */
	HiSTM_SysTick_init();

	/* bsp init */
	HiSTM_SPI1_Init();
	HiSTM_SCP_init();
	HiSTM_SCP_clear(0x0000);
	bsp_HiSTM_LED_init();
	bsp_HiSTM_button_init_IT();
	HiSTM_USART1_init();
	HiSTM_USART1_tramsmit("[0] system init\r\n", 17);


	/* show tips */
	HiSTM_SCP_display_string(0,0,"LGG bootloader",HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF,0x0000);
	HiSTM_SCP_display_string(0,80,"press A->dfu",HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF,0x0000);
	HiSTM_SCP_display_string(0,100,"press B->btldr",HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF,0x0000);


	tick_start = HiSTM_get_system_ticks();

	/* wait user to select mode for 3s */
	while(tick_elips < 150 && bl_status == 0)
	{
		tick_elips = (HiSTM_get_system_ticks() - tick_start) / 50;
		HiSTM_SCP_display_char(tick_elips, 40, '=', HiSTM_SCP_CHARMODE_NOOVERLYING, 0xFFFF, 0x0000);
	}

	if(bl_status == 1)
		btldr_loop();
	else
		jump_to_application(0x08010000);

	return 0;
}

