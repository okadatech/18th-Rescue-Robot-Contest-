#include "i2c_lcd.h"

/* Read me
 * RE,IS -> Function set command
 * SD    -> Extend command/OLED Characterization
 *
 *
 * */


void oled_i2c_to_oled(I2C_HandleTypeDef *handler){
	 oled_I2C = handler;
	 oled_init();
	 oled_contrast(0xFF);
	 oled_clear();
	 oled_display_setting(true, false, false);
}

void oled_put(char t_data){
	uint8_t command[2];
	command[0]=0x40;
	command[1]=t_data;
	HAL_I2C_Master_Transmit(oled_I2C,I2C_ADDRESS,(uint8_t*)command,2,200);
}

void oled_puts(char *strings){
	uint8_t stringsbuf[17] = {0};
	int 	count = 1;
	stringsbuf[0] = 0x40;
	while(*strings){
		stringsbuf[count] = (uint8_t)*strings++;
		count++;
	}
	HAL_I2C_Master_Transmit(oled_I2C,I2C_ADDRESS,(uint8_t*)stringsbuf,count,200);
}

void oled_writeCommand(char t_command){
	uint8_t command[2];
	command[0]=0x00;
	command[1]=t_command;
	HAL_I2C_Master_Transmit(oled_I2C,I2C_ADDRESS,(uint8_t*)command,2,0xF);
}

void oled_delay_puts(char *strings,int delay_ms){
	while(*strings){
		HAL_Delay(delay_ms);
		oled_put(*strings++);
	}
}



void oled_contrast(int contrast){
	oled_writeCommand(0x2A);//RE=1
	oled_writeCommand(EnableSD);//SD=1
	oled_writeCommand(0x81);//コントラストセット
	oled_writeCommand(contrast);//輝度MAX(0x00~0xFF)
	oled_writeCommand(DisableSD);//SDを0に戻す
	oled_writeCommand(0x28);//2C=高文字 28=ノーマル
	HAL_Delay(100);
}

void oled_init(){
	oled_returnhome();
	oled_power(true);
	oled_clear();
}

void oled_clear(){
	oled_writeCommand(ClearDisplay);
}

void oled_power(bool state){
	if(state == true){
		oled_writeCommand(DisplayON);
		HAL_Delay(10);
	}
	else{
		oled_writeCommand(DisplayOFF);
		HAL_Delay(10);
	}
}


void oled_display_setting(bool displayon,bool cursoron,bool blinkon){
	char command[1];
	command[0] = 0x08;
	command[0] =
			1		  << 3 |
			displayon << 2 |
			cursoron  << 1 |
			blinkon   << 0;

	oled_writeCommand(command[0]);
	HAL_Delay(10);

}

/**
  * @brief  文字開始位置の設定
  * @param  column	0~1
  * @param  row		0~15
  * @retval none
  */
void oled_setcursor(int column,int row){
	if(column==0 && row<16){
		oled_writeCommand(0x80+row);
	}
	else if(column==1 && row<16){
		oled_writeCommand(0xA0+row);
	}
	else{
		oled_writeCommand(0x80);
	}
}

void oled_returnhome(){
	oled_writeCommand(ReturnHome);
}
