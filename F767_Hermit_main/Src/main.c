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

TIM_MasterConfigTypeDef sMasterConfig;
TIM_OC_InitTypeDef sConfigOC;
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig;
TIM_Encoder_InitTypeDef sConfig;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void main_run();
void sens_test();
void comu_test();
void motortest_mode();
void armtest_mode();
void demo_mode();
void Calibration();
void printLCD();
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
long map(long x, long in_min, long in_max, long out_min, long out_max) ;

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define Servonumber 11
#define debug 1
uint8_t motor[5];
int16_t Rarmdata[5]={90,90,90,90,90};
int16_t Larmdata[5]={90,90,90,90,90};
uint8_t Servo[4]={90,90,90,90};
int16_t rtempdata[5]={90,90,90,90,90};
int16_t ltempdata[5]={90,90,90,90,90};
uint8_t flug_Rxdata=0;
uint8_t TPIPConnect=0;
uint8_t Rxdetatemp;
uint8_t test_var=90;;
uint8_t mode=0;
uint8_t Flug_Rxdata;
uint16_t posDataR1,posDataR2,posDataR3,posDataL1,posDataL2,posDataL3;
uint8_t Rxbuf[Servonumber+7];
uint8_t data[Servonumber+6],tempdata[Servonumber+6];
/* USER CODE END 0 */

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
  MX_TIM1_Init();
  MX_UART5_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_TIM10_Init();
  MX_TIM11_Init();
  MX_TIM13_Init();
  MX_TIM14_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM8_Init();
  MX_TIM2_Init();
  MX_TIM6_Init();
  MX_TIM12_Init();
  MX_TIM9_Init();
  MX_UART7_Init();
  MX_TIM4_Init();
  MX_TIM5_Init();
  MX_USART3_UART_Init();
  MX_UART4_Init();
 // MX_IWDG_Init();
  MX_UART8_Init();

  /* USER CODE BEGIN 2 */
	Rarm(90,90,90,90,90);
	Larm(90,90,90,90,90);
	servo(90,0,0);
	motor_move(0,0,0,0,0);
  if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==1){
    	  MX_IWDG_Init();
  }
  else{
	  beep(10,30,30);
  }
  //HAL_IWDG_Refresh(&hiwdg);
  digtemp=1000;
  xprintf_init(&huart2);
  JY901_init(&hi2c1);
  DFPlayer_init(&huart7);
  oled_i2c_to_oled(&hi2c1);
  HAL_TIM_Base_Start_IT(&htim6);
  if(HAL_TIM_Encoder_Init(&htim1, &sConfig) != HAL_OK){Error_Handler();}
  HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
  TIM1->CNT=30000;
  if(HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK){Error_Handler();}
  HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
  TIM3->CNT=30000;
  if(HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK){Error_Handler();}
  HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
  TIM4->CNT=30000;
  if(HAL_TIM_Encoder_Init(&htim5, &sConfig) != HAL_OK){Error_Handler();}
  HAL_TIM_Encoder_Start(&htim5, TIM_CHANNEL_ALL);
  TIM5->CNT=30000;
  if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)Rxbuf,18) != HAL_OK){Error_Handler();}
	Rarm(90,90,90,90,90);
	Larm(90,90,90,90,90);
	Rarm(90,90,90,90,90);
	Larm(90,90,90,90,90);
	Rarm(90,90,90,90,90);
	Larm(90,90,90,90,90);
	servo(90,0,0);
	motor_move(0,0,0,0,0);
  oled_returnhome();
  oled_puts("Is The Order a");
  oled_setcursor(1,2);
  oled_puts("Rescue Robot?");
  HAL_Delay(600);
  DFPlayer_setvolume(0x25);
  HAL_Delay(100);
  Rarm(90,90,90,90,90);
  Larm(90,90,90,90,90);
  DFPlayer_playmp3(4);
  HAL_Delay(500);
  HAL_IWDG_Refresh(&hiwdg);
  HAL_Delay(1000);
  HAL_IWDG_Refresh(&hiwdg);
  HAL_Delay(600);
  HAL_IWDG_Refresh(&hiwdg);
  oled_clear();
  HAL_IWDG_Refresh(&hiwdg);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  mofu:
	  	  mode=HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_14)*4+(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_13)*2)
	  			  +(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_12));
	  	  switch(mode){
	  	  case 1:
	  		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  HOUI_def=JY901_def_set();
	  			  while(TPIPConnect==0){
	  				Rarm(90,90,90,90,90);
	  				Larm(90,90,90,90,90);
	  				servo(90,0,0);
	  				motor_move(0,0,0,0,0);
	  			    oled_returnhome();
	  			    oled_puts("main_run select ");
	  			    oled_setcursor(1,0);
	  			    oled_puts("waiting for TPIP");
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
	  				xprintf(" 12=%d",Rxbuf[12]);
	  				xprintf(" 13=%d",Rxbuf[13]);
	  				xprintf(" 14=%d",Rxbuf[14]);
	  				xprintf(" 15=%d",Rxbuf[15]);
	  				xprintf(" 16=%d",Rxbuf[16]);
	  				xprintf(" 17=%d\r\n",Rxbuf[17]);
	  			  	if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==0){goto mofu;}
	  			  	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,1);
	  			    HAL_IWDG_Refresh(&hiwdg);
	  			  	HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			  	}
	  			  	beep(3,50,50);
	  			    DFPlayer_playmp3(6);
	  			  	oled_clear();
	  			  	counttime=0;
	  			  	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  		if(TPIPConnect==1){
	  			  		main_run();
	  			  		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,1);
				  		if(data[Servonumber+5]%11==0){
				  		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,1);
				  		}
				  		if(data[Servonumber+5]%11==5){
				  		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,0);
				  		}
				  		if(counttime>70){
				  		DFPlayer_playmp3(1);
				  		counttime=0;
				  		}
	  			  	}
	  			  	  else{
					  		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,0);
	  			  			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,0);
	  			  			Rarm(rtempdata[0],rtempdata[1],rtempdata[2],rtempdata[3],rtempdata[4]);
	  			  			Larm(ltempdata[0],ltempdata[1],ltempdata[2],ltempdata[3],ltempdata[4]);
	  			  			servo(Servo[0],0,0);
	  			  			motor_move(0,0,0,0,0);
	  			  			oled_returnhome();
	  			  			oled_puts("main_run select");
	  			  			oled_setcursor(1,0);
	  			  			oled_puts("lost connection!");
	  			  			for(int i=0;i<(Servonumber+6);i++){
	  			  				xprintf(" %d)%d",i,data[i]);
	  			  			}
	  			  		xprintf("\r\n");
		  			    DFPlayer_playmp3(7);
	  			  		beep(1,300,300);
		  			    HAL_IWDG_Refresh(&hiwdg);
	  			  		beep(1,300,300);
		  			    HAL_IWDG_Refresh(&hiwdg);
	  			  		beep(1,300,300);
		  			    HAL_IWDG_Refresh(&hiwdg);
	  			  		beep(1,300,300);
		  			    HAL_IWDG_Refresh(&hiwdg);
	  			  	  }
	  			  	  HAL_IWDG_Refresh(&hiwdg);
	  			  	  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			  }
			  		HAL_GPIO_WritePin(GPIOC,GPIO_PIN_11,0);
	  		  		HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,0);
	  		  }
	  		  else{
	  			Rarm(rtempdata[0],rtempdata[1],rtempdata[2],rtempdata[3],rtempdata[4]);
	  			Larm(ltempdata[0],ltempdata[1],ltempdata[2],ltempdata[3],ltempdata[4]);
	  			servo(Servo[0],0,0);
	 	  	  	  motor_move(0,0,0,0,0);
	  			  oled_returnhome();
	  			  oled_puts("main_run select");
	  			  oled_setcursor(1,0);
	  			  oled_puts("OK?     waiting ");
	  			  HAL_Delay(5);
	  		  }
	  	  break;

	  	  case 2:
	  			if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  				HOUI_def=JY901_def_set();
	  				HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,0);
	  				while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  				comu_test();
	  				oled_returnhome();
	  				oled_puts("Comu test select");
	  				oled_setcursor(1,0);
	  				oled_puts("Runnning         ");
	  			    HAL_IWDG_Refresh(&hiwdg);
	  				HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			}
	  			}
	  			else{

	  				Rarm(90,90,90,90,90);
	  				Larm(90,90,90,90,90);
	  				servo(90,0,0);
	  				oled_returnhome();
	  				oled_puts("Comu test select");
	  				oled_setcursor(1,0);
	  				oled_puts("OK?     waiting ");
	  				HAL_Delay(5);
	  			}
	  	  break;

	  	  case 3:
	  		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  HOUI_def=JY901_def_set();
	  			  HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,0);
	  			    TIM1->CNT=30000;
	  			    TIM3->CNT=30000;
	  			    TIM4->CNT=30000;
	  			    TIM5->CNT=30000;
	  			  	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  	sens_test();
	  			  	oled_returnhome();
	  			  	oled_puts("sens_test select");
	  			  	oled_setcursor(1,0);
	  			  	oled_puts("Running          ");
	  			  HAL_IWDG_Refresh(&hiwdg);
	  			  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			  }
	  		  }
	  		  else{
	  			Rarm(90,90,90,90,90);
	  			Larm(90,90,90,90,90);
	  			servo(90,0,0);
	 	  	  	  motor_move(0,0,0,0,0);
	  				oled_returnhome();
	  				oled_puts("sens_test select");
	  				oled_setcursor(1,0);
	  				oled_puts("OK?     waiting ");
	  				HAL_Delay(5);
	  		  }
	  	  break;

	  	  case 4:
	  		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  	  HOUI_def=JY901_def_set();
	  			  	  oled_clear();
		  			    TIM1->CNT=30000;
		  			    TIM3->CNT=30000;
		  			    TIM4->CNT=30000;
		  			    TIM5->CNT=30000;
	  			    while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			    	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,1);
	  			    	motortest_mode();
	  			      HAL_IWDG_Refresh(&hiwdg);
	  					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			     }
	  		  }
	  		  else{

	  			Rarm(90,90,90,90,90);
	  			Larm(90,90,90,90,90);
	  			servo(90,0,0);
	 	  	  	  motor_move(0,0,0,0,0);
	  			oled_returnhome();
			    oled_puts("motortest select");
	  			oled_setcursor(1,0);
	  			oled_puts("OK?     waiting ");
	  			HAL_Delay(5);
	  		  }
	  	  break;

	  	  case 5:
	  		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  HOUI_def=JY901_def_set();
	  			    while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			    	HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,0);
	  			    	armtest_mode();
	  			    	oled_returnhome();
	  			    	oled_puts("arm test  select");
	  			    	oled_setcursor(1,0);
	  			    	oled_puts("Ruuning         ");
	  			      HAL_IWDG_Refresh(&hiwdg);
	  					HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			     }
	  		  }
	  		  else{
	  			Rarm(rtempdata[0],rtempdata[1],rtempdata[2],rtempdata[3],rtempdata[4]);
	  			Larm(ltempdata[0],ltempdata[1],ltempdata[2],ltempdata[3],ltempdata[4]);
	  			servo(Servo[0],0,0);
	 	  	  	  motor_move(0,0,0,0,0);
	  			oled_returnhome();
			    oled_puts("arm test  select");
	  			oled_setcursor(1,0);
	  			oled_puts("OK?     waiting ");
	  			HAL_Delay(5);
	  		  }
	  	  break;

	  	  case 6:
	  		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  HOUI_def=JY901_def_set();
	  				HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,1);
	  				while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  				demo_mode();
	  				oled_returnhome();
	  				oled_puts("demo mode select");
	  				oled_setcursor(1,0);
	  				oled_puts("Runnning         ");
	  			  HAL_IWDG_Refresh(&hiwdg);
	  				HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
	  			}
	  		  }
	  		  else{

	  			Rarm(90,90,90,90,90);
	  			Larm(90,90,90,90,90);
	  			servo(90,0,0);
	 	  	  	  motor_move(0,0,0,0,0);
	  				oled_returnhome();
	  				oled_puts("demo mode select");
	  				oled_setcursor(1,0);
	  				oled_puts("OK?     waiting ");
	  				HAL_Delay(5);
	  		  }
	  	  break;

	  	  case 7:
	  			oled_returnhome();
	  			oled_puts("Calib select");
	  			oled_setcursor(1,0);
	  			HAL_GPIO_WritePin(GPIOG,GPIO_PIN_15,1);
	  		  if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	  			  HAL_IWDG_Refresh(&hiwdg);
	  			  Calibration();
	  		  }
	  		  else{
	  			  oled_puts("OK?     waiting ");
	  			   HAL_Delay(5);
	 	  		  HAL_IWDG_Refresh(&hiwdg);

	 	  		Rarm(90,90,90,90,90);
	 	  		Larm(90,90,90,90,90);
	 	  		servo(90,0,0);
	 	  	  	  motor_move(0,0,0,0,0);

	  		  }
	  	  break;

	  	  default:
	  		  HAL_IWDG_Refresh(&hiwdg);

	  		Rarm(90,90,90,90,90);
	  		Larm(90,90,90,90,90);
	  		servo(90,0,0);
	  	  	  motor_move(0,0,0,0,0);
	  	  	  oled_returnhome();
	  	  	  oled_puts("select mode     ");
	  	  	  oled_setcursor(1,0);
	  	  	  oled_puts("           SURF ");
	  	  	  HAL_Delay(5);
	  	  break;
	  	  }
	  	  HAL_IWDG_Refresh(&hiwdg);
	  	  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
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
                              |RCC_PERIPHCLK_USART3|RCC_PERIPHCLK_UART4
                              |RCC_PERIPHCLK_UART5|RCC_PERIPHCLK_UART7
                              |RCC_PERIPHCLK_UART8|RCC_PERIPHCLK_I2C1
                              |RCC_PERIPHCLK_I2C2;
  PeriphClkInitStruct.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInitStruct.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Usart3ClockSelection = RCC_USART3CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart4ClockSelection = RCC_UART4CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart5ClockSelection = RCC_UART5CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart7ClockSelection = RCC_UART7CLKSOURCE_PCLK1;
  PeriphClkInitStruct.Uart8ClockSelection = RCC_UART8CLKSOURCE_PCLK1;
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
	HOUI=JY901_yaw_get(HOUI_def);
	Rarmdata[0]=data[5];
	Rarmdata[1]=data[6];
	Rarmdata[2]=data[7];
	Rarmdata[3]=data[8];
	Rarmdata[4]=data[9];
	Larmdata[0]=data[10];
	Larmdata[1]=data[11];
	Larmdata[2]=data[12];
	Larmdata[3]=data[13];
	Larmdata[4]=data[14];
	Servo[0]=data[15];
	motor_move(motor[0],motor[1],motor[2],motor[3],motor[4]);
	Rarm(Rarmdata[0],Rarmdata[1],Rarmdata[2],Rarmdata[3],Rarmdata[4]);
	Larm(Larmdata[0],Larmdata[1],Larmdata[2],Larmdata[3],Larmdata[4]);
	servo(Servo[0],0,0);
	if(Flug_Rxdata==1){
	oled_clear();
	oled_returnhome();
	oled_puts("main_run select");
	oled_setcursor(1,0);
	switch(motor[0]){
	case 150:
		oled_puts("Running   LS");
	break;
	case 200:
		oled_puts("Running   RS");
	break;
	case 100:
		printLCD();
	break;
	case 250:
		printLCD();
	break;
	case 50:
		printLCD();
	break;
	case 125:
		printLCD();
	break;
	default:
		oled_puts("Running");
	break;
	}
	xprintf(" HOUI=%d",JY901_yaw_get(HOUI_def));
	xprintf(" cmd=%d",motor[0]);
	xprintf(" dig=%d",digree);
	xprintf(" p1=%d",power1);
	xprintf(" p2=%d",power2);
	xprintf(" p3=%d",power3);
	xprintf(" p4=%d",power4);
	xprintf(" p=%d",power);
	xprintf(" H=%d\r\n",HOUI);
	Flug_Rxdata=0;
	}
	rtempdata[0]=Rarmdata[0];
	rtempdata[1]=Rarmdata[1];
	rtempdata[2]=Rarmdata[2];
	rtempdata[3]=Rarmdata[3];
	rtempdata[4]=Rarmdata[4];
	ltempdata[0]=Larmdata[0];
	ltempdata[1]=Larmdata[1];
	ltempdata[2]=Larmdata[2];
	ltempdata[3]=Larmdata[3];
	ltempdata[4]=Larmdata[4];
}

