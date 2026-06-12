#ifndef __SERVON_H
#define __SERVON_H

#include "stm32f1xx_hal.h"

/**
 * @brief 舵机初始化，启动 PWM 输出
 */
void Servo_Init(void);

/**
 * @brief 设置舵机角度（绝对位置）
 * @param angle    目标角度，范围 0 ~ 180
 * @param direction 运动方向（保留参数，0=逆时针，1=顺时针，实际由绝对角度决定）
 */
void Servo_SetAngle(uint8_t angle, uint8_t direction);

/**
 * @brief 直接设置绝对角度（内部函数也可供外部调用）
 * @param angle 目标角度，范围 0 ~ 180
 */
void Servo_SetAngleAbs(uint8_t angle);

#endif /* __SERVON_H */