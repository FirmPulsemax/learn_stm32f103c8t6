#ifndef __TEMP_H
#define __TEMP_H

#include "stm32f1xx_hal.h"

void Temp_Init(void);
float Temp_Read(void);

#endif