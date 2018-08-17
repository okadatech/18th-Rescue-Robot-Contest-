/*
 * solenoid.h
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#ifndef SOLENOID_H_
#define SOLENOID_H_

#include "stm32f7xx_hal.h"
#include "gpio.h"
#include <stdbool.h>
#include <string.h>

void solenoid(uint8_t movedata);

#endif /* SOLENOID_H_ */