void sens_test(){
	  Rarm(90,90,90,90,90);
	  Larm(90,90,90,90,90);
	  servo(test_var,0,0);
	  motor_move(0,0,0,0,0);
	  if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)){
		  if(test_var>=180){test_var=180;}
		  else{test_var=test_var+5;}
	  }
	  else if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)){
		  if(test_var<=0){test_var=0;}
		  else{test_var=test_var-5;}
	  }
	xprintf(" L=%d%d%d%d%d%d%d%d%d%d%d%d"
	,HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_2),HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_3)
	,HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_4),HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_13)
	,HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_14),HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_15)
	,HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_2),HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_3)
	,HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_4),HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_5)
	,HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_10),HAL_GPIO_ReadPin(GPIOF,GPIO_PIN_0));
	xprintf(" SWFD=%d",HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7));
	xprintf(" SWBK=%d",HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9));
	xprintf(" SWL=%d",HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10));
	xprintf(" SWR=%d",HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4));
	xprintf(" SWLS=%d",HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3));
	xprintf(" SWRS=%d",HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2));
	xprintf(" HOUdef=%d",HOUI_def);
	xprintf(" HOUI=%d",JY901_yaw_get(HOUI_def));
	xprintf(" E1=%d",TIM1->CNT);
	xprintf(" E2=%d",TIM3->CNT);
	xprintf(" E3=%d",TIM4->CNT);
	xprintf(" E4=%d",TIM5->CNT);
	xprintf("\r\n");
}

