/*
 * actuator.h
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include "management.h"

TIM_Encoder_InitTypeDef sConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfigOC;
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

#define SERVO_LOW 380
#define SERVO_HIGH 1120
void slider(uint8_t cmd,uint8_t speed);
void servo(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t e,uint8_t f,uint8_t g,uint8_t h);
void pwm(int pwm1,int pwm2,int pwm3,int pwm4);
void beep(uint8_t time,uint16_t on_time,uint16_t off_time);
long map_a(long x, long in_min, long in_max, long out_min, long out_max);

#endif /* ACTUATOR_H_ */