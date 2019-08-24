#ifndef HiSTM_SCP_H_
#define HiSTM_SCP_H_

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "spi.h"
#include "timer.h"

/* LCD parameters */
#define  HiSTM_SCP_PM_WIDTH   128
#define  HiSTM_SCP_PM_HEIGHT  160

#define  HiSTM_SCP_OP_POTRAIT
#ifndef HiSTM_SCP_OP_POTRAIT
#define  HiSTM_SCP_OP_LANDSCAPE
#endif

/* Hardware Connection (GPIO) */
#define  HiSTM_SCP_DC_PORT    GPIOB
#define  HiSTM_SCP_DC_PIN     GPIO_Pin_9
#define  HiSTM_SCP_RES_PORT   GPIOB
#define  HiSTM_SCP_RES_PIN    GPIO_Pin_8
#define  HiSTM_SCP_CEN_PORT   GPIOB
#define  HiSTM_SCP_CEN_PIN    GPIO_Pin_4
#define  HiSTM_SCP_BL_PORT
#define  HiSTM_SCP_BL_PIN

#define  HiSTM_SCP_DC_OUTH   HiSTM_SCP_DC_PORT->ODR |=  HiSTM_SCP_DC_PIN
#define  HiSTM_SCP_DC_OUTL   HiSTM_SCP_DC_PORT->ODR &= ~HiSTM_SCP_DC_PIN
#define  HiSTM_SCP_RES_OUTH  HiSTM_SCP_RES_PORT->ODR |=  HiSTM_SCP_RES_PIN
#define  HiSTM_SCP_RES_OUTL  HiSTM_SCP_RES_PORT->ODR &= ~HiSTM_SCP_RES_PIN
#define  HiSTM_SCP_CEN_OUTH  HiSTM_SCP_CEN_PORT->ODR |=  HiSTM_SCP_CEN_PIN
#define  HiSTM_SCP_CEN_OUTL  HiSTM_SCP_CEN_PORT->ODR &= ~HiSTM_SCP_CEN_PIN
#define  HiSTM_SCP_BL_OUTH   HiSTM_SCP_BL_PORT->ODR |=  HiSTM_SCP_BL_PIN
#define  HiSTM_SCP_BL_OUTL   HiSTM_SCP_BL_PORT->ODR &= ~HiSTM_SCP_BL_PIN

/* Software interface */
//#define  HiSTM_Delay HiSTM_Delay

#define HiSTM_SCP_CHARMODE_OVERLYING   0
#define HiSTM_SCP_CHARMODE_NOOVERLYING 1

typedef struct{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
}HiSTM_SCP_DS_RGB888;

typedef uint16_t HiSTM_SCP_DS_RGB565;

/* SCP Function */
void HiSTM_SCP_transmit_byte(uint8_t data);
void HiSTM_SCP_transmit_cmd(uint8_t cmd);
void HiSTM_SCP_transmit_data8(uint8_t data);
void HiSTM_SCP_transmit_data16(uint16_t data);
void HiSTM_SCP_address_set(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void HiSTM_SCP_init(void);
void HiSTM_SCP_clear(uint16_t color);
void HiSTM_SCP_fill_region(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color);
void HiSTM_SCP_draw_point(uint16_t X, uint16_t Y, uint16_t color);
void HiSTM_SCP_display_char(uint16_t X, uint16_t Y, uint8_t ascii, uint8_t mode, uint16_t font_color, uint16_t bkg_color);
void HiSTM_SCP_display_string(uint16_t X, uint16_t Y, uint8_t* string, uint8_t mode, uint16_t font_color, uint16_t bkg_color);

#endif


