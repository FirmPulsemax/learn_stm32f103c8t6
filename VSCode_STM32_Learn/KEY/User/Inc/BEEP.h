#ifndef __BEEP_H
#define __BEEP_H

#include "main.h"

// 与 gpio.c 中使用的宏名称保持一致
#define BEEP_Pin        GPIO_PIN_12
#define BEEP_GPIO_Port  GPIOB

void BEEP_Init(void);
void BEEP_On(void);
void BEEP_Off(void);

#endif