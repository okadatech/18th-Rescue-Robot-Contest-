/*
 * JY901.h
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#ifndef JY901_H_
#define JY901_H_

#include "stm32f7xx_hal.h"
#include "i2c.h"
#include "iwdg.h"
#include <stdbool.h>
#include <string.h>

I2C_HandleTypeDef *JY901_I2C;
#define JY901_I2C_ADDRESS (0x50<<1)


void JY901_init(I2C_HandleTypeDef *handler);
void JY901_calibration(uint32_t time,uint8_t cmd);
int JY901_def_set();
int JY901_yaw_get(uint16_t def);
#endif /* JY901_H_ */
