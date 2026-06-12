#include "servon.h"
#include "tim.h"   // 包含 htim4 句柄

extern TIM_HandleTypeDef htim4;  // 声明在 tim.c 中定义的定时器句柄

/**
 * @brief 舵机初始化：启动 TIM4 的 PWM 通道 3，并设置中位 90°
 */
void Servo_Init(void)
{
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3);
    Servo_SetAngleAbs(90);  // 初始位置设为 90°
}

/**
 * @brief 绝对角度控制核心函数
 * @param angle 0~180
 * @note  脉宽计算：0° -> 0.5ms (500计数)，180° -> 2.5ms (2500计数)
 *        公式：pulse = 500 + angle * 100 / 9
 */
void Servo_SetAngleAbs(uint8_t angle)
{
    uint16_t pulse;

    if (angle > 180)
        angle = 180;

    // 整数运算，避免浮点：pulse = 500 + (angle * 2000) / 180
    pulse = 500 + (angle * 100) / 9;

    __HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, pulse);
}

/**
 * @brief 带方向的舵机角度设置（方向参数在此版本中未使用，因为绝对角度已确定位置）
 * @param angle     目标角度 0~180
 * @param direction 0=逆时针，1=顺时针（保留，可扩展相对运动）
 */
void Servo_SetAngle(uint8_t angle, uint8_t direction)
{
    // 若需要实现相对步进运动，可根据 direction 和当前角度计算新目标
    // 当前版本直接设置为绝对角度
    Servo_SetAngleAbs(angle);
}