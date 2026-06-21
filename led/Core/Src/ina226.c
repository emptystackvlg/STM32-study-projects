#include "ina226.h"
extern I2C_HandleTypeDef hi2c1;


HAL_StatusTypeDef INA226_WriteReg (uint8_t reg_addr, uint16_t value)
{
	uint8_t tx_buf [2];
	tx_buf [0] = (value>>8) & 0xFF;			//переворачиваем байты, потому что для INA-226 MSB-first
	tx_buf [1] = value & 0xFF;
	return HAL_I2C_Mem_Write(&hi2c1, INA226_ADDRESS, reg_addr, I2C_MEMADD_SIZE_8BIT, tx_buf, 2, 100);
}


HAL_StatusTypeDef INA226_ReadReg (uint8_t reg_addr, uint16_t* value)
{
	uint8_t rx_buf [2];
	HAL_StatusTypeDef status;
	status = HAL_I2C_Mem_Read(&hi2c1, INA226_ADDRESS, reg_addr, I2C_MEMADD_SIZE_8BIT, rx_buf, 2, 100);
	if (status == HAL_OK)
	{
		*value = (rx_buf[0]<<8)| rx_buf[1];				//записываем значение (LSB-First)
	}
	return status;
}
void INA226_Init ()
{
	 uint16_t config = 0x4000; // Базовый бит (всегда 1)

	 config |= INA226_AVG_64;
	 config |= INA226_VBUS_CT_2116US;
	 config |= INA226_VSH_CT_2116US;
	 config |= INA226_MODE_CONTINUOUS;

	 INA226_WriteReg(INA226_REG_CONFIG, config);

}



double INA226_GetBusVoltage()
{
	uint16_t raw_voltage = 0;
	double real_voltage = 0;
	if (INA226_ReadReg(INA226_REG_BUSV,&raw_voltage) == HAL_OK)
	{
		real_voltage = (double)raw_voltage*0.00125;
		return real_voltage;
	}
	else return 999;
}

double INA226_GetShuntVoltage ()
{
	uint16_t raw_shunt_voltage = 0;
	double shunt_voltage_mV = 0;
	if (INA226_ReadReg(INA226_REG_SHUNTV,&raw_shunt_voltage) == HAL_OK)
	{
		shunt_voltage_mV = raw_shunt_voltage * 0.0025;
		return shunt_voltage_mV;
	}
	else return 999;

}
