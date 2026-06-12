#include "KEY.h"

#define KEY_DEBOUNCE_TIME   20
static uint8_t key_triggered[2] = {0};

static void delay_ms(uint32_t ms) {
    HAL_Delay(ms);
}

Key_ID KEY_Scan(void) {
    uint8_t key1_down = (HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin) == GPIO_PIN_RESET);
    uint8_t key2_down = (HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin) == GPIO_PIN_RESET);

    if (key1_down) {
        if (!key_triggered[0]) {
            delay_ms(KEY_DEBOUNCE_TIME);
            if (HAL_GPIO_ReadPin(KEY_1_GPIO_Port, KEY_1_Pin) == GPIO_PIN_RESET) {
                key_triggered[0] = 1;
                return KEY_1;
            }
        }
    } else {
        key_triggered[0] = 0;
    }

    if (key2_down) {
        if (!key_triggered[1]) {
            delay_ms(KEY_DEBOUNCE_TIME);
            if (HAL_GPIO_ReadPin(KEY_2_GPIO_Port, KEY_2_Pin) == GPIO_PIN_RESET) {
                key_triggered[1] = 1;
                return KEY_2;
            }
        }
    } else {
        key_triggered[1] = 0;
    }

    return KEY_NONE;
}

void KEY_Init(void) {
    // GPIO已由MX_GPIO_Init配置
}