void comu_test(){
	Rarm(90,90,90,90,90);
	Larm(90,90,90,90,90);
	servo(90,0,0);
	motor_move(0,0,0,0,0);
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
		xprintf(" 12=%d",Rxbuf[12]);
		xprintf(" 13=%d",Rxbuf[13]);
		xprintf(" 14=%d",Rxbuf[14]);
		xprintf(" 15=%d",Rxbuf[15]);
		xprintf(" 16=%d",Rxbuf[16]);
		xprintf(" 17=%d\r\n",Rxbuf[17]);
}

void motortest_mode(){
	Rarm(90,90,90,90,90);
	Larm(90,90,90,90,90);
	servo(90,0,0);
		oled_returnhome();
		oled_puts("motortest select");
		oled_setcursor(1,0);
		if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_7)==0){
			motor_move(100,0x03,0xE8,201,2);
			//motor_move(250,0x03,0xE8,201,2);
			printLCD();
		}
		else if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)==0){
			motor_move(100,0x04,0x9C,201,2);
			printLCD();
		}
		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_4)==0){
			motor_move(100,0x04,0x42,201,2);
			printLCD();
		}
		else if(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_10)==0){
			motor_move(100,0x04,0xF6,201,2);
			printLCD();
		}
		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_3)==0){
			motor_move(150,0,0,201,2);
			oled_puts("Running   RS");
		}
		else if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0){
			motor_move(200,0,0,201,2);
			oled_puts("Running   LS");
		}
		else{
		motor_move(0,0,0,0,0);
		oled_puts("Running     ");
		}
		//HAL_Delay(10);
}

