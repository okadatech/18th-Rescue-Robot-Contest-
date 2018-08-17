/*
 * DFPlayer_Mini_mp3.h
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#ifndef DFPLAYER_MINI_MP3_H_
#define DFPLAYER_MINI_MP3_H_


#include "stm32f7xx_hal.h"
#include "usart.h"
#include <stdbool.h>
#include <string.h>


UART_HandleTypeDef *huart_DFPlayer;

void DFPlayer_init(UART_HandleTypeDef *handler);
void DFPlayer_setvolume(uint8_t volume);
void DFPlayer_playmp3(uint8_t playnumber);
void DFPlayer_stopmp3();


#endif /* DFPLAYER_MINI_MP3_H_ */
