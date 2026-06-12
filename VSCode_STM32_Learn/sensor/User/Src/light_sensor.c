#include "light_sensor.h"
#include "adc.h"
#include "gpio.h"

void light_sensor_init(void)
{
}

uint16_t light_read_adc(void)
{
    uint16_t adc_value = 0;
    ADC_ChannelConfTypeDef sConfig = {0};

    sConfig.Channel = LIGHT_ADC_CHANNEL;
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

uint8_t light_read_digital(void)
{
    return HAL_GPIO_ReadPin(GPIOB, light_do_Pin);
}