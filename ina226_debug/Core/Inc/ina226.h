#ifndef __INA226_H
#define __INA226_H

#include "stdint.h"
#include "main.h"


#define INA226_ADDRESS        (0x40 << 1)
#define INA226_REG_CONFIG     0x00 // Регистр конфигурации
#define INA226_REG_SHUNTV     0x01 // Напряжение на шунте
#define INA226_REG_BUSV       0x02 // Напряжение на нагрузке (Bus Voltage)
#define INA226_REG_CALIB      0x05 // Регистр калибровки (нужен для подсчета Тока/Мощности)



#define INA226_AVG_64           0x0800 // Усреднение: 64 выборки
#define INA226_VBUS_CT_2116US   0x0280 // Время конверсии VBUS: 2.116 мс
#define INA226_VSH_CT_2116US    0x0028 // Время конверсии Shunt: 2.116 мс
#define INA226_MODE_CONTINUOUS  0x0007 // Режим: непрерывный



HAL_StatusTypeDef INA226_WriteReg (uint8_t reg_addr, uint16_t value);
HAL_StatusTypeDef INA226_ReadReg (uint8_t reg_addr, uint16_t* value);
void INA226_Init ();
double INA226_GetBusVoltage();
double INA226_GetShuntVoltage ();

#endif
