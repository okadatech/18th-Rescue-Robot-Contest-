
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "CCS811.h"
#include "DFplayer_Mini_mp3.h"
#include "xprintf.h"
#define delay_time 80
#define SERVO_LOW 380
#define SERVO_HIGH 1120

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfigOC;
TIM_MasterConfigTypeDef sMasterConfig;

long map(long x, long in_min, long in_max, long out_min, long out_max);
void servo(uint8_t servo1,uint8_t servo2,uint8_t servo3);
void motor(uint8_t R1,uint8_t R2,uint8_t L1,uint8_t L2);
void camera(uint8_t num);
uint16_t CGdata[2];
uint8_t Rx[11],Tx[4];
uint8_t motorR,motorL;
uint8_t TPIP=0,Rxtemp;
uint8_t data[11],vtemp;
uint32_t counttime=0;
uint8_t flug=0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();
  MX_USART3_UART_Init();
  MX_TIM6_Init();
  MX_IWDG_Init();
  /* USER CODE BEGIN 2 */
  HAL_IWDG_Refresh(&hiwdg);
  servo(90,90,90);
  xprintf_init(&huart2);
  HAL_TIM_Base_Start_IT(&htim6);
  HAL_IWDG_Refresh(&hiwdg);
  CCS811_init(&hi2c1);
  DFPlayer_init(&huart3);
  HAL_IWDG_Refresh(&hiwdg);
  DFPlayer_setvolume(0x7);
  HAL_Delay(500);
  HAL_IWDG_Refresh(&hiwdg);


  if(HAL_UART_Receive_DMA(&huart1,(uint8_t*)Rx,sizeof(Rx))!=HAL_OK){
	  Error_Handler();
  }
  DFPlayer_playmp3(0);
  while(TPIP==0){
    motor(10,0,10,0);
    HAL_IWDG_Refresh(&hiwdg);
  }
  DFPlayer_playmp3(1);
  HAL_IWDG_Refresh(&hiwdg);
  HAL_Delay(2000);
  HAL_IWDG_Refresh(&hiwdg);
  DFPlayer_stopmp3();
  DFPlayer_setvolume(0x30);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  CGdata[0]=CCS811_CO2_get();
	  CGdata[1]=CCS811_TVOCs_get();
	  for(int i=0;i<11;i++){
		  xprintf(" data[%d]:%d",i,data[i]);
	  }
	  xprintf(" CO2:%d",CGdata[0]);
	  xprintf(" gas:%d",CGdata[1]);
	  xprintf("\n");
	  if(TPIP==0){
		  motor(10,0,10,0);
		  HAL_IWDG_Refresh(&hiwdg);
	  }
	  else if(TPIP==1){

		  camera(data[8]);
		  motor(data[1], data[2], data[3], data[4]);
		  servo(data[5],data[6],data[7]);
		  HAL_IWDG_Refresh(&hiwdg);

			if(flug==1){
				switch (data[9]) {
					case 1:
						DFPlayer_playmp3(2);
						break;
					case 2:
						DFPlayer_playmp3(3);
						break;
					case 3:
						DFPlayer_playmp3(4);
						break;
					case 4:
						DFPlayer_playmp3(5);
						break;
					default:
						DFPlayer_stopmp3();
						break;
				}
				flug=0;
			}

	  }
	  HAL_IWDG_Refresh(&hiwdg);


  }

  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Configure the main internal regulator output voltage 
    */
  __HAL_RCC_PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 180;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Activate the Over-Drive mode 
    */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(Rxtemp!=data[10]){
		TPIP=1;
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,1);
	}
	else{
		TPIP=0;
		HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,0);
	}
	Rxtemp=data[10];
	counttime++;
	if(counttime>50){
		flug=1;
		counttime=0;
	}
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
	  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void servo(uint8_t servo1,uint8_t servo2,uint8_t servo3){
	  sConfigOC.Pulse = map(servo1,0,180,SERVO_LOW,SERVO_HIGH);
	  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	 	  {
	 	  Error_Handler();
	   }
	   if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1) != HAL_OK)
	   {
	 	  Error_Handler();
	   }
	  sConfigOC.Pulse = map(servo2,0,180,SERVO_LOW,SERVO_HIGH);
	  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	   {
		  Error_Handler();
	   }
	  if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2) != HAL_OK)
	  {
		  Error_Handler();
	  }
	  sConfigOC.Pulse = map(servo3,0,180,SERVO_LOW,SERVO_HIGH);
	  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
	  {
	 	  Error_Handler();
	   }
	   if (HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3) != HAL_OK)
	   {
	 	  Error_Handler();
	   }

}

