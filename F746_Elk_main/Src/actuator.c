/*
 * actuator.c
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */
#include "actuator.h"

void pwm(int pwm1,int pwm2,int pwm3,int pwm4){
	  	  sConfigOC.Pulse = pwm4;
		  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		  sConfigOC.Pulse = pwm3;
		  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
		  sConfigOC.Pulse = pwm2;
		  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
		  sConfigOC.Pulse = pwm1;
		  HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
}

void slider(uint8_t cmd,uint8_t speed){
	switch (cmd) {
		case 10:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
		break;

		case 100:
			sConfigOC.Pulse = (speed-1)*4;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
		break;

		case 200:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = (speed-1)*4;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
		break;

		default:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
		break;
	}
}


void servo(uint8_t a,uint8_t b,uint8_t c,uint8_t d,uint8_t e,uint8_t f,uint8_t g,uint8_t h)
{
		if(a>180){a=180;}
		if(b>180){b=180;}
		if(c>180){c=180;}
		if(a<40){a=40;}
		if(b<40){b=40;}
		if(c<40){c=40;}
		if(d>105){d=105;}
		if(d<30){d=30;}
		if(e>180){e=180;}
		if(f>180){f=180;}
		if(g>180){g=180;}
		if(h>180){h=180;}
		sConfigOC.Pulse = map_a(a,180,0,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(b,180,0,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
		sConfigOC.Pulse = map_a(c,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		sConfigOC.Pulse = map_a(d,180,0,330,1170);
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
		sConfigOC.Pulse = map_a(e,180,0,330,1170);
		HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(f,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		sConfigOC.Pulse = map_a(g,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
		sConfigOC.Pulse = map_a(h,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);

}

void beep(uint8_t time,uint16_t on_time,uint16_t off_time){
	for(uint8_t fortime=0;fortime<time;fortime++){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1);
		HAL_Delay(on_time);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);
		HAL_Delay(off_time);
	}
}

long map_a(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
