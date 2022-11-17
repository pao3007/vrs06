/*
 * lps22hb.h
 *
 *  Created on: 17. 11. 2022
 *      Author: lukac
 */

#include "main.h"
#include "i2c.h"

#define 	SCALE_FACTOR							4096.0


#define 	LPS22HB_WHO_AM_I_ADDRES					0x0F
#define 	LPS22HB_WHO_AM_I_VALUE					0xB1

#define 	LPS22HB_DEVICE_ADDRESS					0xB8
#define 	LPS22HB_DEVICE_ADDRESS_ALTER			0xBA

#define 	LPS22HB_ADDRESS_CTRL1					0x10

#define 	LPS22HB_PRESS_OUT_XL					0x28
#define 	LPS22HB_PRESS_OUT_L						0x29
#define 	LPS22HB_PRESS_OUT_H						0x2A

#define 	LPS22HB_REF_P_XL						0x15
#define 	LPS22HB_REF_P_L							0x16
#define 	LPS22HB_REF_P_H							0x17


uint8_t lps22hb_init(void);
void lps22hb_write_byte(uint8_t reg_addr, uint8_t value);
uint8_t lps22hb_read_byte(uint8_t reg_addr);
void lps22hb_readArray(uint8_t * data, uint8_t reg, uint8_t length);
float lps22hb_get_pressure();
