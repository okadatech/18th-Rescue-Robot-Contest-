
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
/* Private variables ---------------------------------------------------------*/
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
long map(long x, long in_min, long in_max, long out_min, long out_max) ;
void main_run();
void sens_test();
void comu_test();
void test_mode();
void demo_mode();
void calib_mode();
/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define Servonumber 4
#define debug 1
uint8_t Flug_Rxdata=0;
uint8_t Rxbuf[Servonumber+11];
uint8_t TPIPConnect=0,Rxdetatemp=0;
uint8_t data[Servonumber+11-1],tempdata[Servonumber+11-1];
uint8_t SW[5];
uint8_t mode;
uint8_t motor[5];
int16_t servodata[Servonumber]={180,67,90,180};
int16_t servotemp[Servonumber]={180,67,90,180};
uint32_t uwDirectionCount1 = 0;
uint32_t uwDirectionCount2 = 0;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	 if(Rxdetatemp!=data[Servonumber+9] || HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0){
		 TPIPConnect=1;
		 HAL_GPIO_WritePin(GPIOE,GPIO_PIN_0,1);
	 }
	 else{
		 TPIPConnect=0;
		 HAL_GPIO_TogglePin(GPIOE,GPIO_PIN_0);
	 }
	 Rxdetatemp=data[Servonumber+9];
}

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
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_TIM8_Init();
  MX_TIM9_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM12_Init();
  MX_USART1_UART_Init();
  MX_USART2_UART_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM6_Init();
  MX_TIM1_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  //MX_IWDG_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
  xprintf_init(&huart2);
  xdev_out(uart_putc);
  oled_i2c_to_oled(&hi2c1);
  oled_returnhome();
  if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==1){
    	 MX_IWDG_Init();
  }
  else{
	  oled_puts("Debug mode");
	  oled_setcursor(1,0);
	  oled_puts("No init of iwdg");
	  beep(10,30,30);
	  HAL_Delay(200);
  }

  oled_clear();
  servo(180,67,90,180,180,90,90,90,90,90);
  motor_move(0,0,0,0);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1);
  JY901_init(&hi2c1);
  DFPlayer_init(&huart3);
  oled_returnhome();
  oled_puts("Is The Order a");
  oled_setcursor(1,2);
  oled_puts("Rescue Robot?");
  HAL_Delay(700);
  DFPlayer_setvolume(0x25);
  HAL_Delay(100);
  DFPlayer_playmp3(1);
  HAL_Delay(300);
  HAL_IWDG_Refresh(&hiwdg);
  HAL_Delay(1000);
  HAL_IWDG_Refresh(&hiwdg);
  HAL_Delay(600);
  HAL_IWDG_Refresh(&hiwdg);
  oled_clear();
  HAL_IWDG_Refresh(&hiwdg);
  HAL_TIM_Base_Start_IT(&htim6);
  if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)Rxbuf,(Servonumber + 11)) != HAL_OK)
  {
	  Error_Handler();
  }
  if(HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK)
  {
	  Error_Handler();
  }
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  TIM1->CNT=30000;
  Expand_flug=0;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  mofu:
	  mode=HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_12)*4+(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)*2)
			  +(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_14));
	  switch(mode){
	  case 1:
		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  oled_clear();
			  HOUI_def=JY901_def_set();
			  TIM1->CNT=30000;
			    uint32_t timeout=0;
			    while(encordermotor1(0) && timeout<10000000){
			    	timeout++;
			    	delayUs(1);
			    	HAL_IWDG_Refresh(&hiwdg);
			    }
			    sConfigOC.Pulse = 0;
			    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
			    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			    sConfigOC.Pulse = 0;
			    HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
			    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
			    timeout=0;
			  while(TPIPConnect==0){
			  	motor_move(0,0,0,0);
			  	oled_returnhome();
			  	oled_puts("main_run select ");
			  	oled_setcursor(1,0);
			  	oled_puts("waiting for TPIP");
			    /*xprintf(" S1=%d",HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3));
			    xprintf(" S2=%d",HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_1));
			    xprintf(" S3=%d",HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_12));
			    xprintf(" S4=%d",HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_10));*/
				xprintf(" 0=%d",Rxbuf[0]);
				xprintf(" 1=%d",Rxbuf[1]);
				xprintf(" 2=%d",Rxbuf[2]);
				xprintf(" 3=%d",Rxbuf[3]);
				xprintf(" 4=%d",Rxbuf[4]);
				xprintf(" 5=%d",Rxbuf[5]);
				xprintf(" 6=%d",Rxbuf[6]);
				xprintf(" 7=%d",Rxbuf[7]);
				xprintf(" 8=%d",Rxbuf[8]);
				xprintf(" 9=%d",Rxbuf[9]);
				xprintf(" 10=%d",Rxbuf[10]);
				xprintf(" 11=%d",Rxbuf[11]);
				xprintf(" 12=%d\r\n",Rxbuf[12]);
			  	if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==0){goto mofu;}
			  	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1);
			    HAL_IWDG_Refresh(&hiwdg);
			    HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			  	}
			    DFPlayer_playmp3(9);
			  	beep(3,50,50);
			  	 oled_clear();
			  	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  		if(TPIPConnect==1){
			  		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1);
			  		main_run();
			  		if(data[Servonumber+11-2]%11==0){
			  		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
			  		}
			  		if(data[Servonumber+11-2]%11==5){
			  		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0);
			  		}
			  	  }
			  	  else{
			  			HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);
			  			motor_move(0,0,0,0);
			  			servo(servotemp[0],servotemp[1],servotemp[2],servotemp[3],servotemp[3],
			  				90,90,90,90,90);
			  			sConfigOC.Pulse = 0;
			  			HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
			  			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			  			sConfigOC.Pulse = 0;
			  			HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
			  			HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
			  			oled_returnhome();
			  			oled_puts("main_run select");
			  			oled_setcursor(1,0);
			  			oled_puts("lost connection!");
			  			for(int i=0;i<13;i++){
			  				xprintf(" %d)%d",i,Rxbuf[i]);
			  			}
			  			/*
			  			for(int i=0;i<(Servonumber+11);i++){
			  				xprintf(" %d)%d",i,data[i]);
			  			}*/
			  			xprintf("\r\n");
					    DFPlayer_playmp3(12);
	  			  		beep(1,300,300);
		  			    HAL_IWDG_Refresh(&hiwdg);
	  			  		beep(1,300,300);
		  			    HAL_IWDG_Refresh(&hiwdg);
			  	  }
			  	  HAL_IWDG_Refresh(&hiwdg);
			  }
			  	sConfigOC.Pulse = 0;
			  	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1);
			  	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
			  	sConfigOC.Pulse = 0;
			  	HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3);
			  	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3) ;
		  		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0);
	  			motor_move(0,0,0,0);
	  			servo(servotemp[0],servotemp[1],servotemp[2],servotemp[3],servotemp[3],
	  				90,90,90,90,90);
		  }
		  else{
			  oled_returnhome();
			  oled_puts("main_run select");
			  oled_setcursor(1,0);
			  oled_puts("OK?     waiting ");
			  HAL_Delay(5);
			  HAL_IWDG_Refresh(&hiwdg);
		  }
	  break;

	  case 2:
			if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
				oled_clear();
				HOUI_def=JY901_def_set();
			    TIM1->CNT=30000;
		  		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);
				motor_move(0,0,0,0);
				  servo(180,67,90,180,180,90,90,90,90,90);
				while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
				oled_returnhome();
				oled_puts("Comu test select");
				oled_setcursor(1,0);
				oled_puts("running         ");

				for(int counttime1=0;counttime1<(Servonumber+11-1);counttime1++){
					xprintf(" data%d)%d",counttime1,data[counttime1]);
				}
				xprintf("\r\n");
				HAL_IWDG_Refresh(&hiwdg);
				HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
				}
			}
			else{
				oled_returnhome();
				oled_puts("Comu test select");
				oled_setcursor(1,0);
				oled_puts("OK?     waiting ");
				HAL_IWDG_Refresh(&hiwdg);
				HAL_Delay(5);
			}
	  break;

	  case 3:
		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  oled_clear();
			  HOUI_def=JY901_def_set();
			    TIM1->CNT=30000;
			    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);
			  	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  	oled_returnhome();
			  	oled_puts("sens_test select");
			  	oled_setcursor(1,0);
			  	oled_puts("Running          ");
				sens_test();
				  HAL_IWDG_Refresh(&hiwdg);
				 HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
				 HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,0);
			  }
				motor_move(0,0,0,0);
				  servo(180,67,90,180,180,90,90,90,90,90);
		  }
		  else{
				oled_returnhome();
				oled_puts("sens_test select");
				oled_setcursor(1,0);
				oled_puts("OK?     waiting ");
				  HAL_IWDG_Refresh(&hiwdg);
				HAL_Delay(5);
		  }
	  break;

	  case 4:
		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  oled_clear();
			  HOUI_def=JY901_def_set();
			    TIM1->CNT=30000;
			    while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			    	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1);
			    	oled_returnhome();
			    	oled_puts("test mode select");
			    	oled_setcursor(1,0);
			    	oled_puts("Ruuning         ");
					HAL_IWDG_Refresh(&hiwdg);
					test_mode();
					motor_move(0,0,0,0);
					  servo(180,67,90,180,180,90,90,90,90,90);
					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			     }
				motor_move(0,0,0,0);
				  servo(180,67,90,180,180,90,90,90,90,90);
		  }
		  else{
			oled_returnhome();
			oled_puts("test mode select");
			oled_setcursor(1,0);
			oled_puts("OK?     waiting ");
			  HAL_IWDG_Refresh(&hiwdg);
			HAL_Delay(5);
		  }
	  break;

	  case 5:
		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  oled_clear();
			  HOUI_def=JY901_def_set();
			    TIM1->CNT=30000;
				HAL_GPIO_WritePin(GPIOB,GPIO_PIN_13,1);
				while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
				oled_returnhome();
				oled_puts("demo mode select");
				oled_setcursor(1,0);
				oled_puts("Runnning         ");
				HAL_IWDG_Refresh(&hiwdg);
				demo_mode();
				HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
			}
				motor_move(0,0,0,0);
				  servo(180,67,90,180,180,90,90,90,90,90);
		  }
		  else{
				oled_returnhome();
				oled_puts("demo mode select");
				oled_setcursor(1,0);
				oled_puts("OK?     waiting ");
				HAL_IWDG_Refresh(&hiwdg);
				HAL_Delay(5);
		  }
	  break;

	  case 6:
			oled_returnhome();
			oled_puts("Calib select");
			oled_setcursor(1,0);
		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
			  calib_mode();
			  HAL_IWDG_Refresh(&hiwdg);
		  }
		  else{
				oled_puts("OK?     waiting ");
				HAL_Delay(5);
		  }
			motor_move(0,0,0,0);
			  servo(180,67,90,180,180,90,90,90,90,90);
	  break;

	  default:
			oled_returnhome();
			oled_puts("select mode     ");
			oled_setcursor(1,0);
			oled_puts("           SURF ");
			motor_move(0,0,0,0);
			  servo(180,67,90,180,180,90,90,90,90,90);
			HAL_IWDG_Refresh(&hiwdg);
		   HAL_Delay(5);
	  break;
	  }
	  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
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
                              |RCC_PERIPHCLK_I2C2;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c1ClockSelection = RCC_I2C1CLKSOURCE_PCLK1;
  PeriphClkInitStruct.I2c2ClockSelection = RCC_I2C2CLKSOURCE_PCLK1;
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
void main_run(){
			  motor_move(data[0],data[1],data[2],data[3]);
			  servo(servodata[0],servodata[1],90,servodata[3],servodata[3],servodata[2],servodata[3],90,90,90);
			  encordermotor1(data[8]);
			  slider(data[4],data[5],data[6],data[7]);
			  //LCD•\Ž¦
			  if(Flug_Rxdata==1){
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
			  xprintf(" D7=%d",data[7]);*/
			  xprintf(" D8=%d",data[8]);
			  xprintf(" D9=%d",data[9]);
			  xprintf(" D10=%d",data[10]);
			  xprintf(" D11=%d",data[11]);
			  xprintf(" D12=%d",data[12]);
			  xprintf(" H=%d",HOUI);
			  xprintf(" D13=%d\r\n",data[13]);
			Flug_Rxdata=0;
			}

}

