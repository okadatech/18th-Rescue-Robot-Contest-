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
int func(int h);
void slider(uint8_t cmd_bed,uint8_t speed_bed,uint8_t cmd_mechanism,uint8_t speed_mechanism);
void servo(int16_t a,int16_t b,int16_t c,int16_t d,int16_t e,int16_t f,int16_t g,int16_t h,int16_t i,int16_t j);
void pwm(int pwm1,int pwm2,int pwm3,int pwm4);
void beep(uint8_t time,uint16_t on_time,uint16_t off_time);
int encordermotor1(uint8_t place1);
long map_a(long x, long in_min, long in_max, long out_min, long out_max);

#endif /* ACTUATOR_H_ */
