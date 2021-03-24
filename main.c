
#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#define TX_BUFFER_SIZE 256 	// Buffer uzunluklarini tanimla (256).
#define RX_BUFFER_SIZE 8   	// Gelen veri buffer uzunlugu


/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */
void convertCharToint(void);
void debugPrintf(char *format, ...);	
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* Degiskenler */
	uint8_t rx[RX_BUFFER_SIZE];
	uint8_t rxToint[RX_BUFFER_SIZE];
	uint8_t serialStatus = 0;
	char TX_BUFFER[TX_BUFFER_SIZE];
	uint8_t UART_TRANSMIT_READY = 1;
/* Degisken tanimlamari biter */

/**
  * @brief  The application entry point.
  * @retval int
  */
	


int main(void)
{
  /* Inits */
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_USART2_UART_Init();
	HAL_UART_Receive_IT(&huart2, rx, RX_BUFFER_SIZE); // assigned to RX char buffer
  while (1)
  {	

			debugPrintf("\n Test String Contains Varying Data Types Integer = %d, float = %f, float = %0.3f \r\n", 1, 0.25, (float)1/3);
			HAL_Delay(1000);
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
  /** Configure the main internal regulator output voltage
  */
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

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


void convertCharToint(void)
{
	/*
			@ Bu fonksiyon, gelen veriyi Int tipine donusturmektedir.
	*/
	for(uint16_t i=0;i<RX_BUFFER_SIZE;i++)
	{
		rxToint[i] = rx[i] - '0'; // rx buffer variables are converted to unsinged integers.
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // if RX buffer flag is set,
{
  HAL_UART_Receive_IT(&huart2, rx, RX_BUFFER_SIZE); 
	convertCharToint();  // gelen veriyi donustur
	serialStatus = 1; // eger veri okunursa serial status set olsun.
}

void debugPrintf(char *format, ...) // own printf function // format free
{
	
	va_list args;
	va_start(args, format);
	uint8_t len; // verinin uzunlugu
  len = vsprintf(TX_BUFFER, format, args);
	while(UART_TRANSMIT_READY == 0);
	UART_TRANSMIT_READY = 0;
	if(HAL_UART_Transmit_IT(&huart2, (uint8_t*)TX_BUFFER, len)!= HAL_OK)
  {
    Error_Handler();
  }	
	va_end(args);
	
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) // TX process is complete flag is set.
{
	UART_TRANSMIT_READY = 1;
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