void armtest_mode(){
	motor_move(0,0,0,0,0);
	if(TPIPConnect==1){
		Rarmdata[0]=data[5];
		Rarmdata[1]=data[6];
		Rarmdata[2]=data[7];
		Rarmdata[3]=data[8];
		Rarmdata[4]=data[9];
		Larmdata[0]=data[10];
		Larmdata[1]=data[11];
		Larmdata[2]=data[12];
		Larmdata[3]=data[13];
		Larmdata[4]=data[14];
		Servo[0]=data[15];

		Rarm(Rarmdata[0],Rarmdata[1],Rarmdata[2],Rarmdata[3],Rarmdata[4]);
		Larm(Larmdata[0],Larmdata[1],Larmdata[2],Larmdata[3],Larmdata[4]);
		servo(Servo[0],0,0);
		rtempdata[0]=Rarmdata[0];
		rtempdata[1]=Rarmdata[1];
		rtempdata[2]=Rarmdata[2];
		rtempdata[3]=Rarmdata[3];
		rtempdata[4]=Rarmdata[4];
		ltempdata[0]=Larmdata[0];
		ltempdata[1]=Larmdata[1];
		ltempdata[2]=Larmdata[2];
		ltempdata[3]=Larmdata[3];
		ltempdata[4]=Larmdata[4];
	}
	else{
		Rarm(90,90,90,90,90);
		Larm(90,90,90,90,90);
		servo(90,0,0);
		motor_move(0,0,0,0,0);
	}
}

