/*
 * actuator.c
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */
#include "actuator.h"
uint32_t uwDirectionCounta = 0;


int func(int h) {

	const float L = 230;
	const float H_min = 60;
	const float H_delta = 110;
	const float W_Max = sqrt(L*L - H_min * H_min);

	static int before_result = 0;

	float ans = L * L - H_min * H_min - 0.000016f * H_delta * H_delta * h * h - 0.008f * H_delta * h * H_min;
	if (ans < 0) return before_result;

	int result = (int)((W_Max - sqrt(ans)) * 0.5f + 0.5f);
	if (result < 0) return before_result;

	before_result = result;
	return result;
}

void pwm(int pwm3,int pwm4,int pwm1,int pwm2){
	  	  sConfigOC.Pulse = pwm2;
		  HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
		  sConfigOC.Pulse = pwm1;
		  HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
		  sConfigOC.Pulse = pwm3;
		  HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
		  sConfigOC.Pulse = pwm4;
		  HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_4);
		  HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
}

void slider(uint8_t cmd_bed,uint8_t speed_bed,uint8_t cmd_mechanism,uint8_t speed_mechanism){
	switch (cmd_bed) {
		case 10:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		break;

		case 200:
			if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_4)==0){
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
			}
			else{
			sConfigOC.Pulse = (speed_bed-1)*4;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
			}
		break;

		case 100:
			if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_5)==0){
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
			}
			else{
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
			sConfigOC.Pulse = (speed_bed-1)*4;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
			}
		break;

		default:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);
		break;
	}
	switch (cmd_mechanism) {
		case 10:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
		break;

		case 100:
			if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_2)==0){
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			}
			else{
			sConfigOC.Pulse = (speed_mechanism-1)*4;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			}
		break;

		case 200:
			if(HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_3)==0){
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
				HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			}
			else{
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			sConfigOC.Pulse = (speed_mechanism-1)*4;
			HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
			}
		break;

		default:
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_4);
			HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4);
		break;
	}
}


void servo(int16_t a,int16_t b,int16_t c,int16_t d,int16_t e,int16_t f,int16_t g,int16_t h,int16_t i,int16_t j)
{
		if(a>180){a=180;}
		if(b>153){b=153;}
		if(c>180){c=180;}
		if(d>180){d=180;}
		if(e>180){e=180;}
		if(f>180){f=180;}
		if(g>180){g=180;}
		if(h>180){h=180;}
		if(i>180){g=180;}
		if(j>180){h=180;}
		sConfigOC.Pulse = map_a(a,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(b,180,0,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
		sConfigOC.Pulse = map_a(c,180,0,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
		sConfigOC.Pulse = map_a(d,180,0,380,1120);
		HAL_TIM_PWM_ConfigChannel(&htim8, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
		sConfigOC.Pulse = map_a(e,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(f,180,0,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
		sConfigOC.Pulse = map_a(g,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(h,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(i,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a(j,0,180,SERVO_LOW,SERVO_HIGH);
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);

}

int encordermotor1(uint8_t place1){
	#define en1max 52116
	#define en1min 30000
	uint32_t placetemp1 =map_a(place1,0,250,en1min,en1max);;
	uwDirectionCounta = TIM1->CNT;
	if(place1==0){
			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0){
				TIM1->CNT = en1min;
				sConfigOC.Pulse = 0;
			    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
				Expand_flug=1;
				return HAL_OK;
			}
			else{
				sConfigOC.Pulse =700;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
				Expand_flug=0;
				return 2;
			}
		}
		else if(place1==250){
			if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0){
				TIM1->CNT = en1max;
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
				Expand_flug=1;
				return HAL_OK;
			}
			else{
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				sConfigOC.Pulse = 700;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
				Expand_flug=0;
				return 1;
			}
		}
		else{
	if(uwDirectionCounta<(placetemp1-5)){

		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0){
			TIM1->CNT = en1max;
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
			Expand_flug=1;
			return HAL_OK;
		}
		else{
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		sConfigOC.Pulse = map_a((placetemp1 - uwDirectionCounta), 0, en1max-en1min, 500, 1000);
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		Expand_flug=0;
		return 2;
		}
	}
	else if(uwDirectionCounta>=(placetemp1+5)){
		if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0){
				TIM1->CNT = en1min;
				sConfigOC.Pulse = 0;
			    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
				HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
				Expand_flug=1;
				return HAL_OK;
			}
		else{
		sConfigOC.Pulse = map_a((uwDirectionCounta - placetemp1), 0, en1max-en1min, 500, 1000);
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		sConfigOC.Pulse =0;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		Expand_flug=0;
		return 1;
		}
	}
	else{
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) ;
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		Expand_flug=1;
		return HAL_OK;
	}

}
}

void beep(uint8_t time,uint16_t on_time,uint16_t off_time){
	for(uint8_t fortime=0;fortime<time;fortime++){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,1);
		HAL_Delay(on_time);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_12,0);
		HAL_Delay(off_time);
	}
}

long map_a(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
