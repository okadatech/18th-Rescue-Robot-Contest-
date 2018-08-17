/*
 * CCS811.h
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#ifndef CCS811_H_
#define CCS811_H_

#include "stm32f7xx_hal.h"
#include "i2c.h"
#include <stdbool.h>
#include <string.h>

I2C_HandleTypeDef *CCS811_I2C;

#define CCS811addr 0x5B<<1 // connected to GND

void CCS811_init(I2C_HandleTypeDef *handler);
uint16_t CCS811_CO2_get();
uint16_t CCS811_TVOCs_get();
uint8_t environment_get();


#endif /* CCS811_H_ */