void demo_mode(){
	HOUI=JY901_yaw_get(HOUI_def);
	Rarm(90,90,90,0,90);
	Larm(90,90,90,0,90);
	servo(90,0,0);
	motor_move(0,0,0,0,0);
	xprintf("HOUI=%d",HOUI);
	 if(HOUI>= 5 && HOUI<=355){
		 motor1(0,0);
		 motor2(0,0);
		 motor3(0,0);
		 motor4(0,0);
		 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
		 HAL_Delay(10);
		 while(HOUI>=5 && HOUI<=355){
			 HOUI=JY901_yaw_get(HOUI_def);
			 if(HOUI<180){
				 motor1((int)map_m(HOUI,0,180,200,500),0);
				 motor2((int)map_m(HOUI,0,180,200,500),0);
				 motor3(0,(int)map_m(HOUI,0,180,200,500));
			  	 motor4(0,(int)map_m(HOUI,0,180,200,500));
			  	 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
			 	 xprintf("HOUI=%d",HOUI);
			  	 xprintf(" LS now");
			  	 xprintf(" speed= %d\r\n",(int)map_m(HOUI,0,180,200,500));
			 }
			  else{
				  motor1(0,(int)map_m(HOUI,359,180,200,500));
				  motor2(0,(int)map_m(HOUI,359,180,200,500));
				  motor3((int)map_m(HOUI,359,180,200,500),0);
				  motor4((int)map_m(HOUI,359,180,200,500),0);
				  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,1);
				  xprintf("HOUI=%d",HOUI);
				  xprintf(" RS now");
				  xprintf(" speed= %d\r\n",(int)map_m(HOUI,359,180,200,500));
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
	 motor1(0,0);
	 motor2(0,0);
	 motor3(0,0);
	 motor4(0,0);
	 xprintf("\r\n");
	 HAL_GPIO_WritePin(GPIOD,GPIO_PIN_0,0);
}

void Calibration(){
	while(HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_11)==1){
	Rarm(90,90,90,0,90);
	Larm(90,90,90,0,90);
	servo(90,0,0);
	motor_move(0,0,0,0,0);
	oled_returnhome();
	oled_puts("Calib select    ");
	oled_setcursor(1,0);
	oled_puts("Running Press RS");
	HAL_Delay(5);
    if(HAL_GPIO_ReadPin(GPIOD,GPIO_PIN_2)==0){	//press RS
    DFPlayer_playmp3(8);
	oled_clear();
	oled_returnhome();
	oled_puts("Angular velocity");
	oled_setcursor(1,0);
	oled_puts("    Calibration ");
	JY901_calibration(2000,1);
	oled_clear();
	oled_returnhome();
	oled_puts("Magnetic");
	oled_setcursor(1,0);
	oled_puts(" Calibration  RS");
	xprintf("houi cab\r\n");
	motor_move(200,0,0,101,3);
	JY901_calibration(12000,2);
	motor_move(0,0,0,0,0);
	oled_clear();
	oled_returnhome();
	oled_puts("Calibration End ");
	xprintf("cab end\r\n");
	JY901_calibration(100,3);
	xprintf("save\r\n");
	JY901_calibration(100,4);
	DFPlayer_stopmp3();
	beep(2,100,100);
}
 HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_0);
 HAL_IWDG_Refresh(&hiwdg);
}
}

