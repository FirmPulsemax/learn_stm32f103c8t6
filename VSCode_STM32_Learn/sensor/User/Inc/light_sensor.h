#ifndef __LIGHT_SENSOR_H
#define __LIGHT_SENSOR_H

#include "stdint.h"

#define LIGHT_ADC_CHANNEL   ADC_CHANNEL_9   // PB1

void light_sensor_init(void);
uint16_t light_read_adc(void);
uint8_t light_read_digital(void);   // 读取 light_do_Pin

#endif