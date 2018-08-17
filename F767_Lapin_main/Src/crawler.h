/*
 * crawler.h
 *
 *  Created on: 2017/10/16
 *      Author: okada_tech
 */

#ifndef CRAWLER_H_
#define CRAWLER_H_

#include "management.h"

#define delay_time 20
void motor_move(uint8_t Rdata1,uint8_t Rdata2,uint8_t Ldata1,uint8_t Ldata2);
void recuber(uint8_t cmd,uint8_t power);
long map_crawler(long x, long in_min, long in_max, long out_min, long out_max);


#endif /* CRAWLER_H_ */
