/*
 * crawler.c
 *
 *  Created on: 2017/10/16
 *      Author: okada_tech
 */

#include "crawler.h"
void motor_move(uint8_t Rdata1,uint8_t Rdata2,uint8_t Ldata1,uint8_t Ldata2){
	static uint8_t tempR,tempL;
	motorR = Ldata2;
	motorL = Rdata2;
	if(motorR<0){motorR=0;}
	if(motorL<0){motorL=0;}

	if(Rdata2>=0 && Ldata2>=0){
		switch(Rdata1){
		case 10:
			switch(Ldata1){
			case 10:
				pwm(1000,1000,1000,1000);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
			break;

			case 100:
				if(tempL==3){
				pwm(1000,1000,1000,1000);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				HAL_Delay(delay_time);
				}
				pwm(0,0,0,(motorR*4));tempL=2;
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
			break;

			case 200:
				if(tempL==2){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				pwm(0,0,(motorR*4),0);tempL=3;
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
			break;
			case 150:
				if(tempL==3){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				pwm(0,0,0,(motorR*4));
				HOUI_def=JY901_def_set();
				tempL=2;
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			case 250:
				if(tempL==2){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				pwm(0,0,(motorR*4),0);tempL=3;
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;


			default:
				  pwm(1000,1000,1000,1000);
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				  tempR=0;
				  tempL=0;
			break;
			}
		break;

		case 100:
			  if(tempR==3){
				  pwm(1000,1000,1000,1000);
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				  HAL_Delay(delay_time);
			  }
				  switch(Ldata1){
					  case 10:
						  pwm(0,(motorL*4),0,0);
							HOUI_def=JY901_def_set();
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
					  break;

					  case 100:
						  if(tempL==3){
							 pwm(1000,1000,1000,1000);
							  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
							 HAL_Delay(delay_time);
						   }
						  if((motorL)==(motorR)){
							  recuber(Ldata1,motorL);
						  }
						  else{
						  pwm(0,(motorL*4),0,(motorR*4));
							HOUI_def=JY901_def_set();
						  }
						  tempL=2;
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
					  break;

					  case 200:
						  if(tempL==2){
							  pwm(1000,1000,1000,1000);
							  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
							  HAL_Delay(delay_time);
						  }
						  pwm(0,(motorL*4),(motorR*4),0);tempL=3;
							HOUI_def=JY901_def_set();
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
					  break;

						case 150:
							if(tempL==3){
								pwm(1000,1000,1000,1000);
								HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
								HAL_Delay(delay_time);
							}
							pwm(0,(motorL*4),0,(motorR*4));
							HOUI_def=JY901_def_set();
							tempL=2;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
							break;

						case 250:
							if(tempL==2){
								pwm(1000,1000,1000,1000);
								HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
								HAL_Delay(delay_time);
							}
							pwm(0,(motorL*4),(motorR*4),0);tempL=3;
							HOUI_def=JY901_def_set();
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
							break;

					  default:
						  pwm(1000,1000,1000,1000);
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
						  tempR=0;
						  tempL=0;
					  break;
			  }
			  tempR=2;
		break;

		case 200:
			  if(tempR==2){
				  pwm(1000,1000,1000,1000);
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				  HAL_Delay(delay_time);
			  }
				switch(Ldata1){
					case 10:
						  pwm((motorL*4),0,0,0);
							HOUI_def=JY901_def_set();
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
					break;

					case 100:
						  if(tempL==3){
						 	pwm(1000,1000,1000,1000);
							  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
						 	HAL_Delay(delay_time);
						 	}
						  pwm((motorL*4),0,0,(motorR*4));tempL=2;
							HOUI_def=JY901_def_set();
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
					break;

					case 200:
						  if(tempL==2){
							  pwm(1000,1000,1000,1000);
							  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
							  HAL_Delay(delay_time);
						  }
						  if((motorL)==(motorR)){
							  recuber(Ldata1,motorL);
						  }
						  else{
						  pwm((motorL*4),0,(motorR*4),0);
							HOUI_def=JY901_def_set();
						  }
						  tempL=3;
						  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
					break;

					case 150:
						if(tempL==3){
							pwm(1000,1000,1000,1000);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
							HAL_Delay(delay_time);
						}
						pwm(0,(motorL*4),0,(motorR*4));
						HOUI_def=JY901_def_set();
						tempL=2;
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
						break;

					case 250:
						if(tempL==2){
							pwm(1000,1000,1000,1000);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
							HAL_Delay(delay_time);
						}
						pwm(0,(motorL*4),(motorR*4),0);tempL=3;
						HOUI_def=JY901_def_set();
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
						break;

					default:
						pwm(1000,1000,1000,1000);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
						tempR=0;
						tempL=0;
					break;
				}
			  tempR=3;
		break;

		case 150:
			if(tempR==3){
				pwm(1000,1000,1000,1000);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				HAL_Delay(delay_time);
			}
			switch(Ldata1){
			case 10:
				pwm(0,(motorL*4),0,0);
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			case 100:
				  if(tempL==3){
				 	pwm(1000,1000,1000,1000);
					  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				 	HAL_Delay(delay_time);
				 	}
				  pwm((motorL*4),0,0,(motorR*4));tempL=2;
					HOUI_def=JY901_def_set();
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
			break;

			case 200:
				  if(tempL==2){
					  pwm(1000,1000,1000,1000);
					  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					  HAL_Delay(delay_time);
				  }
				  pwm((motorL*4),0,(motorR*4),0);
					HOUI_def=JY901_def_set();
				  tempL=3;
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
			break;

			case 150:
				if(tempL==3){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				pwm(0,(motorL*4),0,(motorR*4));
				HOUI_def=JY901_def_set();
				tempL=2;
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			case 250:
				if(tempL==2){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				  pwm(0,(motorL*4),(motorR*4),0);tempL=3;//
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			default:
				pwm(1000,1000,1000,1000);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				tempR=0;
				tempL=0;
				break;
			}
			tempR=2;
		break;

		case 250:
			if(tempR==2){
				pwm(1000,1000,1000,1000);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				HAL_Delay(delay_time);
			}
			switch(Ldata1){
			case 10:
				pwm((motorL*4),0,0,0);
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			case 100:
				  if(tempL==3){
				 	pwm(1000,1000,1000,1000);
					  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				 	HAL_Delay(delay_time);
				 	}
				  pwm((motorL*4),0,0,(motorR*4));tempL=2;
					HOUI_def=JY901_def_set();
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
			break;

			case 200:
				  if(tempL==2){
					  pwm(1000,1000,1000,1000);
					  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					  HAL_Delay(delay_time);
				  }
				  pwm((motorL*4),0,(motorR*4),0);
					HOUI_def=JY901_def_set();
				  tempL=3;
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
			break;


			case 150:
				if(tempL==3){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				pwm((motorL*4),0,0,(motorR*4));tempL=2;
				HOUI_def=JY901_def_set();
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			case 250:
				if(tempL==2){
					pwm(1000,1000,1000,1000);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
					HAL_Delay(delay_time);
				}
				pwm((motorL*4),0,(motorR*4),0);
				HOUI_def=JY901_def_set();
				tempL=3;
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,1);
				break;

			default:
				pwm(1000,1000,1000,1000);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
				tempR=0;
				tempL=0;
				break;
			}
			tempR=3;
	break;

	default:
		pwm(1000,1000,1000,1000);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
		tempR=0;
		tempL=0;
	break;
	}
	}
	else{
		pwm(1000,1000,1000,1000);
		HAL_GPIO_WritePin(GPIOD,GPIO_PIN_8,0);
		tempR=0;
		tempL=0;
	}
}

void recuber(uint8_t cmd,uint8_t power){
	HOUI=JY901_yaw_get(HOUI_def);
	uint8_t	changepower;
	int16_t	power_subtraction;
	if(power>200){changepower=4;}
	else if(power>=100){changepower=3;}
	else{changepower=2;}

	switch(cmd){
	case 100:
		if(HOUI>1 && HOUI<180){
			power_subtraction =(power*4)-(map_crawler((HOUI*log((float)(HOUI+1)/1.5)),0,180,10,1000)*changepower);
			if(power_subtraction<0){power_subtraction=0;}
			pwm(0,(power*4),0,(power_subtraction));
		}
		else if(HOUI<358 && HOUI>180){
			power_subtraction=(power*4)-(map_crawler((360-HOUI)*log((float)(((360-HOUI)+1)/1.5)),0,180,10,1000)*changepower);
			if(power_subtraction<0){power_subtraction=0;}
			pwm(0,(power_subtraction),0,(power*4));
		}
		else{
		pwm(0,(power*4),0,(power*4));
		}
	break;

	case 200:
		if(HOUI>1 && HOUI<180){
			power_subtraction =(power*4)-(map_crawler((HOUI*log((float)(HOUI+1)/1.5)),0,180,10,1000)*changepower);
			if(power_subtraction<0){power_subtraction=0;}
			pwm((power_subtraction),0,(power*4),0);
	}
	else if(HOUI<358 && HOUI>180){
		power_subtraction=(power*4)-(map_crawler((360-HOUI)*log((float)(((360-HOUI)+1)/1.5)),0,180,10,1000)*changepower);
		if(power_subtraction<0){power_subtraction=0;}
		pwm((power*4),0,(power_subtraction),0);
	}
	else{
	pwm((power*4),0,(power*4),0);
	}
	break;

	default:
		pwm(1000,1000,1000,1000);
	break;
	}

}


long map_crawler(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
