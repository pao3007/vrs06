/*
 * hts221.c
 *
 *  Created on: Nov 6, 2022
 *      Author: lukac
 */

#include "hts221.h"

uint8_t addres = HTS221_DEVICE_ADDRESS;

uint8_t hts221_read_byte(uint8_t reg_addr)
{
	uint8_t data = 0;
	return *(i2c_master_read(&data, 1, reg_addr, addres, 0));
}

void hts221_write_byte(uint8_t reg_addr, uint8_t value)
{
	i2c_master_write(value, reg_addr, addres, 0);
}

uint8_t hts221_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = lsm6ds0_read_byte(HTS221_WHO_AM_I_ADDRES);

	if(val == HTS221_WHO_AM_I_ADDRES)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		status = 0;
	}

	//acc device init

	uint8_t ctrl1 = 1 << 7; //PD->1 active mode
	hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);

	return status;
}
