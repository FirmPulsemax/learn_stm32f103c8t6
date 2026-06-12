#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"

// 引脚定义直接使用 main.h 中的宏
#define MOTOR_AIN1_PIN      MOTOR_DIR1_Pin
#define MOTOR_AIN1_PORT     MOTOR_DIR1_GPIO_Port
#define MOTOR_AIN2_PIN      MOTOR_DIR2_Pin
#define MOTOR_AIN2_PORT     MOTOR_DIR2_GPIO_Port

// PWM 最大值（必须与 TIM2 的 Period 一致，您 tim.c 中为 99）
#define PWM_MAX_DUTY        99

typedef enum {
    MOTOR_STOP = 0,
    MOTOR_FORWARD,
    MOTOR_BACKWARD
} Motor_Direction;

void Motor_Init(void);
void Motor_SetSpeed(uint16_t duty);                  // duty: 0 ~ PWM_MAX_DUTY
void Motor_SetDirection(Motor_Direction dir);
void Motor_Control(Motor_Direction dir, uint16_t speed_percent);  // speed_percent: 0~100

#endif