/*
 * solenoid.c
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#include "solenoid.h"


void solenoid(uint8_t movedata){
	uint8_t tempbuf;
	tempbuf=(movedata & 0b00000010)>>1;
	if(tempbuf==1){
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_14);
		HAL_Delay(75);
	}
	else{
		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_14,0);
	}
	tempbuf=(movedata & 0b00000100)>>2;
	if(tempbuf==1){HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,1);}
	else{HAL_GPIO_WritePin(GPIOC,GPIO_PIN_15,0);}
}
