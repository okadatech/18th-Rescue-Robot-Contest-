/*
 * management.h
 *
 *  Created on: 2018/01/13
 *      Author: okada_tech
 */

#ifndef MANAGEMENT_H_
#define MANAGEMENT_H_

#include "main.h"
#include "stm32f7xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include <math.h>
#define ARM_MATH_CM7
#include "arm_math.h"
#include "xprintf.h"
#include "i2c_lcd.h"
#include "i2c_lcd.h"
#include "JY901.h"
#include "DFPlayer_Mini_mp3.h"
#include "crawler.h"
#include "actuator.h"
#include "microsectimer.h"
#include <stdbool.h>
#include <string.h>


TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfigOC;
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
TIM_Encoder_InitTypeDef sConfig;


uint8_t Txdata[1];
uint8_t Expand_flug;
uint16_t HOUI,HOUI_def;
int16_t motorL,motorR;
uint32_t counttime;

#endif /* MANAGEMENT_H_ */
