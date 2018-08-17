/*
 * actuator.c
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */
#include "actuator.h"


const uint8_t ICS_POS_CMD= 0x80;
const uint8_t ICS_PARA_WRITE_COMMND= 0xC0;
const uint8_t SUB_ST_COMMND= 0x01;
const uint8_t SUB_SP_COMMND= 0x02;

void Rarm(int16_t servo1,int16_t servo2,int16_t servo3,int16_t servo4,int16_t servo5){
	if(servo1>=90){servo1=90;}
	if(servo1<=20){servo1=20;}
    servo1=(servo1-90)*12/7+120;
    servo2=servo2-5;
    servo3=servo3-5;
	servo4=servo4+10;
	servo5=servo5+7;
	if(servo1>180){servo1=180;}
	if(servo1<0){servo1=0;}
	if(servo2<=50){servo2=50;}
	if(servo2>180){servo2=180;}
	if(servo3>180){servo3=180;}
	if(servo3<0){servo3=0;}
	if(servo4>180){servo4=180;}
	if(servo4<0){servo4=0;}
	if(servo5>180){servo5=180;}
	if(servo5<0){servo5=0;}
	sConfigOC.Pulse = map_a(servo1,120,0,SERVO_LOW,SERVO_HIGH);
	HAL_TIM_PWM_ConfigChannel(&htim13, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
	sConfigOC.Pulse = map_a(servo2,120,0,SERVO_LOW,SERVO_HIGH);
	HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
	ics_set_pos1(1,map_a(servo3,0,180,4833,10166));
	ics_set_pos1(2,map_a(servo4,180,0,4833,10166));
	ics_set_pos1(3,map_a(servo5,0,180,4833,10166));
}
void Larm(int16_t servo1,int16_t servo2,int16_t servo3,int16_t servo4,int16_t servo5){
	if(servo1>=90){servo1=90;}
	if(servo1<=20){servo1=20;}
	servo1=(servo1-90)*12/7+120;
    servo2=servo2-3;
	servo4=servo4+5;
	servo5=servo5+7;
	if(servo1>180){servo1=180;}
	if(servo1<0){servo1=0;}
	if(servo2<=60){servo2=60;}
	if(servo2>120){servo2=120;}
	if(servo3>180){servo3=180;}
	if(servo3<0){servo3=0;}
	if(servo4>180){servo4=180;}
	if(servo4<0){servo4=0;}
	if(servo5>180){servo5=180;}
	if(servo5<0){servo5=0;}
	sConfigOC.Pulse = map_a(servo1,0,120,SERVO_LOW,SERVO_HIGH);
	HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	sConfigOC.Pulse = map_a(servo2,0,120,SERVO_LOW,SERVO_HIGH);
	HAL_TIM_PWM_ConfigChannel(&htim14, &sConfigOC, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
	ics_set_pos2(1,map_a(servo3,180,0,4833,10166));
	ics_set_pos2(2,map_a(servo4,0,180,4833,10166));
	ics_set_pos2(3,map_a(servo5,180,0,4833,10166));

}

void servo(uint8_t a,uint8_t b,uint8_t c){
	if(a<35){a=35;}
	if(a>140){a=140;}
	sConfigOC.Pulse = map_a(a,0,180,SERVO_LOW,SERVO_HIGH);
	if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.Pulse = map_a(b,0,180,SERVO_LOW,SERVO_HIGH);
	if (HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.Pulse = map_a(c,0,180,SERVO_LOW,SERVO_HIGH);
	if (HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}

}

void motor2(int m1a,int m1b){
	sConfigOC.Pulse = m1a;
	if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.Pulse = m1b;
	if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
}
void motor1(int m2a,int m2b){
	sConfigOC.Pulse = m2a;
	if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.Pulse = m2b;
	if (HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
	    Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
}
void motor4(int m3b,int m3a){
	sConfigOC.Pulse = m3a;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.Pulse = m3b;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) != HAL_OK)
	{
		Error_Handler();
	}
}
void motor3(int m4b,int m4a){
	sConfigOC.Pulse = m4a;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.Pulse = m4b;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4) != HAL_OK)
	{
		Error_Handler();
	}
}

int Synchronize1(uint8_t *txBuff, size_t txLength, uint8_t *rxBuff, size_t rxLength)
{
  int size=0; //受信したbyte数
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1);
  HAL_UART_Transmit(&huart4,(uint8_t*)txBuff, txLength,0xf);
  while(HAL_UART_GetState(&huart4)==HAL_UART_STATE_BUSY_TX){}
  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
  size= HAL_UART_Receive(&huart4,(uint8_t*)rxBuff, rxLength,0xF);
  while(HAL_UART_GetState(&huart4)==HAL_UART_STATE_BUSY_RX){}
  if (size != HAL_OK) //指定した受信数かどうか確認
  {
    return 0;
  }
  return 1;
}

