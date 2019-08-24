#include "spi.h"
#include "timer.h"


void HiSTM_SPI1_Init(void)
{
	SPI_InitTypeDef   spi_init_struct;
	GPIO_InitTypeDef  gpio_init_struct;
	//  enable clks
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	spi_init_struct.SPI_Mode = SPI_Mode_Master;
	spi_init_struct.SPI_Direction = SPI_Direction_1Line_Tx;
	spi_init_struct.SPI_CPHA = SPI_CPHA_1Edge;
	spi_init_struct.SPI_CPOL = SPI_CPOL_Low;
	spi_init_struct.SPI_DataSize = SPI_DataSize_8b;
	spi_init_struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_64;
	spi_init_struct.SPI_FirstBit = SPI_FirstBit_MSB;
	spi_init_struct.SPI_NSS = SPI_NSS_Soft;
	SPI_Init(SPI1, &spi_init_struct);

	gpio_init_struct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_init_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &gpio_init_struct);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_SPI1);

	SPI_Cmd(SPI1, ENABLE);
}

uint8_t HiSTM_SPI1_transmit_data(uint8_t data)
{
	uint32_t i;
	//  check if last transmission okay
//	if(SPI2->SR & SPI_SR_BSY)
//		return HiSTM_SPI_TX_ERROR;
	SPI1->DR = data;

	//  wait for transmission
	for(i=0; i<0xFF; i++);

	return HiSTM_SPI_TX_OK;
}

