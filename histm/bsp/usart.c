#include "usart.h"
#include "string.h"

extern uint8_t cmd_buffer[1024];

#define USART_RX_BLOCK_SIZE 1024
#define USART_TX_BLOCK_SIZE 1024

uint8_t usart_tx_buffer[USART_TX_BLOCK_SIZE] = { 0 };
uint8_t usart_rx_buffer[USART_RX_BLOCK_SIZE] = { 0 };
uint32_t usart_rx_status = 0;

USART_InitTypeDef usart_init_struct;
static void HiSTM_strcpy(uint8_t* src, uint8_t* dst, uint16_t length);

void HiSTM_USART1_init(void)
{
	GPIO_InitTypeDef  gpio_init_struct;
	DMA_InitTypeDef   dma_init_struct;
	NVIC_InitTypeDef  nvic_init_struct;

	/* first enable clocks */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

	/* init usart1 */
	usart_init_struct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	usart_init_struct.USART_BaudRate = 115200;  //  default baud_rate
	usart_init_struct.USART_WordLength = USART_WordLength_8b;
	usart_init_struct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	usart_init_struct.USART_Parity = USART_Parity_No;
	usart_init_struct.USART_StopBits = USART_StopBits_1;
	USART_Init(USART1, &usart_init_struct);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	USART_ClearITPendingBit(USART1, USART_IT_IDLE);

	/* init gpio */
	gpio_init_struct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	gpio_init_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_init_struct.GPIO_OType = GPIO_OType_PP;
	gpio_init_struct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOB, &gpio_init_struct);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

	/* init dma */
	//  rx buffer
	dma_init_struct.DMA_Channel = DMA_Channel_4;
	dma_init_struct.DMA_DIR = DMA_DIR_PeripheralToMemory;
	dma_init_struct.DMA_Mode = DMA_Mode_Normal;
	dma_init_struct.DMA_Priority = DMA_Priority_High;
	dma_init_struct.DMA_BufferSize = USART_RX_BLOCK_SIZE;  //  up to 10KB data per receive
	dma_init_struct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma_init_struct.DMA_Memory0BaseAddr = (uint32_t)usart_rx_buffer;
	dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma_init_struct.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	USART_DMACmd(USART1, USART_DMAReq_Rx, ENABLE);
	DMA_Init(DMA2_Stream5, &dma_init_struct);
	DMA_ITConfig(DMA2_Stream5, DMA_IT_TCIF4, ENABLE);
	DMA_ClearITPendingBit(DMA2_Stream5, DMA_IT_TCIF4);

	//  tx buffer
	dma_init_struct.DMA_Channel = DMA_Channel_4;
	dma_init_struct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	dma_init_struct.DMA_Mode = DMA_Mode_Normal;
	dma_init_struct.DMA_Priority = DMA_Priority_High;
	dma_init_struct.DMA_BufferSize = USART_TX_BLOCK_SIZE;
	dma_init_struct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	dma_init_struct.DMA_Memory0BaseAddr = (uint32_t)usart_tx_buffer;
	dma_init_struct.DMA_MemoryInc = DMA_MemoryInc_Enable;
	dma_init_struct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	dma_init_struct.DMA_PeripheralBaseAddr = (uint32_t)&USART1->DR;
	dma_init_struct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	dma_init_struct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	DMA_Init(DMA2_Stream7, &dma_init_struct);

	//  enable receive interrupt
	nvic_init_struct.NVIC_IRQChannel = DMA2_Stream5_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = DISABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;
	NVIC_Init(&nvic_init_struct);

	nvic_init_struct.NVIC_IRQChannel = USART1_IRQn;
	nvic_init_struct.NVIC_IRQChannelCmd = DISABLE;
	nvic_init_struct.NVIC_IRQChannelPreemptionPriority = 2;
	nvic_init_struct.NVIC_IRQChannelSubPriority = 0;

	USART_Cmd(USART1, ENABLE);
	DMA_Cmd(DMA2_Stream5, ENABLE);
}

/*
 * 		USART1 receive interrupt
 * */
void USART1_IRQHandler(void)
{
	uint32_t tmp_counter = 0;
	volatile uint32_t temp;
	if( USART_GetITStatus(USART1, USART_IT_IDLE) == SET )
	{
		//  clear idle status
		temp = USART1->SR;
		temp = USART1->DR;
		//  rx complete
		//  1.  disable rxDMA
		DMA_Cmd(DMA2_Stream5, DISABLE);
		//  2.  get data size
		tmp_counter = USART_RX_BLOCK_SIZE - DMA_GetCurrDataCounter(DMA2_Stream5);
		//  3.  data process
		HiSTM_strcpy(usart_rx_buffer, cmd_buffer, tmp_counter);
		usart_rx_status  = ( tmp_counter | ( 1 << 31 ) );

		//  4.  configure & enable rxDMA
		DMA2_Stream5->NDTR = USART_RX_BLOCK_SIZE;
		DMA2_Stream5->M0AR = (uint32_t)usart_rx_buffer;
		DMA_Cmd(DMA2_Stream5, ENABLE);
	}
}

uint8_t HiSTM_USART1_tramsmit(uint8_t* data, uint16_t length)
{
	/* check if txDMA idle */
	if( DMA_GetCmdStatus(DMA2_Stream7) != DISABLE )
		return TXERR_txDMA_BUSY;
	DMA2_Stream7->M0AR = (uint32_t) data;
	DMA2_Stream7->NDTR = length;
	DMA_Cmd(DMA2_Stream7, ENABLE);
	return 0x00;
}

uint8_t HiSTM_USART1_send_string(uint8_t* data)
{
	/* check if txDMA idle */
	if( DMA_GetCmdStatus(DMA2_Stream7) != DISABLE )
		return TXERR_txDMA_BUSY;

	HiSTM_USART1_tramsmit(data, strlen(data));

	return 0x00;
}

static void HiSTM_strcpy(uint8_t* src, uint8_t* dst, uint16_t length)
{
	uint16_t i;
	for(i=0;i<length;i++)
	{
		dst[i] = src[i];
	}
}
