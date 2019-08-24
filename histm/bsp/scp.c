#include "scp.h"
#include "scp_font.h"

/*
 *   @ Description: STM32 based ST7735S LCD Controller Driverlib
 *   @ Author:      HIT-hanbo
 *   @ History:     2019-07-11  Demo
*/


/*
 *   @ Brief: transmit a byte to st7735s via SPI interface
 *   @ param: data to transmit
 */
void HiSTM_SCP_transmit_byte(uint8_t data)
{
	HiSTM_SCP_CEN_OUTL;
	//  provide your spi transmit function
	HiSTM_SPI1_transmit_data(data);
	HiSTM_SCP_CEN_OUTH;
}

/*
 *   @ Brief: transmit a REGISTER address to st7735s (write command)
 *   @ param: cmd to transmit
 */
void HiSTM_SCP_transmit_cmd(uint8_t cmd)
{
	HiSTM_SCP_DC_OUTL;
	HiSTM_SCP_transmit_byte(cmd);
}

/*
 *   @ Brief: transmit a BYTE DATA to st7735s (write data)
 *   @ param: data byte to transmit
 */
void HiSTM_SCP_transmit_data8(uint8_t data)
{
	HiSTM_SCP_DC_OUTH;
	HiSTM_SCP_transmit_byte(data);
}

/*
 *   @ Brief: transmit a HALFWORD DATA to st7735s (write data)
 *   @ param: data halfword to transmit
 */
void HiSTM_SCP_transmit_data16(uint16_t data)
{
	HiSTM_SCP_DC_OUTH;
	HiSTM_SCP_transmit_byte(data >> 8);
	HiSTM_SCP_transmit_byte(data);
}

/*
 *  @ Brief: set LCD address to option
 *  @ param: (x1, y1) - start address , (x2, y2) - stop address
 */
void HiSTM_SCP_address_set(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2)
{
#ifdef HiSTM_SCP_OP_POTRAIT
	HiSTM_SCP_transmit_cmd(0x2A);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(x1 + 2);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(x2 + 2);

	HiSTM_SCP_transmit_cmd(0x2B);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(y1 + 1);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(y2 + 1);
#endif
#ifdef HiSTM_SCP_OP_LANDSCAPE
	HiSTM_SCP_transmit_cmd(0x2A);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(x1 + 1);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(x2 + 1);

	HiSTM_SCP_transmit_cmd(0x2B);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(y1 + 2);
	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_data8(y2 + 2);
#endif
	HiSTM_SCP_transmit_cmd(0x2C);
}

/*
 *  @ Brief: init st7735s controller
 */
