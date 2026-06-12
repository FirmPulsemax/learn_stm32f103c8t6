#include "myadc.h"
#include "adc.h"          // 引用 CubeMX 生成的 ADC 头文件，其中声明了 hadc1 和 MX_ADC1_Init
#include "stm32f1xx_hal.h"

// 初始化 ADC：调用 CubeMX 生成的初始化，并启动连续转换
void ADC_Init(void)
{
    MX_ADC1_Init();       // 已在 adc.c 中实现
    HAL_ADC_Start(&hadc1); // hadc1 在 adc.c 中定义，外部可见
}

// 读取 ADC 值（阻塞等待转换完成，超时10ms）
uint16_t ADC_GetValue(void)
{
    if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
    {
        return (uint16_t)HAL_ADC_GetValue(&hadc1);
    }
    else
    {
        return 0;
    }
}