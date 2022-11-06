/*
 * hts221.h
 *
 *  Created on: Nov 6, 2022
 *      Author: lukac
 */

#include "main.h"
#include "i2c.h"

#define 	HTS221_WHO_AM_I_ADDRES					0x0F

#define 	HTS221_DEVICE_ADDRESS					0xBE

#define 	HTS221_ADDRESS_CTRL1					0x10


uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);