void HiSTM_SCP_init(void)
{
	GPIO_InitTypeDef  gpio_init_struct;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	HiSTM_SPI1_Init();

	gpio_init_struct.GPIO_Pin = HiSTM_SCP_DC_PIN;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(HiSTM_SCP_DC_PORT, &gpio_init_struct);
	HiSTM_SCP_DC_OUTH;

	gpio_init_struct.GPIO_Pin = HiSTM_SCP_RES_PIN;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(HiSTM_SCP_RES_PORT, &gpio_init_struct);
	HiSTM_SCP_RES_OUTH;

	gpio_init_struct.GPIO_Pin = HiSTM_SCP_CEN_PIN;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(HiSTM_SCP_CEN_PORT, &gpio_init_struct);
	HiSTM_SCP_CEN_OUTH;


	HiSTM_SCP_RES_OUTL;
	HiSTM_Delay(300);

	HiSTM_SCP_RES_OUTH;
	HiSTM_Delay(300);

	HiSTM_SCP_transmit_cmd(0x11);
	HiSTM_Delay(300);

	HiSTM_SCP_transmit_cmd(0xB1);
	HiSTM_SCP_transmit_data8(0x05);	HiSTM_SCP_transmit_data8(0x3C);	HiSTM_SCP_transmit_data8(0x3C);
	HiSTM_SCP_transmit_cmd(0xB2);
	HiSTM_SCP_transmit_data8(0x05);	HiSTM_SCP_transmit_data8(0x3C);	HiSTM_SCP_transmit_data8(0x3C);
	HiSTM_SCP_transmit_cmd(0xB3);
	HiSTM_SCP_transmit_data8(0x05);	HiSTM_SCP_transmit_data8(0x3C);	HiSTM_SCP_transmit_data8(0x3C);
	HiSTM_SCP_transmit_data8(0x05);	HiSTM_SCP_transmit_data8(0x3C);	HiSTM_SCP_transmit_data8(0x3C);

	HiSTM_SCP_transmit_cmd(0xB4);
	HiSTM_SCP_transmit_data8(0x03);

	HiSTM_SCP_transmit_cmd(0xC0);
	HiSTM_SCP_transmit_data8(0x28);	HiSTM_SCP_transmit_data8(0x08);	HiSTM_SCP_transmit_data8(0x04);
	HiSTM_SCP_transmit_cmd(0xC1);
	HiSTM_SCP_transmit_data8(0xC0);
	HiSTM_SCP_transmit_cmd(0xC2);
	HiSTM_SCP_transmit_data8(0x0D);	HiSTM_SCP_transmit_data8(0x00);
	HiSTM_SCP_transmit_cmd(0xC3);
	HiSTM_SCP_transmit_data8(0x8D);	HiSTM_SCP_transmit_data8(0x2A);
	HiSTM_SCP_transmit_cmd(0xC4);
	HiSTM_SCP_transmit_data8(0x8D);	HiSTM_SCP_transmit_data8(0xEE);
	HiSTM_SCP_transmit_cmd(0xC5);
	HiSTM_SCP_transmit_data8(0x1A);
	HiSTM_SCP_transmit_cmd(0x36);
#ifdef HiSTM_SCP_OP_POTRAIT
	HiSTM_SCP_transmit_data8(0xC0);
#endif
#ifdef HiSTM_SCP_OP_LANDSCAPE
	HiSTM_SCP_transmit_data8(0xA0);
#endif
	HiSTM_SCP_transmit_cmd(0xE0);
	HiSTM_SCP_transmit_data8(0x04);	HiSTM_SCP_transmit_data8(0x22);	HiSTM_SCP_transmit_data8(0x07);
	HiSTM_SCP_transmit_data8(0x0A);	HiSTM_SCP_transmit_data8(0x2E);	HiSTM_SCP_transmit_data8(0x30);
	HiSTM_SCP_transmit_data8(0x25);	HiSTM_SCP_transmit_data8(0x2A);	HiSTM_SCP_transmit_data8(0x28);
	HiSTM_SCP_transmit_data8(0x26);	HiSTM_SCP_transmit_data8(0x2E);	HiSTM_SCP_transmit_data8(0x3A);
	HiSTM_SCP_transmit_data8(0x00);	HiSTM_SCP_transmit_data8(0x01);	HiSTM_SCP_transmit_data8(0x03);
	HiSTM_SCP_transmit_data8(0x13);

	HiSTM_SCP_transmit_cmd(0xE1);
	HiSTM_SCP_transmit_data8(0x04); HiSTM_SCP_transmit_data8(0x16); HiSTM_SCP_transmit_data8(0x06);
	HiSTM_SCP_transmit_data8(0x0D); HiSTM_SCP_transmit_data8(0x2D); HiSTM_SCP_transmit_data8(0x26);
	HiSTM_SCP_transmit_data8(0x23); HiSTM_SCP_transmit_data8(0x27); HiSTM_SCP_transmit_data8(0x27);
	HiSTM_SCP_transmit_data8(0x25); HiSTM_SCP_transmit_data8(0x2D); HiSTM_SCP_transmit_data8(0x3B);
	HiSTM_SCP_transmit_data8(0x00); HiSTM_SCP_transmit_data8(0x01); HiSTM_SCP_transmit_data8(0x04);
	HiSTM_SCP_transmit_data8(0x13);

	HiSTM_SCP_transmit_cmd(0x3A);
	HiSTM_SCP_transmit_data8(0x05);

	HiSTM_SCP_transmit_cmd(0x29);
}

