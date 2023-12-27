/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_led.h"
#include "stdio.h"
#include <stdlib.h>
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
//  SCB->VTOR = 0x90000000; //app1
	
//	SCB->VTOR = 0x90400000; //app2
	
	__enable_irq();
	
  /* USER CODE END 1 */

  /* Enable I-Cache---------------------------------------------------------*/
  SCB_EnableICache();

  /* Enable D-Cache---------------------------------------------------------*/
  SCB_EnableDCache();

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
  MX_UART4_Init();
  /* USER CODE BEGIN 2 */

	
/*  logo ������վ��http://patorjk.com/software/taag/   */                                                                                
                                                                                     
  printf("               AAA               PPPPPPPPPPPPPPPPP   PPPPPPPPPPPPPPPPP     1111111   \r\n");
  printf("              A:::A              P::::::::::::::::P  P::::::::::::::::P   1::::::1    \r\n");
  printf("             A:::::A             P::::::PPPPPP:::::P P::::::PPPPPP:::::P 1:::::::1    \r\n");
  printf("            A:::::::A            PP:::::P     P:::::PPP:::::P     P:::::P111:::::1     \r\n");
  printf("           A:::::::::A             P::::P     P:::::P  P::::P     P:::::P   1::::1    \r\n");
  printf("          A:::::A:::::A            P::::P     P:::::P  P::::P     P:::::P   1::::1    \r\n");
  printf("         A:::::A A:::::A           P::::PPPPPP:::::P   P::::PPPPPP:::::P    1::::1    \r\n");
  printf("        A:::::A   A:::::A          P:::::::::::::PP    P:::::::::::::PP     1::::l    \r\n");
  printf("       A:::::A     A:::::A         P::::PPPPPPPPP      P::::PPPPPPPPP       1::::l    \r\n");
  printf("      A:::::AAAAAAAAA:::::A        P::::P              P::::P               1::::l     \r\n");
  printf("     A:::::::::::::::::::::A       P::::P              P::::P               1::::l    \r\n");
  printf("    A:::::AAAAAAAAAAAAA:::::A      P::::P              P::::P               1::::l     \r\n");
  printf("   A:::::A             A:::::A    PP::::::PP          PP::::::PP          111::::::111 \r\n");
  printf("  A:::::A               A:::::A  P::::::::P          P::::::::P          1::::::::::1 \r\n");
  printf(" A:::::A                 A:::::A P::::::::P          P::::::::P          1::::::::::1 \r\n");
  printf("AAAAAAA                   AAAAAAAPPPPPPPPPP          PPPPPPPPPP          111111111111 \r\n\r\n\r\n");
  printf(" jump to app1 success\r\n\r\n\r\n");                                                                           
      


   
	 
                                                                                             
                                                                                             
//  printf("              AAA               PPPPPPPPPPPPPPPPP   PPPPPPPPPPPPPPPPP    222222222222222    \r\n");
//  printf("             A:::A              P::::::::::::::::P  P::::::::::::::::P  2:::::::::::::::22  \r\n");
//  printf("            A:::::A             P::::::PPPPPP:::::P P::::::PPPPPP:::::P 2::::::222222:::::2 \r\n");
//  printf("           A:::::::A            PP:::::P     P:::::PPP:::::P     P:::::P2222222     2:::::2 \r\n");
//  printf("          A:::::::::A             P::::P     P:::::P  P::::P     P:::::P            2:::::2 \r\n");
//  printf("          A:::::A:::::A            P::::P     P:::::P  P::::P     P:::::P            2:::::2 \r\n");
//  printf("         A:::::A A:::::A           P::::PPPPPP:::::P   P::::PPPPPP:::::P          2222::::2  \r\n");
//  printf("        A:::::A   A:::::A          P:::::::::::::PP    P:::::::::::::PP      22222::::::22   \r\n");
//  printf("       A:::::A     A:::::A         P::::PPPPPPPPP      P::::PPPPPPPPP      22::::::::222     \r\n");
//  printf("      A:::::AAAAAAAAA:::::A        P::::P              P::::P             2:::::22222        \r\n");
//  printf("     A:::::::::::::::::::::A       P::::P              P::::P            2:::::2             \r\n");
//  printf("    A:::::AAAAAAAAAAAAA:::::A      P::::P              P::::P            2:::::2             \r\n");
//  printf("   A:::::A             A:::::A   PP::::::PP          PP::::::PP          2:::::2       222222\r\n");
//  printf("  A:::::A               A:::::A  P::::::::P          P::::::::P          2::::::2222222:::::2\r\n");
//  printf(" A:::::A                 A:::::A P::::::::P          P::::::::P          2::::::::::::::::::2\r\n");
//  printf("AAAAAAA                   AAAAAAAPPPPPPPPPP          PPPPPPPPPP          22222222222222222222\r\n\r\n\r\n");
//  printf(" jump to app2 success\r\n\r\n\r\n");                                                                                           
//                                                                                             
//                                                                                           
//       
	 
   
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
		
		LEDB_TOGGLE();
		HAL_Delay(500);
		
     
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

  /** Supply configuration update enable
  */
  HAL_PWREx_ConfigSupply(PWR_LDO_SUPPLY);

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  __HAL_RCC_SYSCFG_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE0);

  while(!__HAL_PWR_GET_FLAG(PWR_FLAG_VOSRDY)) {}

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 5;
  RCC_OscInitStruct.PLL.PLLN = 192;
  RCC_OscInitStruct.PLL.PLLP = 2;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL1VCIRANGE_2;
  RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL1VCOWIDE;
  RCC_OscInitStruct.PLL.PLLFRACN = 0;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2
                              |RCC_CLOCKTYPE_D3PCLK1|RCC_CLOCKTYPE_D1PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB3CLKDivider = RCC_APB3_DIV2;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_APB2_DIV2;
  RCC_ClkInitStruct.APB4CLKDivider = RCC_APB4_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM7 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM7) {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

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
