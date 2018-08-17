/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
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
#include "stm32f7xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "management.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define servonumber 3
uint8_t flug_Rxdata=0;
uint8_t TPIPConnect=0;
uint8_t data[7+servonumber],tempdata[7+servonumber];
uint8_t Rxbuf[8+servonumber];
uint8_t Rxdetatemp;
uint8_t Txdata[1];
/* Private variables ---------------------------------------------------------*/
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void Calibration();
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
	//Tim1 14.4KHz
	//Tim2 50Hz
	//Tim4 50Hz
	//Tim6 20Hz
	//Tim9 50Hz
  /* USER CODE END 1 */

  /* Enable I-Cache-------------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache-------------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_TIM2_Init();
  MX_I2C3_Init();
  MX_TIM4_Init();
  MX_TIM9_Init();
  MX_TIM6_Init();
  MX_USART3_UART_Init();
  //MX_IWDG_Init();

  /* USER CODE BEGIN 2 */
  	if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7)==1){
  	  MX_IWDG_Init();
  	}
  	else{
  		beep(10,30,30);
  	}
  	servo(180,180,180,90,90,90,90,90);
    motor_move(0,0,0,0);
	slider(10,0);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);
    HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,0);
    HAL_TIM_Base_Start_IT(&htim6);
    if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)Rxbuf,(8+servonumber)) != HAL_OK){Error_Handler();}

    xprintf_init(&huart2);
    JY901_init(&hi2c1);
    DFPlayer_init(&huart3);
    oled_i2c_to_oled(&hi2c1);

    HAL_IWDG_Refresh(&hiwdg);
    oled_returnhome();
    oled_puts("Is The Order a");
    oled_setcursor(1,2);
    oled_puts("Rescue Robot?");
    HAL_Delay(700);
    DFPlayer_setvolume(0x25);
    HAL_Delay(100);
    DFPlayer_playmp3(4);
    HAL_IWDG_Refresh(&hiwdg);
  	servo(180,180,180,90,90,90,90,90);
    HAL_Delay(1000);
    HAL_IWDG_Refresh(&hiwdg);
    HAL_Delay(1000);
    HAL_IWDG_Refresh(&hiwdg);
    oled_clear();
    CCS811_init(&hi2c1);

    HAL_IWDG_Refresh(&hiwdg);
   while(TPIPConnect==0){
		  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,1);
	   if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==0){
		   if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7)==0){
		   Calibration();
		   HAL_IWDG_Refresh(&hiwdg);
		   }
		   else{
		   oled_returnhome();
		   oled_puts("waiting for     ");
		   oled_setcursor(1,0);
		   oled_puts("Calibration     ");
		   HAL_Delay(5);
		   HAL_IWDG_Refresh(&hiwdg);
	   }
	   }
	   else{
		   HAL_IWDG_Refresh(&hiwdg);
	  oled_returnhome();
	  oled_puts("waiting for     ");
	  oled_setcursor(1,0);
	  oled_puts("      connection");
	  if((environment_get()&0x00000001)==1){
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,1);
	 }
	 else{
		  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,0);
	 }
	  HOUI=JY901_yaw_get(HOUI_def);
	  xprintf("angle=%d",HOUI);
	  xprintf(" CO2=%d",CCS811_CO2_get());
	  for(int i=0; i<(8+servonumber);i++){xprintf(" %d=%d",i,Rxbuf[i]);}
	  xprintf("\r\n");
	  HAL_IWDG_Refresh(&hiwdg);
	  HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
	   servo(180,180,180,90,90,90,90,90);
	  motor_move(0,0,0,0);
	  slider(10,0);
	 }
  }
    DFPlayer_playmp3(5);
    oled_clear();
    oled_returnhome();
    oled_puts("Connect to TPIP ");
    oled_setcursor(1,0);
    oled_puts("      Success!!!");
    beep(3,50,50);
	HAL_Delay(150);
	counttime=0;
	HOUI_def=JY901_def_set();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_2)==0){
	 		   if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_7)==0){
	 		   Calibration();
	 		  HAL_IWDG_Refresh(&hiwdg);}
	 		   else{
	 		   oled_returnhome();
	 		   oled_puts("waiting for     ");
	 		   oled_setcursor(1,0);
	 		   oled_puts("Calibration     ");
	 		   servo(180,180,180,90,90,90,90,90);
			   slider(10,0);
	 		   motor_move(0,0,0,0);
	 		   HAL_IWDG_Refresh(&hiwdg);
	 		   HAL_Delay(5);
	 		   }
	  }
	  else{
	  if(TPIPConnect==1){
		  motor_move(data[0],data[1],data[2],data[3]);
		  if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2)==0){//flont
			  if(data[4]==100){
				  slider(10,0);
			  }
			  else{
				  slider(data[4],data[5]);
			  }
		  }
		  else if(HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)==0){//back
			  if(data[4]==200){
				  slider(10,0);
			  }
			  else{
				  slider(data[4],data[5]);
			  }
		  }
		  else{
			  slider(data[4],data[5]);
		  }
		  servo(data[6],data[6],data[6],data[7],data[8],90,90,90);

		  //LCD•\Ž¦
		  if(flug_Rxdata==1){
		  oled_returnhome();
		  oled_puts("connection      ");
		  oled_setcursor(1,0);
		switch(data[0]){
		case 10:
			switch (data[2]) {
				case 100:oled_puts("mR = 0  mL = +  ");break;
				case 200:oled_puts("mR = 0  mL = -  ");break;
				case 150:oled_puts("mR = 0  mL = +  ");break;
				case 250:oled_puts("mR = 0  mL = -  ");	break;
				case 10: oled_puts ("mR = 0  mL = 0  ");	break;
			}
		break;

		case 100:
			switch(data[2]){
				case 100:oled_puts("mR = +  mL = +  ");break;
				case 200:oled_puts("mR = +  mL = -  ");break;
				case 150:oled_puts("mR = +  mL = +  ");break;
				case 250:oled_puts("mR = +  mL = -  ");break;
				case 10: oled_puts("mR = +  mL = 0  ");break;
			}
		break;

		case 200:
			switch(data[2]){
				case 100:oled_puts("mR = -  mL = +  ");break;
				case 200:oled_puts("mR = -  mL = -  ");	break;
				case 150:oled_puts("mR = -  mL = +  ");break;
				case 250:oled_puts("mR = -  mL = -  ");	break;
				case 10: oled_puts("mR = -  mL = 0  ");break;
			}
		break;

		case 150:
			switch(data[2]){
				case 100:oled_puts("mR = +  mL = +  ");break;
				case 200:oled_puts("mR = +  mL = -  ");break;
				case 150:oled_puts("mR = +  mL = +  ");break;
				case 250:oled_puts("mR = +  mL = -  ");break;
				case 10:oled_puts("mR = +  mL = 0  ");break;
			}
		break;

		case 250:
			switch(data[2]){
				case 100:oled_puts("mR = -  mL = +  ");break;
				case 200:oled_puts("mR = -  mL = -  ");	break;
				case 150:oled_puts("mR = -  mL = +  ");break;
				case 250:oled_puts("mR = -  mL = -  ");	break;
				case 10:oled_puts("mR = -  mL = 0  ");break;
			}
			break;
		default:oled_puts("no data         ");break;
		}

		  //xprintf(" SW1=%d",HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2));
		  //xprintf(" SW2=%d",HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3));
		  /*xprintf(" D0=%d",data[0]);
		  xprintf(" D1=%d",data[1]);
		  xprintf(" D2=%d",data[2]);
		  xprintf(" D3=%d",data[3]);
		  xprintf(" D4=%d",data[4]);
		  xprintf(" D5=%d",data[5]);
		  xprintf(" D6=%d",data[6]);
		  xprintf(" D7=%d",data[7]);
		  xprintf(" D8=%d",data[8]);*/
		  xprintf(" CO2=%d",CCS811_CO2_get());
		  //xprintf(" motorR=%d",motorR);
		  //xprintf(" motorL=%d",motorL);
		  xprintf(" Hd=%d",HOUI_def);
		  xprintf(" H=%d",HOUI);
		  xprintf(" D9=%d\r\n",data[9]);

		flug_Rxdata=0;
		}
		for(int count=0;count<(7+servonumber);count++){
			tempdata[count]=data[count];
		}
		if(counttime>70){
				  if((environment_get()&0x00000001)==1){
					  DFPlayer_playmp3(2);
					  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,1);
				 }
				 else{
					  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_11,0);
					  DFPlayer_playmp3(1);
				 }
					counttime=0;
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_12);
				}

		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,1);
	  }
	  else{
		  motor_move(0,0,0,0);
		  servo(tempdata[6],tempdata[6],tempdata[6],tempdata[7]
			   ,tempdata[8],90,90,90);
		  for(int i=0; i<(8+servonumber);i++){xprintf(" %d=%d",i,Rxbuf[i]);}
		  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_14,0);
		  oled_returnhome();
		  oled_puts("disconnection   ");
		  oled_setcursor(1,0);
		  oled_puts("all motor stop  ");
		  beep(1,300,100);
	  }
	 }
	  HAL_IWDG_Refresh(&hiwdg);
	  HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_10);
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

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
  RCC_OscInitStruct.PLL.PLLN = 216;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2
                              |RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C3;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c3ClockSelection = RCC_I2C3CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
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