void sens_test(){
	motor_move(0,0,0,0);
	  servo(180,67,90,180,180,90,90,90,90,90);
	HOUI=JY901_yaw_get(HOUI_def);
	uwDirectionCount1 = TIM1->CNT;
	xprintf(" E1=%d ",(int)uwDirectionCount1);
	xprintf(" SWE1=%d",HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2));
	xprintf(" SWE2=%d",HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3));
	xprintf(" SW1=%d",HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_2));
	xprintf(" SW2=%d",HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_3));
	xprintf(" SW3=%d",HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_4));
	xprintf(" SW4=%d",HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_5));
	xprintf(" HOUIdef=%d",HOUI_def);
	xprintf(" HOUI=%d\r\n",HOUI);
	HAL_Delay(5);
}

void comu_test(){
}

void test_mode(){
		motor_move(0,0,0,0);
		  servo(180,67,90,180,180,90,90,90,90,90);
		if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0){
		while(encordermotor1(250)!=HAL_OK){
		xprintf("goto250 ");
		xprintf("encorder1=%d",TIM1->CNT);
		xprintf("\r\n");
		  HAL_IWDG_Refresh(&hiwdg);
		}
		HAL_Delay(1000);
		  HAL_IWDG_Refresh(&hiwdg);
		while(encordermotor1(0)!=HAL_OK){
			xprintf("=%d",func((int)10));
			xprintf("goto0 ");
			xprintf("encorder1=%d",TIM1->CNT);
			xprintf("\r\n");
			  HAL_IWDG_Refresh(&hiwdg);
		}
		}
		xprintf("waiting");
		xprintf(" encorder1=%d",TIM1->CNT);
		xprintf("\r\n");
}

