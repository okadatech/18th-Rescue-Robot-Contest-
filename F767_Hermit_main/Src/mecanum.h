/*
 * mecanum.h
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */

#ifndef MECANUM_H_
#define MECANUM_H_

#include "management.h"

#define bleak_time 30

int max(int a,int b);
long map_m(long x, long in_min, long in_max, long out_min, long out_max) ;
void motor_move(uint8_t comand,uint8_t dig1,uint8_t dig2,uint8_t power1a,uint8_t power2a);


float power_caluculate[4];
int cnt[4],cnt_temp[3];
int power1_temp,power2_temp,power3_temp,power4_temp;

#endif /* MECANUM_H_ */
