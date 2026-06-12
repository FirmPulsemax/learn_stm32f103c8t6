#include "LED.h"

void LED_Init(void) {
    LED_R_Off();
    LED_G_Off();
    LED_B_Off();
}

void LED_R_On(void) {
    HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_RESET);
}
void LED_R_Off(void) {
    HAL_GPIO_WritePin(LED_R_GPIO_Port, LED_R_Pin, GPIO_PIN_SET);
}
void LED_R_Toggle(void) {
    HAL_GPIO_TogglePin(LED_R_GPIO_Port, LED_R_Pin);
}

void LED_G_On(void) {
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
}
void LED_G_Off(void) {
    HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_SET);
}
void LED_G_Toggle(void) {
    HAL_GPIO_TogglePin(LED_G_GPIO_Port, LED_G_Pin);
}

void LED_B_On(void) {
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);
}
void LED_B_Off(void) {
    HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_SET);
}
void LED_B_Toggle(void) {
    HAL_GPIO_TogglePin(LED_B_GPIO_Port, LED_B_Pin);
}
