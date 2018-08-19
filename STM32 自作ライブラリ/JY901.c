/*
 * JY901.c
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */
#include "JY901.h"


void JY901_init(I2C_HandleTypeDef *handler){
	 JY901_I2C = handler;
}

/* cmd=1  Angular velocity Calibration
 * cmd=2  Magnetic Calibration
 * cmd=3  Calibration end
 * cmd=4  Save
 */
void JY901_calibration(uint32_t time,uint8_t cmd){
	uint8_t send_cmd[3];
	uint8_t cycletime=0;
	if(time>1000){
		cycletime=time/1000;
	}
	switch(cmd){
	case 1:
		send_cmd[0]=0x01;
		send_cmd[1]=0x01;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		HAL_Delay(time);
	break;
	case 2:
		send_cmd[0]=0x01;
		send_cmd[1]=0x02;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		for(uint8_t i=0;i<cycletime;i++){
			HAL_Delay(1000);
			HAL_IWDG_Refresh(&hiwdg);
		}
	break;

	case 3:
		send_cmd[0]=0x01;
		send_cmd[1]=0x00;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		HAL_Delay(time);
	break;

	case 4:
		send_cmd[0]=0x00;
		send_cmd[1]=0x00;
		send_cmd[2]=0x00;
		HAL_I2C_Master_Transmit(JY901_I2C,JY901_I2C_ADDRESS,(uint8_t*)send_cmd,3,0xF);
		HAL_Delay(time);
	break;
	}
}

int JY901_def_set(){
	    uint8_t yaw[2];
	    uint16_t  def;
	    HAL_I2C_Mem_Read(JY901_I2C,JY901_I2C_ADDRESS,0x3F,I2C_MEMADD_SIZE_8BIT,(uint8_t*)yaw,2,0xFF);
	    uint8_t yawl=yaw[0];
	    uint8_t yawh=yaw[1];
	    def = ((yawh<< 8 ) | yawl ) * 180/ 32768 ;
	    def=(def-359)*(-1);
	    if(def<0){
	    	def=360+def;
	    }
	    return def;
}

int JY901_yaw_get(uint16_t def){
    uint8_t yaw[2];
    uint16_t digree;
    HAL_I2C_Mem_Read(JY901_I2C,JY901_I2C_ADDRESS,0x3F,I2C_MEMADD_SIZE_8BIT,(uint8_t*)yaw,2,0xFF);
    uint8_t yawl=yaw[0];
    uint8_t yawh=yaw[1];
    int Hx;
    Hx = ((yawh<< 8 ) | yawl ) * 180/ 32768 ;
    Hx=(Hx-359)*(-1);
    Hx = Hx - def;
     if(Hx<0){
     digree=Hx+360;
     }
     else{
     digree=Hx;
     }
     return digree;
}

