/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */

#include "main.h"
#include "gpio.h"
#include "adc.h"          // CubeMX 生成的 ADC 头文件
#include "myadc.h"        // 您的封装头文件
#include "oled.h"         // OLED 头文件

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

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  // 注意：不要在这里调用 MX_ADC1_Init()，因为 ADC_Init() 内部会调用它
  // 如果您的 main.c 原本有 MX_ADC1_Init(); 请注释掉或删除

  /* USER CODE BEGIN 2 */
  OLED_Init();          // 初始化 OLED
  ADC_Init();           // 初始化 ADC 并启动连续转换
  /* USER CODE END 2 */

  while (1)
  {
    /* USER CODE BEGIN 3 */
    uint16_t adc_value = ADC_GetValue();
    float voltage = adc_value * 3.3f / 4095.0f;

    OLED_ShowString(1, 1, "ADC:");
    OLED_ShowNum(1, 6, adc_value, 4);

    OLED_ShowString(2, 1, "Voltage:");
    uint32_t int_part = (uint32_t)voltage;
    uint32_t frac_part = (uint32_t)((voltage - int_part) * 100);
    OLED_ShowNum(2, 9, int_part, 1);
    OLED_ShowChar(2, 10, '.');
    OLED_ShowNum(2, 11, frac_part, 2);

    HAL_Delay(100);
    /* USER CODE END 3 */
  }
}

/* 下面是您原有的 SystemClock_Config 和 Error_Handler，保持不变 */
void SystemClock_Config(void)
{
  // ... 保持不变 ...
}

void Error_Handler(void)
{
  // ... 保持不变 ...
}