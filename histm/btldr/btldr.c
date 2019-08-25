#include "btldr.h"

uint8_t cmd_buffer[1024] = { 0 };
extern  uint32_t usart_rx_status;

static int8_t HiSTM_strcmp(uint8_t* a, uint8_t* b, uint32_t length);

/*
 *     jump to user application
 *     please make sure your app address is available
 * */
void jump_to_application(uint32_t app_addr)
{
	pFunction p_app = NULL;

	/* prepare to jump to APP */
	/* 1. disable global IRQ */
	__disable_irq();
	RCC_DeInit();

	/* 2. set MSP pointer */
	__set_MSP(*(volatile uint32_t*)app_addr);

	/* 3. jump to APP, bye-bye*/
	p_app = (void(*)())*(volatile uint32_t *)(app_addr + 4);
	SCB->VTOR = 0x08010000;
	p_app();
}

/*
 *       bootloader function
 * */
void btldr_banner(void)
{
	HiSTM_USART1_tramsmit("hi BootLoader\r\n", 15);
}

/*
 * 		internal functions
 *  */
/* flash option: erase sector */
void __btldr_erase(uint32_t address, uint32_t block_size)
{

}

/* flash option: write sector */
void __btldr_write_block(uint32_t address, uint32_t* data, uint32_t length)
{

}

/* exit bootloader */
void __btldr_exit(void)
{
	jump_to_application(0x08010000);
}

/* bootloader User Interface */
void btldr_loop(void)
{
	uint32_t temp0, temp1, temp2;
	uint8_t  tmp_str1[20], tmp_str2[20], tmp_str3[20];

	/* show banner */
	btldr_banner();
	while(1)
	{
		/* print a > */
		HiSTM_USART1_tramsmit(">", 1);
		/* wait for command */
		while((usart_rx_status & (1 << 31)) == 0);
		/* get string length */
		if ( HiSTM_strcmp("erase", cmd_buffer, 5) == 0 )
		{
			//  erase command
			/*  1, get address or app */
			if(HiSTM_strcmp("app", &cmd_buffer[6], 3) == 0)
			{
				//  erase app
			}
			else
			{
				temp1 = strtol(tmp_str1, &tmp_str2, 16);
				temp2 = strtol(&tmp_str2[1], NULL, 10);
				__btldr_erase(temp1, temp2);
			}
		}
		else if( HiSTM_strcmp("exit", cmd_buffer, 4) == 0 )
		{
			//  exit command
			jump_to_application(0x08010000);
		}
		else if(HiSTM_strcmp("write", cmd_buffer, 5) == 0)
		{
			//  write command
		}
		else if(HiSTM_strcmp("restart", cmd_buffer, 7) == 0)
		{
			//  restart command
			__disable_irq();
			NVIC_SystemReset();
		}
		else
		{
			//  unknown command
			HiSTM_USART1_tramsmit("Unknown Command\r\n", 17);
		}
	}
}

static int8_t HiSTM_strcmp(uint8_t* a, uint8_t* b, uint32_t length)
{
	uint32_t i;
	for(i=0; i<length; i++)
	{
		if(a[i] != b[i])
			return (a[i] - b[i]);
	}
	return 0;
}
