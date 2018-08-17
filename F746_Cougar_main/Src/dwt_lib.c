/*
 * dwt_lib.c
 *
 *  Created on: 2017/10/07
 *      Author: takeshi
 */

#include "dwt_lib.h"

void init_cpu_cycle(){
	dwt_access_enable(1);
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
	(*((volatile uint32_t *) 0xE0001004)) = 0;
}

uint32_t get_cpu_cycle(){
	uint32_t cycle = DWT->CYCCNT;
	return cycle;
}

float get_process_time(uint32_t start,uint32_t stop){
	volatile float time = ((float)stop-(float)start)/(float)SystemCoreClock;
	return time*1000000;
}

float get_cpu_load(uint32_t start,uint32_t stop){
	float load = (((float)stop-(float)start)/(float)SystemCoreClock) / (float)(1.0/48000);
	return load*100;
}
float get_process_cycle(uint32_t start,uint32_t stop){
 int cycle = (stop-start);
  return cycle;
}