void demo_mode(){

}

void calib_mode(){
	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_15)==1){
	oled_returnhome();
	oled_puts("Calib select    ");
	oled_setcursor(1,0);
	oled_puts("Running Press SW");
	HAL_Delay(5);
if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)==0){	//press RS
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,1);
	DFPlayer_playmp3(8);
	  servo(180,67,90,180,180,90,90,90,90,90);
	motor_move(0,0,0,0);
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
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_8,0);
	beep(2,150,70);
	}
	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	HAL_IWDG_Refresh(&hiwdg);
}
}

long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		int j = 0;
		while (Rxbuf[j] != 252 && j<(Servonumber + 11-1)) {
			j++;
		}
		if(j>=Servonumber+11-2){
			for (int k = 0; k < 8; k++) {
				data[k] = 0;
			}
			for(int k=8;k<(8+Servonumber);k++){
				data[k]=90;
			}
			data[13]=0;
		}
		else {
			for (int k = 0; k < (Servonumber + 11-1); k++) {
				if ((j + k) >= Servonumber + 11-1) {
					data[k] = Rxbuf[k - (Servonumber + 11-1  - j)];
				}
				else {
					data[k] = Rxbuf[j + k + 1];
				}
			}
			motor[0]=data[0];
			motor[1]=data[1];
			motor[2]=data[2];
			motor[3]=data[3];
			motor[4]=data[4];

			for(int i=0;i<Servonumber;i++){
			servodata[i]=data[i+9];
			}
			Flug_Rxdata=1;
			Txdata[0]=1+(!HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_2))*2+!HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_3)*4+
					!HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_4)*8+!HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_5)*16+Expand_flug*32;
			HAL_UART_Transmit(&huart1,(uint8_t*)Txdata,1,0xFF);
		}
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
	  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,1);
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
