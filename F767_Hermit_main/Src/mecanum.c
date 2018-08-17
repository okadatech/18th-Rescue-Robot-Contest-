/*
 * mecanum.c
 *
 *  Created on: 2017/11/05
 *      Author: okada_tech
 */


#include "mecanum.h"

void motor_move(uint8_t comand,uint8_t dig2,uint8_t dig1,uint8_t power1a,uint8_t power2a){
		  power=(power1a)*(power2a-1);
		  if(power<0){power=0;}
		  if(power1a==0){power=0;}
		  digree=((dig2<<8)+dig1)-1000;
		  if(digree<0){digree=0;}

			/*
				 100;8•ûˆÊ@•ûˆÊC³‚ ‚è¨ƒgƒ‹ƒN§Œä
				 250;8•ûˆÊ@•ûˆÊC³‚È‚µ
				 150;¶‰ñ“]
				 200;‰E‰ñ“]
				 50;360“x@C³‚È‚µ
				 125;360“x@•ûˆÊC³‚ ‚è¨ƒgƒ‹ƒN§Œä
				  */
		  switch(comand){
		  case 50:
			  if(digree>=0 && digree<=360){
				  if(digree>=0 && digree<=45){
					if(digtemp!=0){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
					}
					  power1=(float)arm_sin_f32((45-digree)*M_PI/180)*power;
					  power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*-1*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					motor1(0,power1);
					motor2(0,power2);
					motor3(0,power3);
					motor4(0,power4);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=0;
				  }
				  else if(digree>45 && digree<=90){
					  if(digtemp!=90){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					  power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(power1,0);
					  motor2(0,power2);
					  motor3(power3,0);
					  motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=90;
				  }
				  else if(digree>90 && digree<=135){
					  if(digtemp!=90){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					  power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(power1,0);
					  motor2(0,power2);
					  motor3(power3,0);
					  motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=90;
				  }
				  else if(digree>135 && digree<=180){
					  if(digtemp!=180){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(power1,0);
					  motor2(power2,0);
					  motor3(power3,0);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=180;
				  }
				  else if(digree>180 && digree<=225){
					  if(digtemp!=180){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(power1,0);
					  motor2(power2,0);
					  motor3(power3,0);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=180;
				  }
				  else if(digree>225 && digree<=270){
					  if(digtemp!=270){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(0,power1);
					  motor2(power2,0);
					  motor3(0,power3);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=270;
				  }
				  else if(digree>270 && digree<=315){
					  if(digtemp!=270){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					}
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
					  power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(0,power1);
					  motor2(power2,0);
					  motor3(0,power3);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=270;
				  }
				  else if(digree>315 && digree<=360){
					  if(digtemp!=0){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*-1*power;
					  power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
					  power4=(float)arm_sin_f32((digree-315)*M_PI/180)*power;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power/y);
					  power2=power2*((float)power/y);
					  power3=power3*((float)power/y);
					  power4=power4*((float)power/y);
					  motor1(0,power1);
					  motor2(0,power2);
					  motor3(0,power3);
					  motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=0;
				  	  }
			  }
			  else{
				  motor1(0,0);
				  motor2(0,0);
				  motor3(0,0);
				  motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
				  //digtemp=1000;
			  }
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
		  break;

		  /*case 125:
				HOUI=JY901_yaw_get(HOUI_def);
				if(HOUI>= 5 && HOUI<=355){
					motor1(0,0);
					motor2(0,0);
					motor3(0,0);
					motor4(0,0);
					HAL_GPIO_WritePin(GPIOE,GPIO_PIN_10,0);
					HAL_Delay(50);
					while(HOUI>=5 && HOUI<=355){
					HOUI=JY901_yaw_get(HOUI_def);
					if(HOUI<180){
					motor1((int)map_m(HOUI,0,180,200,500),0);
					motor2((int)map_m(HOUI,0,180,200,500),0);
					motor3(0,(int)map_m(HOUI,0,180,200,500));
					motor4(0,(int)map_m(HOUI,0,180,200,500));
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					}
					else{
						motor1(0,(int)map_m(HOUI,359,180,200,500));
						motor2(0,(int)map_m(HOUI,359,180,200,500));
						motor3((int)map_m(HOUI,359,180,200,500),0);
						motor4((int)map_m(HOUI,359,180,200,500),0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					}
				  	  HAL_IWDG_Refresh(&hiwdg);
					}
					motor1(0,0);
					motor2(0,0);
					motor3(0,0);
					motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
					HAL_Delay(50);
				}
					if(digree>=0 && digree<=360){
					if(digree>=0 && digree<=45){
						if(digtemp!=0){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((45-digree)*M_PI/180)*power;
						power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*-1*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(0,power2);
						motor3(0,power3);
						motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=0;
					}
					else if(digree>45 && digree<=90){
						if(digtemp!=90){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(0,power2);
						motor3(power3,0);
						motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=90;
							  }
					else if(digree>90 && digree<=135){
						if(digtemp!=90){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(0,power2);
						motor3(power3,0);
						motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=90;
					}
					else if(digree>135 && digree<=180){
						if(digtemp!=180){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(power2,0);
						motor3(power3,0);
						motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=180;
					}
					else if(digree>180 && digree<=225){
						if(digtemp!=180){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(power1,0);
						motor2(power2,0);
						motor3(power3,0);
						motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=180;
					}
					else if(digree>225 && digree<=270){
						if(digtemp!=270){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(power2,0);
						motor3(0,power3);
						motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=270;
					}
					else if(digree>270 && digree<=315){
						if(digtemp!=270){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power;
						power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
						power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(power2,0);
						motor3(0,power3);
						motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=270;
					}
					else if(digree>315 && digree<=360){
						if(digtemp!=0){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
						}
						power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power;
						power2=(float)arm_sin_f32((digree-135)*M_PI/180)*-1*power;
						power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power;
						power4=(float)arm_sin_f32((digree-315)*M_PI/180)*power;
						temp1=max(power1,power2);
						temp2=max(power3,temp1);
						y=max(power4,temp2);
						power1=power1*((float)power/y);
						power2=power2*((float)power/y);
						power3=power3*((float)power/y);
						power4=power4*((float)power/y);
						motor1(0,power1);
						motor2(0,power2);
						motor3(0,power3);
						motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						digtemp=0;
					}
				}
				else{
					motor1(0,0);
					motor2(0,0);
					motor3(0,0);
					motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
					//digtemp=1000;
				}
		  break;
		  */

		  /*
		   case 100:
				HOUI=JY901_yaw_get(HOUI_def);
		  	   if(HOUI>= 5 && HOUI<=355){
		  		motor1(0,0);
		  	    motor2(0,0);
		  		motor3(0,0);
		  		motor4(0,0);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		  		HAL_Delay(50);
		  	  while(HOUI>=5 && HOUI<=355){
		  		HOUI=JY901_yaw_get(HOUI_def);
		  	    if(HOUI<180){
		  	 	motor1((int)map_m(HOUI,0,180,200,500),0);
		  	 	motor2((int)map_m(HOUI,0,180,200,500),0);
		  	 	motor3(0,(int)map_m(HOUI,0,180,200,500));
		  	 	motor4(0,(int)map_m(HOUI,0,180,200,500));
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		  	 	xprintf("LS now");
		  	 	xprintf(" speed= %d\r\n",(int)map_m(HOUI,0,180,70,300));
		  	    }
		  	    else{
		  	    	motor1(0,(int)map_m(HOUI,359,180,200,500));
		  	    	motor2(0,(int)map_m(HOUI,359,180,200,500));
		  	    	motor3((int)map_m(HOUI,359,180,200,500),0);
		  	    	motor4((int)map_m(HOUI,359,180,200,500),0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		  	    	xprintf("RS now");
		  	    	xprintf(" speed= %d\r\n",(int)map_m(HOUI,359,180,70,300));
		  	    }
			  	  HAL_IWDG_Refresh(&hiwdg);
		  	  }
				 motor1(0,0);
				 motor2(0,0);
				 motor3(0,0);
				 motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
				 HAL_Delay(50);
		  	  }

		  	   else if(digree>=0 && digree<=360){
		 		  if(digree<=23 || digree>=338){
		 			if(digtemp!=0){
		 					motor1(0,0);
		 					motor2(0,0);
		 					motor3(0,0);
		 					motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 					xprintf("bleak now\r\n");
		 					HAL_Delay(bleak_time);
		 			}
		 			motor1(0,power);
		 			motor2(0,power);
		 			motor3(0,power);
		 			motor4(0,power);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=0;
		 		  }
		 		  else if(digree>23 && digree<=68){
		 			  if(digtemp!=45){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(0,0);
		 			  motor2(0,power);
		 			  motor3(0,0);
		 			  motor4(0,power);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=45;
		 		  }
		 		  else if(digree>68 && digree<=113){
		 			  if(digtemp!=90){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(power,0);
		 			  motor2(0,power);
		 			  motor3(power,0);
		 			  motor4(0,power);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=90;
		 		  }
		 		  else if(digree>113 && digree<=158){
		 			  if(digtemp!=135){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(power,0);
		 			  motor2(0,0);
		 			  motor3(power,0);
		 			  motor4(0,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=135;
		 		  }
		 		  else if(digree>158 && digree<=203){
		 			  if(digtemp!=180){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(power,0);
		 			  motor2(power,0);
		 			  motor3(power,0);
		 			  motor4(power,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=180;
		 		  }
		 		  else if(digree>203 && digree<=248){
		 			  if(digtemp!=225){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(0,0);
		 			  motor2(power,0);
		 			  motor3(0,0);
		 			  motor4(power,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=225;
		 		  }
		 		  else if(digree>248 && digree<=293){
		 			  if(digtemp!=270){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(0,power);
		 			  motor2(power,0);
		 			  motor3(0,power);
		 			  motor4(power,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=270;
		 		  }
		 		  else if(digree>293 && digree<=338){
		 			  if(digtemp!=315){
		 				  motor1(0,0);
		 				  motor2(0,0);
		 				  motor3(0,0);
		 				  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 				xprintf("bleak now\r\n");
		 				  HAL_Delay(bleak_time);
		 			  }
		 			  motor1(0,power);
		 			  motor2(0,0);
		 			  motor3(0,power);
		 			  motor4(0,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
		 			  digtemp=315;
		 		  	  }
		 	  }
		 	  else{
		 		  oled_puts("Running       ST");
		 		  motor1(0,0);
		 		  motor2(0,0);
		 		  motor3(0,0);
		 		  motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 		  //digtemp=1000;
		 	  }
		  break;*/

		  case 250:


			  if(digree>=0 && digree<=360){
				  if(digree<=23 || digree>=338){
					if(digtemp!=0){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
					}
					motor1(0,power);
					motor2(0,power);
					motor3(0,power);
					motor4(0,power);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=0;
				  }
				  else if(digree>23 && digree<=68){
					  if(digtemp!=45){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,0);
					  motor2(0,power);
					  motor3(0,0);
					  motor4(0,power);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=45;
				  }
				  else if(digree>68 && digree<=113){
					  if(digtemp!=90){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(power,0);
					  motor2(0,power);
					  motor3(power,0);
					  motor4(0,power);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=90;
				  }
				  else if(digree>113 && digree<=158){
					  if(digtemp!=135){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(power,0);
					  motor2(0,0);
					  motor3(power,0);
					  motor4(0,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=135;
				  }
				  else if(digree>158 && digree<=203){
					  if(digtemp!=180){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(power,0);
					  motor2(power,0);
					  motor3(power,0);
					  motor4(power,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=180;
				  }
				  else if(digree>203 && digree<=248){
					  if(digtemp!=225){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,0);
					  motor2(power,0);
					  motor3(0,0);
					  motor4(power,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=225;
				  }
				  else if(digree>248 && digree<=293){
					  if(digtemp!=270){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,power);
					  motor2(power,0);
					  motor3(0,power);
					  motor4(power,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=270;
				  }
				  else if(digree>293 && digree<=338){
					  if(digtemp!=315){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,power);
					  motor2(0,0);
					  motor3(0,power);
					  motor4(0,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=315;
				  	  }
			  }
			  else{
				  motor1(0,0);
				  motor2(0,0);
				  motor3(0,0);
				  motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
				 // digtemp=1000;
			  }

				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
		  break;



		  case 100:
				xprintf("E1=%d",TIM1->CNT);
				xprintf(" E2=%d",TIM3->CNT);
				xprintf(" E3=%d",TIM4->CNT);
				xprintf(" E4=%d",TIM5->CNT);
			  cnt[0]=abs((TIM4->CNT)-30000);
			  cnt[1]=abs((TIM5->CNT)-30000);
			  cnt[2]=abs((TIM1->CNT)-30000);
			  cnt[3]=abs((TIM3->CNT)-30000);
			  cnt_temp[0]=cnt[0];
			  cnt_temp[1]=0;
			  if(cnt_temp[0]<cnt[1]){
				  cnt_temp[0]=cnt[1];
				  cnt_temp[1]=1;
			  }
			 if(cnt_temp[0]<cnt[2]){
				  cnt_temp[0]=cnt[2];
				  cnt_temp[1]=2;
			  }
			  if(cnt_temp[0]<cnt[3]){
				  cnt_temp[0]=cnt[3];
				  cnt_temp[1]=3;
			  }


			  if(cnt_temp[1]==0){
				  power_caluculate[0]=1;
				  power_caluculate[1]=1+(float)(cnt[0]-cnt[1])/(float)cnt[0];
				  power_caluculate[2]=1+(float)(cnt[0]-cnt[2])/(float)cnt[0];
				  power_caluculate[3]=1+(float)(cnt[0]-cnt[3])/(float)cnt[0];
			  }
			  else if(cnt_temp[1]==1){
				  power_caluculate[0]=1+(float)(cnt[1]-cnt[0])/(float)cnt[1];
				  power_caluculate[1]=1;
				  power_caluculate[2]=1+(float)(cnt[1]-cnt[2])/(float)cnt[1];
				  power_caluculate[3]=1+(float)(cnt[1]-cnt[3])/(float)cnt[1];
			  }
			  else if(cnt_temp[1]==2){
				  power_caluculate[0]=1+(float)(cnt[2]-cnt[0])/(float)cnt[2];
				  power_caluculate[1]=1+(float)(cnt[2]-cnt[1])/(float)cnt[2];
				  power_caluculate[2]=1;
				  power_caluculate[3]=1+(float)(cnt[2]-cnt[3])/(float)cnt[2];
			  }
			  else if(cnt_temp[1]==3){
				  power_caluculate[0]=1+(float)(cnt[3]-cnt[0])/(float)cnt[3];
				  power_caluculate[1]=1+(float)(cnt[3]-cnt[1])/(float)cnt[3];
				  power_caluculate[2]=1+(float)(cnt[3]-cnt[2])/(float)cnt[3];
				  power_caluculate[3]=1;
			  }

			 if(cnt_temp[0]==0){
				 power_caluculate[0]=1;
				 power_caluculate[1]=1;
				 power_caluculate[2]=1;
				 power_caluculate[3]=1;

			 }


				xprintf(" P1=%d",(int)((float)power_caluculate[0]*1000));
				xprintf(" P2=%d",(int)((float)power_caluculate[1]*1000));
				xprintf(" P3=%d",(int)((float)power_caluculate[2]*1000));
				xprintf(" P4=%d\r\n",(int)((float)power_caluculate[3]*1000));

			  if(digree>=0 && digree<=360){
				  if(digree<=23 || digree>=338){
					if(digtemp!=0){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							  power_caluculate[0]=1;
							  power_caluculate[1]=1;
							  power_caluculate[2]=1;
							  power_caluculate[3]=1;
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
					}
					motor1(0,power*power_caluculate[0]);
					motor2(0,power*power_caluculate[1]);
					motor3(0,power*power_caluculate[2]);
					motor4(0,power*power_caluculate[3]);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=0;
				  }
				  else if(digree>23 && digree<=68){
					  if(digtemp!=45){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,0);
					  motor2(0,power*power_caluculate[1]);
					  motor3(0,0);
					  motor4(0,power*power_caluculate[3]);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=45;
				  }
				  else if(digree>68 && digree<=113){
					  if(digtemp!=90){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(power*power_caluculate[0],0);
					  motor2(0,power*power_caluculate[1]);
					  motor3(power*power_caluculate[2],0);
					  motor4(0,power*power_caluculate[3]);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=90;
				  }
				  else if(digree>113 && digree<=158){
					  if(digtemp!=135){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(power*power_caluculate[0],0);
					  motor2(0,0);
					  motor3(power*power_caluculate[2],0);
					  motor4(0,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=135;
				  }
				  else if(digree>158 && digree<=203){
					  if(digtemp!=180){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(power*power_caluculate[0],0);
					  motor2(power*power_caluculate[1],0);
					  motor3(power*power_caluculate[2],0);
					  motor4(power*power_caluculate[3],0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=180;
				  }
				  else if(digree>203 && digree<=248){
					  if(digtemp!=225){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,0);
					  motor2(power*power_caluculate[1],0);
					  motor3(0,0);
					  motor4(power*power_caluculate[3],0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=225;
				  }
				  else if(digree>248 && digree<=293){
					  if(digtemp!=270){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,power*power_caluculate[0]);
					  motor2(power*power_caluculate[1],0);
					  motor3(0,power*power_caluculate[2]);
					  motor4(power*power_caluculate[3],0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=270;
				  }
				  else if(digree>293 && digree<=338){
					  if(digtemp!=315){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
						  power_caluculate[0]=1;
						  power_caluculate[1]=1;
						  power_caluculate[2]=1;
						  power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  motor1(0,power*power_caluculate[0]);
					  motor2(0,0);
					  motor3(0,power*power_caluculate[2]);
					  motor4(0,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=315;
				  	  }
			  }
			  else{
				  motor1(0,0);
				  motor2(0,0);
				  motor3(0,0);
				  motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
				 // digtemp=1000;
			  }
			  TIM1->CNT=30000;
			  TIM3->CNT=30000;
			  TIM4->CNT=30000;
			  TIM5->CNT=30000;
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);
		  break;



		  case 125:
				xprintf("E1=%d",TIM1->CNT);
				xprintf(" E2=%d",TIM3->CNT);
				xprintf(" E3=%d",TIM4->CNT);
				xprintf(" E4=%d",TIM5->CNT);
			  cnt[0]=abs((TIM4->CNT)-30000);
			  cnt[1]=abs((TIM5->CNT)-30000);
			  cnt[2]=abs((TIM1->CNT)-30000);
			  cnt[3]=abs((TIM3->CNT)-30000);
			  cnt_temp[0]=cnt[0];
			  cnt_temp[1]=0;
			  if(cnt_temp[0]<cnt[1]){
				  cnt_temp[0]=cnt[1];
				  cnt_temp[1]=1;
			  }
			 if(cnt_temp[0]<cnt[2]){
				  cnt_temp[0]=cnt[2];
				  cnt_temp[1]=2;
			  }
			  if(cnt_temp[0]<cnt[3]){
				  cnt_temp[0]=cnt[3];
				  cnt_temp[1]=3;
			  }


			  if(cnt_temp[1]==0){
				  power_caluculate[0]=1;
				  power_caluculate[1]=1+(float)(cnt[0]-cnt[1])/(float)cnt[0];
				  power_caluculate[2]=1+(float)(cnt[0]-cnt[2])/(float)cnt[0];
				  power_caluculate[3]=1+(float)(cnt[0]-cnt[3])/(float)cnt[0];
			  }
			  else if(cnt_temp[1]==1){
				  power_caluculate[0]=1+(float)(cnt[1]-cnt[0])/(float)cnt[1];
				  power_caluculate[1]=1;
				  power_caluculate[2]=1+(float)(cnt[1]-cnt[2])/(float)cnt[1];
				  power_caluculate[3]=1+(float)(cnt[1]-cnt[3])/(float)cnt[1];
			  }
			  else if(cnt_temp[1]==2){
				  power_caluculate[0]=1+(float)(cnt[2]-cnt[0])/(float)cnt[2];
				  power_caluculate[1]=1+(float)(cnt[2]-cnt[1])/(float)cnt[2];
				  power_caluculate[2]=1;
				  power_caluculate[3]=1+(float)(cnt[2]-cnt[3])/(float)cnt[2];
			  }
			  else if(cnt_temp[1]==3){
				  power_caluculate[0]=1+(float)(cnt[3]-cnt[0])/(float)cnt[3];
				  power_caluculate[1]=1+(float)(cnt[3]-cnt[1])/(float)cnt[3];
				  power_caluculate[2]=1+(float)(cnt[3]-cnt[2])/(float)cnt[3];
				  power_caluculate[3]=1;
			  }

			 if(cnt_temp[0]==0){
				 power_caluculate[0]=1;
				 power_caluculate[1]=1;
				 power_caluculate[2]=1;
				 power_caluculate[3]=1;

			 }


				xprintf(" P1=%d",(int)((float)power_caluculate[0]*1000));
				xprintf(" P2=%d",(int)((float)power_caluculate[1]*1000));
				xprintf(" P3=%d",(int)((float)power_caluculate[2]*1000));
				xprintf(" P4=%d\r\n",(int)((float)power_caluculate[3]*1000));


				if(cnt_temp[0]<500){
					power_caluculate[0]=1;
					power_caluculate[1]=1;
					power_caluculate[2]=1;
					power_caluculate[3]=1;
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);

				}
				else{
					HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,1);
				}

				  power1_temp=(float)power*power_caluculate[0];
				  power2_temp=(float)power*power_caluculate[1];
				  power3_temp=(float)power*power_caluculate[2];
				  power4_temp=(float)power*power_caluculate[3];

			  if(digree>=0 && digree<=360){
				  if(digree>=0 && digree<=45){
					if(digtemp!=0){
							motor1(0,0);
							motor2(0,0);
							motor3(0,0);
							motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
							xprintf("bleak now\r\n");
							HAL_Delay(bleak_time);
					}
					  power1=(float)arm_sin_f32((45-digree)*M_PI/180)*power1_temp;
					  power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*-1*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					motor1(0,power1);
					motor2(0,power2);
					motor3(0,power3);
					motor4(0,power4);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=0;
				  }
				  else if(digree>45 && digree<=90){
					  if(digtemp!=90){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }


					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power1_temp;
					  power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(power1,0);
					  motor2(0,power2);
					  motor3(power3,0);
					  motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=90;
				  }
				  else if(digree>90 && digree<=135){
					  if(digtemp!=90){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power1_temp;
					  power2=(float)arm_sin_f32((135-digree)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*-1*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(power1,0);
					  motor2(0,power2);
					  motor3(power3,0);
					  motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=90;
				  }
				  else if(digree>135 && digree<=180){
					  if(digtemp!=180){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power1_temp;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(power1,0);
					  motor2(power2,0);
					  motor3(power3,0);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=180;
				  }
				  else if(digree>180 && digree<=225){
					  if(digtemp!=180){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*power1_temp;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((225-digree)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(power1,0);
					  motor2(power2,0);
					  motor3(power3,0);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=180;
				  }
				  else if(digree>225 && digree<=270){
					  if(digtemp!=270){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power1_temp;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(0,power1);
					  motor2(power2,0);
					  motor3(0,power3);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=270;
				  }
				  else if(digree>270 && digree<=315){
					  if(digtemp!=270){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					}
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power1_temp;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*power2_temp;
					  power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((315-digree)*M_PI/180)*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(0,power1);
					  motor2(power2,0);
					  motor3(0,power3);
					  motor4(power4,0);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=270;
				  }
				  else if(digree>315 && digree<=360){
					  if(digtemp!=0){
						  motor1(0,0);
						  motor2(0,0);
						  motor3(0,0);
						  motor4(0,0);
							power_caluculate[0]=1;
							power_caluculate[1]=1;
							power_caluculate[2]=1;
							power_caluculate[3]=1;
							HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
						xprintf("bleak now\r\n");
						  HAL_Delay(bleak_time);
					  }
					  power1=(float)arm_sin_f32((digree-45)*M_PI/180)*-1*power1_temp;
					  power2=(float)arm_sin_f32((digree-135)*M_PI/180)*-1*power2_temp;
					  power3=(float)arm_sin_f32((digree-225)*M_PI/180)*power3_temp;
					  power4=(float)arm_sin_f32((digree-315)*M_PI/180)*power4_temp;
					  temp1=max(power1,power2);
					  temp2=max(power3,temp1);
					  y=max(power4,temp2);
					  power1=power1*((float)power1_temp/y);
					  power2=power2*((float)power2_temp/y);
					  power3=power3*((float)power3_temp/y);
					  power4=power4*((float)power4_temp/y);
					  motor1(0,power1);
					  motor2(0,power2);
					  motor3(0,power3);
					  motor4(0,power4);
						HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
					  digtemp=0;
				  	  }
			  }
			  else{
				  motor1(0,0);
				  motor2(0,0);
				  motor3(0,0);
				  motor4(0,0);
					power_caluculate[0]=1;
					power_caluculate[1]=1;
					power_caluculate[2]=1;
					power_caluculate[3]=1;
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
				  //digtemp=1000;
			  }
			  TIM1->CNT=30000;
			  TIM3->CNT=30000;
			  TIM4->CNT=30000;
			  TIM5->CNT=30000;

		  break;


		  case 150:
				//LS
				if(digtemp!=2000){
					motor1(0,0);
					motor2(0,0);
					motor3(0,0);
					motor4(0,0);
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
					HAL_Delay(bleak_time);
					xprintf("bleak now\r\n");
				}

				motor1(0,power);
				motor2(0,power);
				motor3(power,0);
				motor4(power,0);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
				digtemp=2000;
				HOUI_def=JY901_def_set();
		  break;

		  case 200:
				//RS
				if(digtemp!=3000){
					motor1(0,0);
					motor2(0,0);
					motor3(0,0);
					motor4(0,0);
					xprintf("bleak now\r\n");
					HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
					HAL_Delay(bleak_time);
				}
				motor1(power,0);
				motor2(power,0);
				motor3(0,power);
				motor4(0,power);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
				digtemp=3000;
				HOUI_def=JY901_def_set();
		  break;

		  default:
				motor1(0,0);
			    motor2(0,0);
			    motor3(0,0);
			    motor4(0,0);
				HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_15,0);
				//digtemp=1000;
		  break;
		  }

	}

int max(int a,int b){
	if(a>b){return a;}
	else{return b;}
}
long map_m(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	}
