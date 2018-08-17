/*
 * actuator.c
 *
 *  Created on: 2017/10/15
 *      Author: okada_tech
 */

#include "actuator.h"
#include "stdlib.h"

uint32_t uwDirectionCounta = 0;
uint32_t uwDirectionCountb = 0;


void servo(int16_t a,int16_t b,int16_t c,int16_t d,int16_t e,int16_t f,int16_t g,int16_t h,int16_t i,int16_t j){
		a=a;
		b=b-10;
		c=c-10;
		d=d;
		e=e;
		f=f;
		if(a>180){a=180;}
		if(b>105){b=105;}
		if(c>105){c=105;}
		if(d>100){d=100;}
		if(e>170){e=170;}
		if(f>180){f=180;}
		if(a<0){a=0;}
		if(b<5){b=5;}
		if(c<5){c=5;}
		if(d<20){d=20;}
		if(e<10){e=10;}
		if(f<0){f=0;}
		/*if(g>180){g=180;}
		if(h>180){h=180;}
		if(i>180){i=180;}
		if(j>180){j=180;}*/
		  sConfigOC.Pulse = map_a(a,0,180,350,1220);
		  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1);
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);

		  sConfigOC.Pulse = map_a(b,180,0,250,1150);
		  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2);
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);

		  sConfigOC.Pulse = map_a(c,0,180,250,1150);
		  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3);
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);

		  sConfigOC.Pulse = map_a(d,180,0,250,1150);
		  HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4);
		  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4) ;

		  sConfigOC.Pulse = map_a(e,0,180,250,1150);
		  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_1) ;
		  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1) ;

		  /*sConfigOC.Pulse = map_a(f,0,180,250,1150);
		  HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_2) ;
		  HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_2);

		  sConfigOC.Pulse = map_a(g,0,180,250,1150);
		  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  sConfigOC.Pulse = map_a(h,0,180,250,1150);
		  if (HAL_TIM_PWM_ConfigChannel(&htim4, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  if (HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_4) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  sConfigOC.Pulse = map_a(i,0,180,250,1150);
		  if (HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  if (HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  sConfigOC.Pulse = map_a(j,0,180,250,1150);
		  if (HAL_TIM_PWM_ConfigChannel(&htim10, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
		  {
			  Error_Handler();
		  }
		  if (HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1) != HAL_OK)
		  {
			  Error_Handler();
		  }*/
}

int encordermotor1(uint8_t place1){
	#define en1max 29720
	#define en1min 30000
	uint32_t placetemp1 =map_a(place1,0,250,en1min,en1max);
	uwDirectionCounta = TIM5->CNT;
	if(place1==0){
			if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1)==0){
				TIM5->CNT = en1min;
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;
				return HAL_OK;
			}
			else{
				sConfigOC.Pulse = 700;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;
				return 2;
			}
		}
		else if(place1==250){
			if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==0){
				TIM5->CNT = en1max;
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;

				return HAL_OK;
			}
			else{
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
				sConfigOC.Pulse = 700;
				HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;
				return 1;
			}
		}
		else{
	if(uwDirectionCounta<(placetemp1-5)){
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1)==0){
			TIM5->CNT = en1min;
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
			HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;
			return HAL_OK;
		}
		else{
		sConfigOC.Pulse = map_a((placetemp1 - uwDirectionCounta), 0, en1min-en1max, 500, 1000);
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
		return 2;
		}
	}
	else if(uwDirectionCounta>=(placetemp1+5)){
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==0){
			TIM5->CNT = en1max;
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
			HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;
			return HAL_OK;
		}
		else{
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		sConfigOC.Pulse =map_a((uwDirectionCounta - placetemp1), 0, en1min-en1max, 500, 1000);
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2) ;
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
		return 1;
		}
	}
	else{
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_1) ;
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_1);
		sConfigOC.Pulse = 0;
		HAL_TIM_PWM_ConfigChannel(&htim12, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2) ;
		return HAL_OK;
	}
	}

}

int encordermotor2(uint8_t place2){
	#define en2max 30400
	#define en2min 30000
	volatile uint32_t placetemp2 =map_a(place2,0,250,en2min,en2max);
	uwDirectionCountb = TIM8->CNT;
	if(place2==0){
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)==0){
			TIM8->CNT = en2min;
			sConfigOC.Pulse = 0;
		    HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) ;
			return HAL_OK;
		}
		else{
			sConfigOC.Pulse = 700;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) ;
			return 2;
		}
	}
	else if(place2==250){
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_12)==0){
			TIM8->CNT = en2max;
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) ;

			return HAL_OK;
		}
		else{
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 700;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) ;
			return 1;
		}
	}
	else{
		if(uwDirectionCountb < (placetemp2-10)){
			if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_12)==0){
				TIM8->CNT = en2min;
				sConfigOC.Pulse = 0;
			    HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
				HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
				sConfigOC.Pulse = 0;
				HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
				HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) ;
				return HAL_OK;
			}
			else{
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = map_a(abs(placetemp2 - uwDirectionCountb), 0, (en2max-en2min), 500, 1000);
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
			return 2;
			}
		}
		else if(uwDirectionCountb > (placetemp2+10)){
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10)==0){
			TIM8->CNT = en2max;
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2) ;
			return HAL_OK;
			}
		else{
			sConfigOC.Pulse = map_a((uwDirectionCountb - placetemp2), 0, en2max-en2min, 500, 1000);
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse =0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2) ;
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
			return 1;
		}
		}
		else{
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_1);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_1);
			sConfigOC.Pulse = 0;
			HAL_TIM_PWM_ConfigChannel(&htim9, &sConfigOC, TIM_CHANNEL_2);
			HAL_TIM_PWM_Start(&htim9, TIM_CHANNEL_2);
			return HAL_OK;
		}
	}
}
void motor1(int m1b,int m1a){
		sConfigOC.Pulse = m1a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		sConfigOC.Pulse = m1b;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}
void motor2(int m2a,int m2b){
		sConfigOC.Pulse = m2a;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
		sConfigOC.Pulse = m2b;
		HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4) ;
}
void motor3(int m3b,int m3a){
		sConfigOC.Pulse = m3a;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
		sConfigOC.Pulse = m3b;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
void motor4(int m4a,int m4b){
		sConfigOC.Pulse = m4a;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
		sConfigOC.Pulse = m4b;
		HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4);
		HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

long map_a(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}

void beep(uint8_t time,uint16_t on_time,uint16_t off_time){
	for(uint8_t fortime=0;fortime<time;fortime++){
	  	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,1);
		HAL_Delay(on_time);
	  	HAL_GPIO_WritePin(GPIOE,GPIO_PIN_2,0);
		HAL_Delay(off_time);
	}
}
