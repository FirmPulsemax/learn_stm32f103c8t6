#include "temp.h"
#include "gpio.h"   // 包含 TEMP_Pin, TEMP_GPIO_Port

// 定义引脚操作宏（开漏输出，默认为高电平）
#define TEMP_HIGH()  HAL_GPIO_WritePin(TEMP_GPIO_Port, TEMP_Pin, GPIO_PIN_SET)
#define TEMP_LOW()   HAL_GPIO_WritePin(TEMP_GPIO_Port, TEMP_Pin, GPIO_PIN_RESET)
#define TEMP_READ()  HAL_GPIO_ReadPin(TEMP_GPIO_Port, TEMP_Pin)

// 使用 DWT 实现微秒延时
static void Delay_us(uint32_t us)
{
    // 读取当前计数值
    uint32_t start = DWT->CYCCNT;
    uint32_t cycles = us * (SystemCoreClock / 1000000);  // 计算所需时钟周期数
    while ((DWT->CYCCNT - start) < cycles);
}

// 初始化 DWT 计数器（只需调用一次）
static void DWT_Init(void)
{
    // 使能 DWT 调试组件
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    // 复位并使能 DWT 计数器
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

// 初始化引脚 (PB13 开漏输出)
void Temp_Init(void)
{
    GPIO_InitTypeDef gpio_init = {0};
    gpio_init.Pin = TEMP_Pin;
    gpio_init.Mode = GPIO_MODE_OUTPUT_OD;
    gpio_init.Pull = GPIO_PULLUP;       // 内部上拉辅助（最好外部加4.7k）
    gpio_init.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(TEMP_GPIO_Port, &gpio_init);
    TEMP_HIGH();

    // 初始化 DWT 微秒延时
    DWT_Init();
}

// 复位并检测器件存在
static uint8_t Temp_Reset(void)
{
    uint8_t presence;
    TEMP_LOW();
    Delay_us(500);
    TEMP_HIGH();
    Delay_us(70);
    presence = TEMP_READ();
    Delay_us(250);
    return presence;   // 0 表示存在
}

// 写一个位
static void Temp_WriteBit(uint8_t bit)
{
    if (bit)
    {
        TEMP_LOW();
        Delay_us(2);
        TEMP_HIGH();
        Delay_us(62);
    }
    else
    {
        TEMP_LOW();
        Delay_us(70);
        TEMP_HIGH();
        Delay_us(2);
    }
}

// 读一个位
static uint8_t Temp_ReadBit(void)
{
    uint8_t bit;
    TEMP_LOW();
    Delay_us(2);
    TEMP_HIGH();
    Delay_us(1);
    bit = TEMP_READ();
    Delay_us(60);
    return bit;
}

// 写一个字节（低位先行）
static void Temp_WriteByte(uint8_t data)
{
    for (uint8_t i = 0; i < 8; i++)
    {
        Temp_WriteBit((data >> i) & 0x01);
    }
}

// 读一个字节（低位先行）
static uint8_t Temp_ReadByte(void)
{
    uint8_t data = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        if (Temp_ReadBit())
            data |= (1 << i);
    }
    return data;
}

// 读取温度（带重试机制）
float Temp_Read(void)
{
    for (int retry = 0; retry < 3; retry++)
    {
        if (Temp_Reset() != 0) {
            HAL_Delay(10);
            continue;
        }
        Temp_WriteByte(0xCC);   // 跳过 ROM
        Temp_WriteByte(0x44);   // 启动转换
        HAL_Delay(750);

        if (Temp_Reset() != 0) {
            HAL_Delay(10);
            continue;
        }
        Temp_WriteByte(0xCC);
        Temp_WriteByte(0xBE);   // 读暂存器
        uint8_t lsb = Temp_ReadByte();
        uint8_t msb = Temp_ReadByte();
        int16_t raw = (int16_t)((msb << 8) | lsb);
        float temp = raw * 0.0625f;

        // 验证温度范围是否合理
        if (temp >= -55.0f && temp <= 125.0f)
            return temp;
    }
    // 如果三次都失败，返回上次成功值？更简单：返回 -999 让上层处理
    return -999.0f;
}