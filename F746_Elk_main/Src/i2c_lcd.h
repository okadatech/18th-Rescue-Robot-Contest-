/*
 * i2c_lcd.h
 *
 *  Created on: 2017/09/09
 *      Author: takeshi
 */

#ifndef I2C_LCD_H_
#define I2C_LCD_H_

#include "stm32f7xx_hal.h"
#include "i2c.h"
#include <stdbool.h>
#include <string.h>

I2C_HandleTypeDef *oled_I2C;
#define I2C_ADDRESS (0x3C <<1) //使うI2Cデバイスによって変更してください
typedef enum{
	DisplayON 		= 0x0F,
	DisplayOFF		= 0x0B,
	ClearDisplay	= 0x01,
	ReturnHome 		= 0x02,
	EnableSD		= 0x79,
	DisableSD		= 0x78
} oled_Commands_Typedef;


void oled_i2c_to_oled(I2C_HandleTypeDef *handler);
void oled_put(char t_data);
void oled_puts(char *strings);
void oled_writeCommand(char t_command);
void oled_contrast();
void oled_init();
void oled_clear();
void oled_power(bool state);
void oled_delay_puts(char *strings,int delay_ms);
void oled_display_setting(bool displayon,bool cursoron,bool blinkon);
void oled_returnhome();
void oled_setcursor(int row,int column);

#endif /* I2C_LCD_H_ */
