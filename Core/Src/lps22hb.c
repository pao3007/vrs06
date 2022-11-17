/*
 * lps22hb.c
 *
 *  Created on: 17. 11. 2022
 *      Author: lukac
 */
#include "lps22hb.h"

uint8_t addres_lps22hb = LPS22HB_DEVICE_ADDRESS;

uint8_t lps22hb_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres_lps22hb, 0));
}

void lps22hb_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres_lps22hb, 0);
}

void lps22hb_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres_lps22hb, 1);
}

float lps22hb_get_pressure()
{
	/*uint8_t bar[3];
	lps22hb_readArray(bar, LPS22HB_PRESS_OUT_XL, 3);
	uint32_t counts = bar[0];
	counts |= (bar[1] << 8);
	counts |= (bar[2] << 16);
	float pressure = counts/SCALE_FACTOR;
	return pressure;*/

	uint8_t buffer[3];
	uint32_t tmp = 0;
	uint8_t i;

	lps22hb_readArray(buffer, LPS22HB_PRESS_OUT_XL, 3);
	  /* Build the raw data */
	for(i=0; i<3; i++)
	  tmp |= (((uint32_t)buffer[i]) << (8*i));

	  /* convert the 2's complement 24 bit to 2's complement 32 bit */
	if(tmp & 0x00800000)
	  tmp |= 0xFF000000;

	int32_t raw_press = ((int32_t)tmp);

	float tlak = raw_press/SCALE_FACTOR;
	return tlak;

}


uint8_t lps22hb_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = lps22hb_read_byte(LPS22HB_WHO_AM_I_ADDRES);

	if(val == LPS22HB_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		addres_lps22hb = LPS22HB_DEVICE_ADDRESS_ALTER;
		val = lps22hb_read_byte(LPS22HB_WHO_AM_I_ADDRES);
		if(val == LPS22HB_WHO_AM_I_VALUE)
			{
				status = 1;
			}
			else			//if the device is not found on one address, try another one
			{
				status = 0;
			}
	}

	//acc device init

	uint8_t ctrl1 = 1 << 5; //
	ctrl1 |= 1 << 3; //
	lps22hb_write_byte(LPS22HB_ADDRESS_CTRL1, ctrl1);



	return status;
}


