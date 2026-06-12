#ifndef __FIRE_SENSOR_H
#define __FIRE_SENSOR_H

#include "stdint.h"

#define FIRE_ADC_CHANNEL   ADC_CHANNEL_8   // PB0

void fire_sensor_init(void);
uint16_t fire_read_adc(void);
uint8_t fire_read_digital(void);   // 读取 fire_do_Pin

#endif