/*
 * hts221.h
 *
 *  Created on: Nov 6, 2022
 *      Author: lukac
 */

#include "main.h"
#include "i2c.h"

#define 	HTS221_WHO_AM_I_ADDRES					0x0F
#define 	HTS221_WHO_AM_I_VALUE					0xBC

#define 	HTS221_DEVICE_ADDRESS					0xBE

#define 	HTS221_ADDRESS_CTRL1					0x20

#define 	HTS221_ADDRESS_TEMP_L					0x2A
#define 	HTS221_ADDRESS_TEMP_H					0x2B
#define 	HTS221_ADDRESS_HUM_L					0x28

#define 	HTS_221_T0_DEGC_X8						0x32
#define 	HTS_221_T1_DEGC_X8						0x33
#define 	HTS_221_T1_T0MSB						0x35
#define 	HTS_221_T0_OUT_3C						0x3C
#define 	HTS_221_T0_OUT_3D						0x3D
#define 	HTS_221_T1_OUT_3E						0x3E
#define 	HTS_221_T1_OUT_3F						0x3F

#define		HTS_221_H0_RH_X2						0x30
#define		HTS_221_H1_RH_X2						0x31
#define		HTS_221_H0_T0_OUT						0x36
#define		HTS_221_H1_T0_OUT						0x3A


#define 	TEMP_SENSITIVITY 						0.016f
#define 	TEMP_OFFSET                             25



uint8_t hts221_init(void);
uint8_t hts221_read_byte(uint8_t reg_addr);
void hts221_write_byte(uint8_t reg_addr, uint8_t value);
void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length);
float hts221_get_temp();
int8_t hts221_get_humidity();

