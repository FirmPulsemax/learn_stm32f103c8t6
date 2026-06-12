#include "fire_sensor.h"
#include "adc.h"
#include "gpio.h"   // 包含 fire_do_Pin

void fire_sensor_init(void)
{
    // 无额外初始化
}

uint16_t fire_read_adc(void)
{
    uint16_t adc_value = 0;
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = FIRE_ADC_CHANNEL;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
        return 0;

    HAL_ADC_Start(&hadc1);
    if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK)
        adc_value = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
    return adc_value;
}

uint8_t fire_read_digital(void)
{
    return HAL_GPIO_ReadPin(GPIOB, fire_do_Pin);
}