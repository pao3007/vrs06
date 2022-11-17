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

void hts221_readArray(uint8_t * data, uint8_t reg, uint8_t length)
{
	i2c_master_read(data, length, reg, addres, 1);
}

float hts221_get_temp()
{
	uint8_t tempArr[2];
	hts221_readArray(tempArr,HTS221_ADDRESS_TEMP_L,2);


	int16_t temp = tempArr[0];
	temp |= (tempArr[1] << 8);



	uint8_t T0_degC_x8 = hts221_read_byte(HTS_221_T0_DEGC_X8);
	uint8_t T1_degC_x8 = hts221_read_byte(HTS_221_T1_DEGC_X8);
	uint8_t T1_T0msb = hts221_read_byte(HTS_221_T1_T0MSB);

	uint8_t T0_OUT_arr[2];
	uint8_t T1_OUT_arr[2];
	hts221_readArray(T0_OUT_arr,HTS_221_T0_OUT_3C,2);
	hts221_readArray(T1_OUT_arr,HTS_221_T1_OUT_3E,2);

	int16_t T0_OUT = T0_OUT_arr[0];
	T0_OUT |= (T0_OUT_arr[1] << 8);

	int16_t T1_OUT = T1_OUT_arr[0];
	T1_OUT |= (T1_OUT_arr[1] << 8);

	LL_mDelay(10);

	double T_DegC;
	double T0_degC = (T0_degC_x8 + (1 << 8) * (T1_T0msb & 0x03)) / 8.0;
	double T1_degC = (T1_degC_x8 + (1 << 6) * (T1_T0msb & 0x0C)) / 8.0;
	T_DegC = (T0_degC + (temp - T0_OUT) * (T1_degC - T0_degC) / (T1_OUT - T0_OUT));

	return (float)T_DegC;

}

int8_t hts221_get_humidity()
{
	uint8_t humLArr[2];
	uint8_t H0_T0_out_arr[2];
	uint8_t H1_T0_out_arr[2];

	hts221_readArray(humLArr, HTS221_ADDRESS_HUM_L,2);
	int16_t humL = humLArr[0];
	humL |= (humLArr[1] << 8);

	hts221_readArray(H0_T0_out_arr,HTS_221_H0_T0_OUT,2);
	int16_t H0_T0_out = H0_T0_out_arr[0];
	H0_T0_out |=  (H0_T0_out_arr[1] << 8);

	hts221_readArray(H1_T0_out_arr,HTS_221_H1_T0_OUT,2);
	int16_t H1_T0_out = H1_T0_out_arr[0];
	H1_T0_out |=  (H1_T0_out_arr[1] << 8);

	uint8_t H0_rH_x2 = hts221_read_byte(HTS_221_H0_RH_X2);
	uint8_t H1_rH_x2 = hts221_read_byte(HTS_221_H1_RH_X2);

	int8_t H_perc;
	int8_t H0 = H0_rH_x2 / 2;
	int8_t H1 = H1_rH_x2 / 2;
	H_perc = (H0 + ((humL - H0_T0_out) * (H1 - H0)) / (H1_T0_out - H0_T0_out));

	return H_perc;
}



uint8_t hts221_init(void)
{

	uint8_t status = 1;

	//LIS3MDL_ACC_ON;

	LL_mDelay(100);

	uint8_t val = hts221_read_byte(HTS221_WHO_AM_I_ADDRES);

	if(val == HTS221_WHO_AM_I_VALUE)
	{
		status = 1;
	}
	else			//if the device is not found on one address, try another one
	{
		status = 0;
	}

	//acc device init

	uint8_t ctrl1 = 1 << 7; //PD->1 active mode
	ctrl1 = ctrl1 | (1 << 0); //
	hts221_write_byte(HTS221_ADDRESS_CTRL1, ctrl1);


	return status;
}