void printLCD(){
	if (digree >= 0 && digree <= 360) {
		if (digree <= 23 || digree >= 338) {oled_puts("Running   FD");}
		else if (digree>23 && digree <= 68)   {oled_puts("Running   RF");}
		else if (digree>68 && digree <= 113)  {oled_puts("Running   Ri");}
		else if (digree>113 && digree <= 158) {oled_puts("Running   RB");}
		else if (digree>158 && digree <= 203) {oled_puts("Running   BK");}
		else if (digree>203 && digree <= 248) {oled_puts("Running   LB");}
		else if (digree>248 && digree <= 293) {oled_puts("Running   Le");}
		else if (digree>293 && digree <= 338) {oled_puts("Running   LF");}
	}
	else{oled_puts("Running  ST");}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
		 counttime++;
	 if(Rxdetatemp!=data[Servonumber+5] || HAL_GPIO_ReadPin(GPIOG,GPIO_PIN_9)==0){
		 TPIPConnect=1;
		 HAL_GPIO_WritePin(GPIOC,GPIO_PIN_12,1);
	 }
	 else{
		 TPIPConnect=0;
		 HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_12);
	 }
	 Rxdetatemp=data[Servonumber+5];
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
		int j = 0;
		while (Rxbuf[j] != 251 && j<(Servonumber + 6)) {
			j++;
		}
		if(j>=Servonumber+6){

			for (int k = 0; k < 4; k++) {
				data[k] = 0;
			}
			for(int k=4;k<(Servonumber+4);k++){
				data[k]=90;
			}
			data[Servonumber+4]=0;
			data[Servonumber+5]=0;

		}
		else {
			for (int k = 0; k < (Servonumber + 6); k++) {
				if ((j + k) >= Servonumber + 6) {
					data[k] = Rxbuf[k - (Servonumber + 6 - j)];
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
			Flug_Rxdata=1;
		}
		}
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
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
	  HAL_GPIO_WritePin(GPIOD,GPIO_PIN_1,1);
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
