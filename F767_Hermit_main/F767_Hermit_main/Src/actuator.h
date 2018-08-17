/*
 * actuator.h
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */

#ifndef ACTUATOR_H_
#define ACTUATOR_H_
#include "management.h"


#define SERVO_MIN 3500 // サーボ最小動作角(-135度)
#define SERVO_CENTER 7500 // サーボ中心角(0度)
#define SERVO_MAX 11500 // サーボ最大動作角(+135度)
#define SERVO_LOW 380
#define SERVO_HIGH 1120
TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfigOC;
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;

void servo(uint8_t a,uint8_t b,uint8_t c);
void Rarm(int16_t servo1,int16_t servo2,int16_t servo3,int16_t servo4,int16_t servo5);
void Larm(int16_t servo1,int16_t servo2,int16_t servo3,int16_t servo4,int16_t servo5);
void motor1(int m1a,int m1b);
void motor2(int m2a,int m2b);
void motor3(int m3a,int m3b);
void motor4(int m4a,int m4b);
int Synchronize1(uint8_t *txBuff, size_t txLength, uint8_t *rxBuff, size_t rxLength);
int ics_set_pos1(uint8_t id,unsigned short pos);
int ics_set_st1(uint8_t id,uint8_t stData);
int ics_set_sp1(uint8_t id,uint8_t spData);
int Synchronize2(uint8_t *txBuff, size_t txLength, uint8_t *rxBuff, size_t rxLength);
int ics_set_pos2(uint8_t id,unsigned short pos);
int ics_set_st2(uint8_t id,uint8_t stData);
int ics_set_sp2(uint8_t id,uint8_t spData);
void beep(uint8_t time,uint16_t on_time,uint16_t off_time);
long map_a(long x, long in_min, long in_max, long out_min, long out_max);

#endif /* ACTUATOR_H_ */
