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
#include "stm32f3xx_hal.h"
#include "adc.h"
#include "dma.h"
#include "usart.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "xprintf.h"
#include "stdlib.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
#define ADC_CONVERTED_DATA_BUFFER_SIZE   ((uint32_t)  3)
uint16_t   aADCxConvertedDataR[2];
uint16_t   aADCxConvertedDataL[4];
ADC_ChannelConfTypeDef sConfig;
uint8_t Txbuf[14];
uint8_t count;
uint16_t mofumofu;
uint16_t tempdata1[5],tempdata2[5],tempdata3[5],tempdata4[5],tempdata5[5],tempdata6[5];
uint16_t sortdata1[5],sortdata2[5],sortdata3[5],sortdata4[5],sortdata5[5],sortdata6[5];
uint16_t out_lowpass[6];
uint16_t medianfilter_out1,medianfilter_out2,medianfilter_out3,medianfilter_out4,medianfilter_out5,medianfilter_out6;
uint16_t out_lowpass_temp1,out_lowpass_temp2,out_lowpass_temp3,out_lowpass_temp4,out_lowpass_temp5,out_lowpass_temp6;
int int_sort( const void *p, const void *q ) {
    return *(uint16_t*)p - *(uint16_t*)q;
}
#define data_cnt  sizeof(sortdata1)/sizeof(uint16_t)
#define rate 0.2

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	  HAL_GPIO_TogglePin(GPIOB,GPIO_PIN_3);
}
/* USER CODE END 0 */

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
  MX_ADC1_Init();
  MX_ADC2_Init();

  /* USER CODE BEGIN 2 */
  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==1){
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
  }
  else{
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
  }
    init_xprintf(&huart2);
    xdev_out(uart_putc);
    if (HAL_ADC_Init(&hadc1) != HAL_OK)
    {
  	  Error_Handler();
    }
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
    {
  	  Error_Handler();
    }
     if (HAL_ADC_Start_DMA(&hadc1, (uint32_t *)aADCxConvertedDataR,2) != HAL_OK)
     {
        Error_Handler();
     }
     if (HAL_ADC_Init(&hadc2) != HAL_OK)
     {
   	  Error_Handler();
     }
     if (HAL_ADC_ConfigChannel(&hadc2, &sConfig) != HAL_OK)
     {
   	  Error_Handler();
     }
      if (HAL_ADC_Start_DMA(&hadc2, (uint32_t *)aADCxConvertedDataL,4) != HAL_OK)
      {
         Error_Handler();
      }
     count=0;
     for(uint16_t start_wait_delay=0;start_wait_delay<200;start_wait_delay++){
    	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1);
    	  tempdata1[count]=aADCxConvertedDataR[0];
  	   	  tempdata2[count]=aADCxConvertedDataR[1];
  	   	  tempdata3[count]=aADCxConvertedDataL[3];
  	   	  tempdata4[count]=aADCxConvertedDataL[0];
  	   	  tempdata5[count]=aADCxConvertedDataL[1];
  	   	  tempdata6[count]=aADCxConvertedDataL[2];
  	   	  for(uint8_t i=0;i<5;i++){
  	   	  sortdata1[i]=tempdata1[i];
  	   	  sortdata2[i]=tempdata2[i];
  	   	  sortdata3[i]=tempdata3[i];
  	   	  sortdata4[i]=tempdata4[i];
  	   	  sortdata5[i]=tempdata5[i];
  	   	  sortdata6[i]=tempdata6[i];
  	   	  }
  	   	  qsort(sortdata1,data_cnt,2,int_sort);
  	   	  qsort(sortdata2,data_cnt,2,int_sort);
  	   	  qsort(sortdata3,data_cnt,2,int_sort);
  	   	  qsort(sortdata4,data_cnt,2,int_sort);
  	   	  qsort(sortdata5,data_cnt,2,int_sort);
  	   	  qsort(sortdata6,data_cnt,2,int_sort);
  	   	  medianfilter_out1=sortdata1[2];
  	   	  medianfilter_out2=sortdata2[2];
  	   	  medianfilter_out3=sortdata3[2];
  	   	  medianfilter_out4=sortdata4[2];
  	   	  medianfilter_out5=sortdata5[2];
  	   	  medianfilter_out6=sortdata6[2];
  	   	  out_lowpass[0]=(float)((float)rate*medianfilter_out1+(float)(1-rate)*out_lowpass_temp1);
  	   	  out_lowpass[1]=(float)((float)rate*medianfilter_out2+(float)(1-rate)*out_lowpass_temp2);
  	   	  out_lowpass[2]=(float)((float)rate*medianfilter_out3+(float)(1-rate)*out_lowpass_temp3);
  	   	  out_lowpass[3]=(float)((float)rate*medianfilter_out4+(float)(1-rate)*out_lowpass_temp4);
  	   	  out_lowpass[4]=(float)((float)rate*medianfilter_out5+(float)(1-rate)*out_lowpass_temp5);
  	   	  out_lowpass[5]=(float)((float)rate*medianfilter_out6+(float)(1-rate)*out_lowpass_temp6);
  	   	  out_lowpass_temp1=out_lowpass[0];
  	   	  out_lowpass_temp2=out_lowpass[1];
  	   	  out_lowpass_temp3=out_lowpass[2];
  	   	  out_lowpass_temp4=out_lowpass[3];
  	   	  out_lowpass_temp5=out_lowpass[4];
  	   	  out_lowpass_temp6=out_lowpass[5];

  	  	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==0){
  	   	  xprintf("raw=%d",aADCxConvertedDataL[3]);
  	   	  xprintf(" medianfilter1=%d",medianfilter_out3);
  	   	  xprintf(" out1=%d",out_lowpass[2]);
  	   	  xprintf("\r\n");
  	  		  }
     	  if(count>=4){
     		  count=0;
     	  }
     	  else{
     		  count++;
     	  }

     }

     Txbuf[0]=254;
     Txbuf[1]= (uint8_t)( (out_lowpass[0]<<2) & 0b0000000011111111);
     Txbuf[2]= (uint8_t)(((out_lowpass[0]<<2) & 0b1111111100000000)>>8);
     Txbuf[3]= (uint8_t)( (out_lowpass[1]<<2) & 0b0000000011111111);
     Txbuf[4]= (uint8_t)(((out_lowpass[1]<<2) & 0b1111111100000000)>>8);
     Txbuf[5]= (uint8_t)( (out_lowpass[2]<<2) & 0b0000000011111111);
     Txbuf[6]= (uint8_t)(((out_lowpass[2]<<2) & 0b1111111100000000)>>8);
     Txbuf[7]= (uint8_t)( (out_lowpass[3]<<2) & 0b0000000011111111);
     Txbuf[8]= (uint8_t)(((out_lowpass[3]<<2) & 0b1111111100000000)>>8);
     Txbuf[9]= (uint8_t)( (out_lowpass[4]<<2) & 0b0000000011111111);
     Txbuf[10]=(uint8_t)(((out_lowpass[4]<<2) & 0b1111111100000000)>>8);
     Txbuf[11]=(uint8_t)( (out_lowpass[5]<<2) & 0b0000000011111111);
     Txbuf[12]=(uint8_t)(((out_lowpass[5]<<2) & 0b1111111100000000)>>8);
     Txbuf[13]=253;
     if (HAL_UART_Transmit_DMA(&huart1, (uint8_t *)Txbuf,14) != HAL_OK)
     {
    	 Error_Handler();
     }
	 HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
	  tempdata1[count]=aADCxConvertedDataR[0];
	  tempdata2[count]=aADCxConvertedDataR[1];
	  tempdata3[count]=aADCxConvertedDataL[3];
	  tempdata4[count]=aADCxConvertedDataL[0];
	  tempdata5[count]=aADCxConvertedDataL[1];
	  tempdata6[count]=aADCxConvertedDataL[2];
  	  for(uint8_t i=0;i<5;i++){
  	  sortdata1[i]=tempdata1[i];
  	  sortdata2[i]=tempdata2[i];
  	  sortdata3[i]=tempdata3[i];
  	  sortdata4[i]=tempdata4[i];
  	  sortdata5[i]=tempdata5[i];
  	  sortdata6[i]=tempdata6[i];
  	  }
  	  qsort(sortdata1,data_cnt,2,int_sort);
  	  qsort(sortdata2,data_cnt,2,int_sort);
  	  qsort(sortdata3,data_cnt,2,int_sort);
  	  qsort(sortdata4,data_cnt,2,int_sort);
  	  qsort(sortdata5,data_cnt,2,int_sort);
  	  qsort(sortdata6,data_cnt,2,int_sort);
  	  medianfilter_out1=sortdata1[2];
  	  medianfilter_out2=sortdata2[2];
  	  medianfilter_out3=sortdata3[2];
  	  medianfilter_out4=sortdata4[2];
  	  medianfilter_out5=sortdata5[2];
  	  medianfilter_out6=sortdata6[2];
  	  out_lowpass[0]=(float)((float)rate*medianfilter_out1+(float)(1-rate)*out_lowpass_temp1);
  	  out_lowpass[1]=(float)((float)rate*medianfilter_out2+(float)(1-rate)*out_lowpass_temp2);
  	  out_lowpass[2]=(float)((float)rate*medianfilter_out3+(float)(1-rate)*out_lowpass_temp3);
  	  out_lowpass[3]=(float)((float)rate*medianfilter_out4+(float)(1-rate)*out_lowpass_temp4);
  	  out_lowpass[4]=(float)((float)rate*medianfilter_out5+(float)(1-rate)*out_lowpass_temp5);
  	  out_lowpass[5]=(float)((float)rate*medianfilter_out6+(float)(1-rate)*out_lowpass_temp6);
  	  out_lowpass_temp1=out_lowpass[0];
  	  out_lowpass_temp2=out_lowpass[1];
  	  out_lowpass_temp3=out_lowpass[2];
  	  out_lowpass_temp4=out_lowpass[3];
  	  out_lowpass_temp5=out_lowpass[4];
  	  out_lowpass_temp6=out_lowpass[5];
  	  if(count>=4){
  		  count=0;
  	  }
  	  else{
  		  count++;
  	  }


     Txbuf[0]=254;
     Txbuf[1]= (uint8_t)( (out_lowpass[0]<<2) & 0b0000000011111111);
     Txbuf[2]= (uint8_t)(((out_lowpass[0]<<2) & 0b1111111100000000)>>8);
     Txbuf[3]= (uint8_t)( (out_lowpass[1]<<2) & 0b0000000011111111);
     Txbuf[4]= (uint8_t)(((out_lowpass[1]<<2) & 0b1111111100000000)>>8);
     Txbuf[5]= (uint8_t)( (out_lowpass[2]<<2) & 0b0000000011111111);
     Txbuf[6]= (uint8_t)(((out_lowpass[2]<<2) & 0b1111111100000000)>>8);
     Txbuf[7]= (uint8_t)( (out_lowpass[3]<<2) & 0b0000000011111111);
     Txbuf[8]= (uint8_t)(((out_lowpass[3]<<2) & 0b1111111100000000)>>8);
     Txbuf[9]= (uint8_t)( (out_lowpass[4]<<2) & 0b0000000011111111);
     Txbuf[10]=(uint8_t)(((out_lowpass[4]<<2) & 0b1111111100000000)>>8);
     Txbuf[11]=(uint8_t)( (out_lowpass[5]<<2) & 0b0000000011111111);
     Txbuf[12]=(uint8_t)(((out_lowpass[5]<<2) & 0b1111111100000000)>>8);
     Txbuf[13]=253;

  	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==0){
  	  xprintf(" out1=%d",out_lowpass[0]);
  	  xprintf(" out2=%d",out_lowpass[1]);
  	  xprintf(" out3=%d",out_lowpass[2]);
  	  xprintf(" out4=%d",out_lowpass[3]);
  	  xprintf(" out5=%d",out_lowpass[4]);
  	  xprintf(" out6=%d",out_lowpass[5]);
  	  /*xprintf(" Tx[0]=%d",Txbuf[0]);
  	  xprintf(" Tx[1]=%d",Txbuf[1]);
  	  xprintf(" Tx[2]=%d",Txbuf[2]);
  	  xprintf(" Tx[3]=%d",Txbuf[3]);
  	  xprintf(" Tx[4]=%d",Txbuf[4]);
  	  xprintf(" Tx[5]=%d",Txbuf[5]);
  	  xprintf(" Tx[6]=%d",Txbuf[6]);
  	  xprintf(" Tx[7]=%d",Txbuf[7]);
  	  xprintf(" Tx[8]=%d",Txbuf[8]);
  	  xprintf(" Tx[9]=%d",Txbuf[9]);
  	  xprintf(" Tx[10]=%d",Txbuf[10]);
  	  xprintf(" Tx[11]=%d",Txbuf[11]);
  	  xprintf(" Tx[12]=%d",Txbuf[12]);
  	  xprintf(" Tx[13]=%d",Txbuf[13]);*/
  	  xprintf("\r\n");
  	  }
  	  if(mofumofu>5000){
  		  HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_12);
  		  mofumofu=0;
  	  }
  	  else{mofumofu++;}
  	  if(HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_3)==1){
  		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,0);
  	  }
  	  else{
  		  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_11,1);
  	  }
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
	  HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,1);
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
