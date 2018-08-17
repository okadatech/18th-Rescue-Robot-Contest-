/*
 * management.h
 *
 *  Created on: 2017/10/16
 *      Author: okada_tech
 */

#ifndef MANAGEMENT_H_
#define MANAGEMENT_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "iwdg.h"
#include <math.h>
#define ARM_MATH_CM7
#include "arm_math.h"
#include "xprintf.h"
#include "i2c_lcd.h"
#include "JY901.h"
#include "DFPlayer_Mini_mp3.h"
#include "CCS811.h"
#include "actuator.h"
#include "crawler.h"
#include <stdbool.h>
#include <string.h>


uint16_t HOUI,HOUI_def;
int16_t motorL,motorR;
uint32_t counttime;

#endif /* MANAGEMENT_H_ */