/*
 *  @ Brief: clear screen with specific color
 *  @ param: color - your expect color filled with full screen
 */
void HiSTM_SCP_clear(uint16_t color)
{
	uint16_t i, j;
	HiSTM_SCP_address_set(0, 0, HiSTM_SCP_PM_WIDTH - 1, HiSTM_SCP_PM_HEIGHT - 1);
	for(i=0; i<HiSTM_SCP_PM_WIDTH; i++)
	{
		for(j=0; j<HiSTM_SCP_PM_HEIGHT; j++)
		{
			HiSTM_SCP_transmit_data16(color);
		}
	}
}

/*
 *  @ Brief:
 *  @ param:
 */
void HiSTM_SCP_fill_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t i, j;
	HiSTM_SCP_address_set(x1, y1, x2, y2);
	for(i=y1; i<y2+1;i++)
	{
		for(j=x1; j<x2+1; j++)
		{
			HiSTM_SCP_transmit_data16(color);
		}
	}
}

/*
 *  @ Brief:
 *  @ param:
 */
void HiSTM_SCP_display_char(uint16_t X, uint16_t Y, uint8_t ascii, uint8_t mode, uint16_t font_color, uint16_t bkg_color)
{
	uint8_t i, j, font;
	uint8_t offset = ascii - ' ';
	if(X>HiSTM_SCP_PM_WIDTH - 16 || Y > HiSTM_SCP_PM_HEIGHT)
		return ;
	HiSTM_SCP_address_set(X, Y, X+7, Y+15);
	if(mode == HiSTM_SCP_CHARMODE_NOOVERLYING)
	{
		for(i=0; i<16; i++)
		{
			font = ascii_1608[(uint16_t)offset * 16 + i];
			for(j=0; j<8; j++)
			{
				if(font & 0x01)
					HiSTM_SCP_transmit_data16(font_color);
				else
					HiSTM_SCP_transmit_data16(bkg_color);
				font >>= 1;
			}
		}
	}
	else if(mode == HiSTM_SCP_CHARMODE_OVERLYING)
	{
		for(i=0; i<16; i++)
		{
			font = ascii_1608[(uint16_t)offset * 16 + i];
			for(j=0; j<8; j++)
			{
				if(font & 0x01)
					HiSTM_SCP_draw_point(X + j, Y + i, font_color);
				font >>= 1;
			}
		}
	}
}

/*
 *  @ Brief:
 *  @ param:
 */
void HiSTM_SCP_display_string(uint16_t X, uint16_t Y, uint8_t* string, uint8_t mode, uint16_t font_color, uint16_t bkg_color)
{
	uint16_t p_x = X, p_y = Y;
	uint8_t* p_string = string;

	while(*p_string != '\0')
	{
		if(p_x > HiSTM_SCP_PM_WIDTH - 16)
		{
			p_x  = 0;
			p_y += 16;
		}
		if(p_y > HiSTM_SCP_PM_HEIGHT - 16)
		{
			p_x = 0;
			p_y = 0;
			HiSTM_SCP_clear(bkg_color);
		}
		HiSTM_SCP_display_char(p_x, p_y, *p_string, mode, font_color, bkg_color);
		p_x += 8;
		p_string ++;
	}
}

/*
 *   Tips: Use "sprintf" function to show digits
 *   (I have try it on my GCC Compiler)
 *   but you cannot display float :( , try to use "q_15"
 * */

/*
 *  @ Brief:
 *  @ param:
 */
void HiSTM_SCP_display_chinese(uint16_t X, uint16_t Y, uint8_t index, uint8_t size, uint16_t font_color, uint16_t bkg_color)
{

}

/*
 *  @ Brief:
 *  @ param:
 */
void HiSTM_SCP_draw_point(uint16_t X, uint16_t Y, uint16_t color)
{
	HiSTM_SCP_address_set(X, Y, X, Y);
	HiSTM_SCP_transmit_data16(color);
}
