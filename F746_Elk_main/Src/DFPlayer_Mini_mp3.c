/*
 * DFPlayer_Mini_mp3.c
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */


#include "DFPlayer_Mini_mp3.h"

uint8_t cmd[8];

void DFPlayer_init(UART_HandleTypeDef *handler){
	huart_DFPlayer = handler;
}

void DFPlayer_setvolume(uint8_t volume){
	uint8_t cmd[8];
	cmd[0]= 0x7E;
	cmd[1]= 0xFF;
	cmd[2]=	0x06;
	cmd[3]=	0x06;
	cmd[4]=	0x00;
	cmd[5]=	0x00;
	cmd[6]=	volume;
	cmd[7]=	0xEF;
	HAL_UART_Transmit(huart_DFPlayer,(uint8_t*)cmd,8,0xF);
}
void DFPlayer_playmp3(uint8_t playnumber){
	uint8_t cmd[8];
	cmd[0]= 0x7E;
	cmd[1]= 0xFF;
	cmd[2]=	0x06;
	cmd[3]=	0x0F;
	cmd[4]=	0x00;
	cmd[5]=	1;
	cmd[6]=	playnumber;
	cmd[7]=	0xEF;
	HAL_UART_Transmit(huart_DFPlayer,(uint8_t*)cmd,8,0xF);
}
void DFPlayer_stopmp3(){
	uint8_t cmd[8];
	cmd[0]= 0x7E;
	cmd[1]= 0xFF;
	cmd[2]=	0x06;
	cmd[3]=	0x0E;
	cmd[4]=	0x00;
	cmd[5]=	0x00;
	cmd[6]=	0x00;
	cmd[7]=	0xEF;
	HAL_UART_Transmit(huart_DFPlayer,(uint8_t*)cmd,8,0xF);
}
