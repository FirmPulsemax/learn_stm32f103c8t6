#include "motor.h"
#include "tim.h"

extern TIM_HandleTypeDef htim2;

void Motor_Init(void)
{
    // 停止电机
    HAL_GPIO_WritePin(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN, GPIO_PIN_RESET);
    // 启动 PWM 输出
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    // 占空比设为 0
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 0);
}

void Motor_SetSpeed(uint16_t duty)
{
    if (duty > PWM_MAX_DUTY) duty = PWM_MAX_DUTY;
    __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, duty);
}

void Motor_SetDirection(Motor_Direction dir)
{
    switch (dir)
    {
        case MOTOR_STOP:
            HAL_GPIO_WritePin(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN, GPIO_PIN_RESET);
            break;
        case MOTOR_FORWARD:
            HAL_GPIO_WritePin(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN, GPIO_PIN_SET);
            HAL_GPIO_WritePin(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN, GPIO_PIN_RESET);
            break;
        case MOTOR_BACKWARD:
            HAL_GPIO_WritePin(MOTOR_AIN1_PORT, MOTOR_AIN1_PIN, GPIO_PIN_RESET);
            HAL_GPIO_WritePin(MOTOR_AIN2_PORT, MOTOR_AIN2_PIN, GPIO_PIN_SET);
            break;
    }
}

void Motor_Control(Motor_Direction dir, uint16_t speed_percent)
{
    if (speed_percent == 0)
    {
        Motor_SetDirection(MOTOR_STOP);
        Motor_SetSpeed(0);
        return;
    }
    if (speed_percent > 100) speed_percent = 100;
    uint32_t duty = (uint32_t)speed_percent * PWM_MAX_DUTY / 100;
    Motor_SetDirection(dir);
    Motor_SetSpeed((uint16_t)duty);
}