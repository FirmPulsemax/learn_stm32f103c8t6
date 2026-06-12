#ifndef __MYADC_H
#define __MYADC_H

#include <stdint.h>

void ADC_Init(void);          // 初始化 ADC（调用 MX_ADC1_Init 并启动连续转换）
uint16_t ADC_GetValue(void);  // 读取 ADC 值

#endif