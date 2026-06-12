#ifndef __LED_H
#define __LED_H

#include "main.h"

// 与 gpio.c 中使用的宏名称保持一致
#define LED_R_Pin       GPIO_PIN_14
#define LED_R_GPIO_Port GPIOB

#define LED_G_Pin       GPIO_PIN_15
#define LED_G_GPIO_Port GPIOB

#define LED_B_Pin       GPIO_PIN_8
#define LED_B_GPIO_Port GPIOA

void LED_Init(void);

void LED_R_On(void);
void LED_R_Off(void);
void LED_R_Toggle(void);

void LED_G_On(void);
void LED_G_Off(void);
void LED_G_Toggle(void);

void LED_B_On(void);
void LED_B_Off(void);
void LED_B_Toggle(void);

#endif