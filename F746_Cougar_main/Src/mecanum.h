/*
 * mecanum.h
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */

#ifndef MECANUM_H_
#define MECANUM_H_

#include "management.h"

#define bleak_time 20

int max(int a,int b);
long map_m(long x, long in_min, long in_max, long out_min, long out_max) ;
void motor_move(uint8_t comand,uint8_t dig1,uint8_t dig2,uint8_t power1a,uint8_t power2a);

#endif /* MECANUM_H_ */