int ics_set_pos1(uint8_t id,unsigned short pos)
{
  uint8_t tx_data[3];
  uint8_t rx_data[3];
  int flag;
  int rAngle;   //受信した角度データ
  /// 送信コマンドを作成
  tx_data[0] = ICS_POS_CMD + id;
  tx_data[1] = (uint8_t)((pos & 0x3F80) >> 7);
  tx_data[2] = (uint8_t)(pos & 0x007F);

  //送受信を行う
  flag = Synchronize1(tx_data,3,rx_data,3);

  if(flag == 0) //失敗した場合は-1を返す
  {
    return -1;
  }

  rAngle = ((rx_data[1] << 7) & 0x3F80) + (rx_data[2] & 0x007F);

  return rAngle;
}
int ics_set_st1(uint8_t id,uint8_t stData)
{
  uint8_t tx_data[3];
  uint8_t rx_data[3];
  int flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_ST_COMMND;
  tx_data[2] = stData;

  //送受信を行う
  flag = Synchronize1(tx_data,3,rx_data,3);

  if(flag == 0) //失敗した場合は-1を返す
   {
     return -1;
   }

  return flag;
}

int ics_set_sp1(uint8_t id,uint8_t spData)
{
  uint8_t tx_data[3];
  uint8_t rx_data[3];
  int flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_SP_COMMND;
  tx_data[2] = spData;

  //送受信を行う
  flag = Synchronize1(tx_data,3,rx_data,3);

  if(flag == 0) //失敗した場合は-1を返す
    {
      return -1;
    }

  return flag;
}

int Synchronize2(uint8_t *txBuff, size_t txLength, uint8_t *rxBuff, size_t rxLength)
{
  int size; //受信したbyte数
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,1);
  HAL_UART_Transmit(&huart5,(uint8_t*)txBuff, txLength,0xf);
  while(HAL_UART_GetState(&huart5)==HAL_UART_STATE_BUSY_TX){}
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_9,0);
  size= HAL_UART_Receive(&huart5,(uint8_t*)rxBuff, rxLength,0xf);
  while(HAL_UART_GetState(&huart5)==HAL_UART_STATE_BUSY_RX){}
  if (size != HAL_OK) //指定した受信数かどうか確認
  {
    return 0;
  }
  return 1;
}

int ics_set_pos2(uint8_t id,unsigned short pos)
{
  uint8_t tx_data[3];
  uint8_t rx_data[3];
  int flag;
  int rAngle;   //受信した角度データ
  /// 送信コマンドを作成
  tx_data[0] = ICS_POS_CMD + id;
  tx_data[1] = (uint8_t)((pos & 0x3F80) >> 7);
  tx_data[2] = (uint8_t)(pos & 0x007F);

  //送受信を行う
  flag = Synchronize2(tx_data,3,rx_data,3);

  if(flag == 0) //失敗した場合は-1を返す
  {
    return -1;
  }

  rAngle = ((rx_data[1] << 7) & 0x3F80) + (rx_data[2] & 0x007F);

  return rAngle;
}
int ics_set_st2(uint8_t id,uint8_t stData)
{
  uint8_t tx_data[3];
  uint8_t rx_data[3];
  int flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_ST_COMMND;
  tx_data[2] = stData;

  //送受信を行う
  flag = Synchronize2(tx_data,3,rx_data,3);

  if(flag == 0) //失敗した場合は-1を返す
   {
     return -1;
   }

  return flag;
}

int ics_set_sp2(uint8_t id,uint8_t spData)
{
  uint8_t tx_data[3];
  uint8_t rx_data[3];
  int flag;
  /// 送信コマンドを作成
  tx_data[0] = ICS_PARA_WRITE_COMMND + id;
  tx_data[1] = SUB_SP_COMMND;
  tx_data[2] = spData;

  //送受信を行う
  flag = Synchronize2(tx_data,3,rx_data,3);

  if(flag == 0) //失敗した場合は-1を返す
    {
      return -1;
    }

  return flag;
}

void beep(uint8_t time,uint16_t on_time,uint16_t off_time){
	for(uint8_t fortime=0;fortime<time;fortime++){
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,1);
		HAL_Delay(on_time);
		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_2,0);
		HAL_Delay(off_time);
	}
}

long map_a(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
