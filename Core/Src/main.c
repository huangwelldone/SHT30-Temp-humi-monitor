/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "usart.h"
#include "gpio.h"
#include "oled.h"
#include "bsp_sht30.h"
#include <stdio.h>
#include <string.h>
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_I2C1_Init();

  MX_USART1_UART_Init();
  char msg[50];
  float temp, humi;
  SHT30_Init(&hi2c1);

  /* USER CODE BEGIN 2 */
  OLED_Init();
  HAL_Delay(20);
  OLED_NewFrame();
  OLED_PrintString(4,20,"温度",&font16x16,0);
  OLED_PrintString(4,46,"湿度",&font16x16,0);
  //OLED_PrintString(0,0,"STM32_Temp_Humi",&afont16x8,0);
  OLED_ShowFrame();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(SHT30_ReadData(&hi2c1, &temp, &humi) == SHT30_OK)
	  {
		  if(temp>16&&temp<20) {OLED_PrintString(30,0,"凉爽",&font16x16,0); OLED_ShowFrame();}
		  if(temp>21&&temp<25) {OLED_PrintString(30,0,"舒适",&font16x16,0); OLED_ShowFrame();}
		  if(temp>26&&temp<31) {OLED_PrintString(30,0,"微热",&font16x16,0); OLED_ShowFrame();}
		  if(temp>31&&temp<35) {OLED_PrintString(30,0,"炎热",&font16x16,0); OLED_ShowFrame();}
		  if(temp>35) {OLED_PrintString(30,0,"酷热",&font16x16,0); OLED_ShowFrame();}
		  if(temp>10&&temp<15) {OLED_PrintString(30,0,"清冷",&font16x16,0); OLED_ShowFrame();}
		  if(temp>5&&temp<9) {OLED_PrintString(30,0,"寒冷",&font16x16,0); OLED_ShowFrame();}
		  if(temp<5) {OLED_PrintString(30,0,"严冷",&font16x16,0); OLED_ShowFrame();}

		  if(humi>30&&humi<50) {OLED_PrintString(65,0,"宜人",&font16x16,0); OLED_ShowFrame();}
		  if(humi>50&&humi<60) {OLED_PrintString(65,0,"润爽",&font16x16,0); OLED_ShowFrame();}
		  if(humi>60&&humi<70) {OLED_PrintString(65,0,"黏腻",&font16x16,0); OLED_ShowFrame();}
		  if(humi>70) {OLED_PrintString(65,0,"湿闷",&font16x16,0); OLED_ShowFrame();}
		  if(humi<30) {OLED_PrintString(65,0,"干燥",&font16x16,0); OLED_ShowFrame();}
		  sprintf(msg,"%.1f",temp);
		  OLED_PrintString(41,17,msg,&font16x16,0);
		  OLED_PrintString(96,23,"℃",&font16x16,0);
		  sprintf(msg,"%.1f",humi);
		  OLED_PrintString(41,42,msg,&font16x16,0);
		  OLED_PrintString(96,42,"%",&font16x16,0);
		  OLED_ShowFrame();
		  sprintf(msg,"Temperature=%.2f,Humidity=%.1f\r\n",temp,humi);
		  HAL_UART_Transmit(&huart1,(uint8_t*)msg,strlen(msg),500);
	   }

	  HAL_Delay(2000);
	  HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
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
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
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
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
