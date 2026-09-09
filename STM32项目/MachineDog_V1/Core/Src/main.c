/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : 8 路舵机来回摆动 + UART 状态上报(v1 测试版)
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
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
  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM17_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  /* ⚠️ CubeMX 不自动调 HAL_TIM_PWM_MspPostInit → 必须手动启动 HAL_TIM_PWM_Start */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);    /* PA8  = TIM1_CH1 = servo7 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);    /* PA5  = TIM2_CH1 = servo3 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);    /* PA2  = TIM2_CH3 = servo0 */
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);    /* PA3  = TIM2_CH4 = servo1 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);    /* PA6  = TIM3_CH1 = servo4 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);    /* PA4  = TIM3_CH2 = servo2 */
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);    /* PB0  = TIM3_CH3 = servo6 */
  HAL_TIM_PWM_Start(&htim17, TIM_CHANNEL_1);   /* PA7  = TIM17_CH1 = servo5 */
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN 3 */
    /* 8 路舵机来回摆动:右 → 中 → 左 → 中 (各 800ms) */

    /* 右侧 2000 (2.0ms = +90°) */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 2000);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 2000);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 2000);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 2000);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 2000);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 2000);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 2000);
    __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 2000);
    HAL_Delay(800);

    /* 中位 1500 */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1500);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 1500);
    __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 1500);
    HAL_Delay(800);

    /* 左侧 1000 */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1000);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1000);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1000);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1000);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1000);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1000);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 1000);
    __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 1000);
    HAL_Delay(800);

    /* 再回中位 1500 */
    __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 1500);
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 1500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 1500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 1500);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 1500);
    __HAL_TIM_SET_COMPARE(&htim17, TIM_CHANNEL_1, 1500);
    HAL_Delay(800);
    /* USER CODE END 3 */
  }
}

/**
  * @brief System Clock Configuration - HSE 8MHz / PLL x42 / SYSCLK 168MHz
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 42;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) { Error_Handler(); }

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) { Error_Handler(); }
}

/* USER CODE BEGIN 4 */
/* USER CODE END 4 */

void Error_Handler(void)
{
  __disable_irq();
  while (1) {}
}
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {}
#endif