void Calibration(){
	DFPlayer_playmp3(8);
  	servo(180,180,180,90,90,90,90,90);
	motor_move(0,0,0,0);
    slider(10,0);
	oled_clear();
	oled_returnhome();
	oled_puts("Angular velocity");
	oled_setcursor(1,0);
	oled_puts("    Calibration ");
	JY901_calibration(1600,1);
	oled_clear();
	oled_returnhome();
	oled_puts("Magnetic");
	oled_setcursor(1,0);
	oled_puts(" Calibration  RS");
	xprintf("houi cab\r\n");
	motor_move(100,100,200,100);
	JY901_calibration(10000,2);
	oled_clear();
	oled_returnhome();
	oled_puts("Calibration End ");
	motor_move(0,0,0,0);
	xprintf("cab end\r\n");
	JY901_calibration(100,3);
	xprintf("save\r\n");
	JY901_calibration(100,4);
	DFPlayer_stopmp3();
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		 counttime++;
	 if(Rxdetatemp!=data[servonumber+6] || HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)==0){
		 TPIPConnect=1;
		 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15,1);
	 }
	 else{
		 TPIPConnect=0;
		 HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_15);
	 }
	 Rxdetatemp=data[servonumber+6];
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	int j = 0;
	while (Rxbuf[j] != 254 && j<(7+servonumber)) {
		j++;
	}
	if(j>=(7+servonumber)){
		for (int k = 0; k < 6; k++) {
			data[k] = 0;
		}
		for(int k=6;k<(6+servonumber);k++){
			data[k]=90;
		}
		data[6+servonumber]=0;
	}
	else {
		for (int k = 0; k < (7+servonumber); k++) {
			if ((j + k) >= (7+servonumber)) {
				data[k] = Rxbuf[k - ((7+servonumber) - j)];
			}
			else {
				data[k] = Rxbuf[j + k + 1];
			}
		}
		flug_Rxdata=1;
	}
	}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_9,1);
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