void camera(uint8_t num){
	  switch(num){
	  	  case 0:
	  		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
	  		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,0);
	  		  break;
	  	  case 1:
	  			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
	  			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,1);
	  			  break;
	  	  case 2:
	  			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
	  			  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,0);
	  			  break;
	  	  default:
	  		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
	  		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_12,0);
	  		  break;

	  }
}

void motor_move(uint32_t pwm1,uint32_t pwm2,GPIO_PinState pin1,GPIO_PinState pin2,GPIO_PinState pin3,GPIO_PinState pin4){
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,pin1);
    HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,pin2);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,pin3);
	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,pin4);
	sConfigOC.Pulse = pwm1;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
	   Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1) != HAL_OK)
	{
	   Error_Handler();
	 }

	sConfigOC.Pulse = pwm2;
	if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
	{
	   Error_Handler();
	}
	if (HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2) != HAL_OK)
	{
	   Error_Handler();
	}
}

void motor(uint8_t L1,uint8_t L2,uint8_t R1,uint8_t R2){

	if(R2<=0){
		motorR=0;
	}
	else{
		motorR = R2-1;
	}
	if(L2<=0){
		motorL=0;
	}
	else{
		motorL = L2-1;
	}

	if (R2 >= 0 && L2 >= 0) {
		switch (R1) {
		case 10:
			switch (L1) {
			case 10:
				motor_move(1000, 1000, 0, 0, 0, 0);
				break;

			case 100:
				motor_move(0, (motorL * 3.5), 0, 0, 1, 0);
				break;

			case 200:
				motor_move(0, (motorL * 3.5), 0, 0, 0, 1);
				break;

			default:
				motor_move(1000, 1000, 0, 0, 0, 0);
				break;
			}
		break;

		case 100:

			switch (L1) {
			case 10:
				motor_move((motorR * 4), 0, 1, 0, 0, 0);
				break;

			case 100:
				motor_move((motorR * 4), (motorL * 3.5), 1, 0, 1, 0);
				break;


			case 200:
				motor_move((motorR * 4), (motorL * 3.5), 1, 0, 0, 1);
				break;

			default:
				motor_move(1000, 1000, 0, 0, 0, 0);
				break;
			}
		break;

		case 200:
			switch (L1) {
			case 10:
				motor_move((motorR * 4), 0, 0, 1, 0, 0);
				break;

			case 100:
				motor_move((motorR * 4), (motorL * 3.5), 0, 1, 1, 0);
				break;

			case 200:
				motor_move((motorR * 4), (motorL * 3.5), 0, 1, 0, 1);
				break;

			default:
				motor_move(1000, 1000, 0, 0, 0, 0);
				break;
			}
		break;


		default:
			motor_move(1000,1000,0,0,0,0);
		break;
		}
	}
	else{
		motor_move(1000,1000,0,0,0,0);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	if(Rx[0]==254){
		data[0]=Rx[0];
		data[1]=Rx[1];
		data[2]=Rx[2];
		data[3]=Rx[3];
		data[4]=Rx[4];
		data[5]=Rx[5];
		data[6]=Rx[6];
		data[7]=Rx[7];
		data[8]=Rx[8];
		data[9]=Rx[9];
		data[10]=Rx[10];
	}
	else if(Rx[1]==254){
		data[0]=Rx[1];
		data[1]=Rx[2];
		data[2]=Rx[3];
		data[3]=Rx[4];
		data[4]=Rx[5];
		data[5]=Rx[6];
		data[6]=Rx[7];
		data[7]=Rx[8];
		data[8]=Rx[9];
		data[9]=Rx[10];
		data[10]=Rx[0];
	}
	else if(Rx[2]==254){
		data[0]=Rx[2];
		data[1]=Rx[3];
		data[2]=Rx[4];
		data[3]=Rx[5];
		data[4]=Rx[6];
		data[5]=Rx[7];
		data[6]=Rx[8];
		data[7]=Rx[9];
		data[8]=Rx[10];
		data[9]=Rx[0];
		data[10]=Rx[1];
	}
	else if(Rx[3]==254){
		data[0]=Rx[3];
		data[1]=Rx[4];
		data[2]=Rx[5];
		data[3]=Rx[6];
		data[4]=Rx[7];
		data[5]=Rx[8];
		data[6]=Rx[9];
		data[7]=Rx[10];
		data[8]=Rx[0];
		data[9]=Rx[1];
		data[10]=Rx[2];
	}
	else if(Rx[4]==254){
		data[0]=Rx[4];
		data[1]=Rx[5];
		data[2]=Rx[6];
		data[3]=Rx[7];
		data[4]=Rx[8];
		data[5]=Rx[9];
		data[6]=Rx[10];
		data[7]=Rx[0];
		data[8]=Rx[1];
		data[9]=Rx[2];
		data[10]=Rx[3];
	}
	else if(Rx[5]==254){
		data[0]=Rx[5];
		data[1]=Rx[6];
		data[2]=Rx[7];
		data[3]=Rx[8];
		data[4]=Rx[9];
		data[5]=Rx[10];
		data[6]=Rx[0];
		data[7]=Rx[1];
		data[8]=Rx[2];
		data[9]=Rx[3];
		data[10]=Rx[4];
	}
	else if(Rx[6]==254){
		data[0]=Rx[6];
		data[1]=Rx[7];
		data[2]=Rx[8];
		data[3]=Rx[9];
		data[4]=Rx[10];
		data[5]=Rx[1];
		data[6]=Rx[2];
		data[7]=Rx[3];
		data[8]=Rx[4];
		data[9]=Rx[5];
		data[10]=Rx[6];
	}
	else if(Rx[7]==254){
		data[0]=Rx[7];
		data[1]=Rx[8];
		data[2]=Rx[9];
		data[3]=Rx[10];
		data[4]=Rx[0];
		data[5]=Rx[1];
		data[6]=Rx[2];
		data[7]=Rx[3];
		data[8]=Rx[4];
		data[9]=Rx[5];
		data[10]=Rx[6];
	}
	else if(Rx[8]==254){
		data[0]=Rx[8];
		data[1]=Rx[9];
		data[2]=Rx[10];
		data[3]=Rx[0];
		data[4]=Rx[1];
		data[5]=Rx[2];
		data[6]=Rx[3];
		data[7]=Rx[4];
		data[8]=Rx[5];
		data[9]=Rx[6];
		data[10]=Rx[7];
	}
	else if(Rx[9]==254){
		data[0]=Rx[9];
		data[1]=Rx[10];
		data[2]=Rx[0];
		data[3]=Rx[1];
		data[4]=Rx[2];
		data[5]=Rx[3];
		data[6]=Rx[4];
		data[7]=Rx[5];
		data[8]=Rx[6];
		data[9]=Rx[7];
		data[10]=Rx[8];
	}
	else if(Rx[10]==254){
		data[0]=Rx[10];
		data[1]=Rx[0];
		data[2]=Rx[1];
		data[3]=Rx[2];
		data[4]=Rx[3];
		data[5]=Rx[4];
		data[6]=Rx[5];
		data[7]=Rx[6];
		data[8]=Rx[7];
		data[9]=Rx[8];
		data[10]=Rx[9];
	}
	Tx[0]=(uint8_t)((CGdata[0]&0b0000000011111111));
	Tx[1]=(uint8_t)((CGdata[0]&0b1111111100000000)>>8);
	Tx[2]=(uint8_t)((CGdata[1]&0b0000000011111111));
	Tx[3]=(uint8_t)((CGdata[1]&0b1111111100000000)>>8);
	HAL_UART_Transmit(&huart1,(uint8_t*)Tx,sizeof(Tx),0xFF);
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
