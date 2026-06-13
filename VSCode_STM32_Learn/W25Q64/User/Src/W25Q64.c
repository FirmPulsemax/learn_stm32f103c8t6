#include "W25Q64.h"
#include "W25Q64_Ins.h"
#include "spi.h"
#include "gpio.h"

#define W25Q_CS_PIN     GPIO_PIN_4
#define W25Q_CS_PORT    GPIOA

static void W25Q_CS_Set(uint8_t level)
{
    HAL_GPIO_WritePin(W25Q_CS_PORT, W25Q_CS_PIN, level ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

static uint8_t SPI_SwapByte(uint8_t send_dat)
{
    uint8_t recv_dat = 0xFF;
    if(HAL_SPI_TransmitReceive(&hspi1, &send_dat, &recv_dat, 1, 50) != HAL_OK)
    {
        HAL_SPI_Abort(&hspi1);
        return 0xFF;
    }
    return recv_dat;
}

void W25Q64_Init(void)
{
    GPIO_InitTypeDef gpio_cfg = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
    gpio_cfg.Pin = W25Q_CS_PIN;
    gpio_cfg.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_cfg.Speed = GPIO_SPEED_FREQ_LOW;
    gpio_cfg.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(W25Q_CS_PORT, &gpio_cfg);

    W25Q_CS_Set(1);
    HAL_Delay(20);
}

void W25Q64_ReadID(uint8_t *MID, uint16_t *DID)
{
    uint8_t high, low;
    W25Q_CS_Set(0);
    HAL_Delay(1);
    SPI_SwapByte(W25Q_READ_JEDEC_ID);
    *MID = SPI_SwapByte(W25Q_DUMMY);
    high = SPI_SwapByte(W25Q_DUMMY);
    low  = SPI_SwapByte(W25Q_DUMMY);
    W25Q_CS_Set(1);
    HAL_Delay(1);
    *DID = (high << 8) | low;
}

static void W25Q_WriteEnable(void)
{
    W25Q_CS_Set(0);
    HAL_Delay(1);
    SPI_SwapByte(W25Q_WRITE_EN);
    W25Q_CS_Set(1);
    HAL_Delay(1);
}

static void W25Q_WaitBusy(void)
{
    uint32_t timeout = 150000;
    W25Q_CS_Set(0);
    HAL_Delay(1);
    SPI_SwapByte(W25Q_READ_STATUS1);
    while((SPI_SwapByte(W25Q_DUMMY) & 0x01) && timeout--)
    {
    }
    W25Q_CS_Set(1);
}

void W25Q64_SectorErase(uint32_t addr)
{
    W25Q_WriteEnable();
    W25Q_CS_Set(0);
    SPI_SwapByte(W25Q_SECTOR_ERASE);
    SPI_SwapByte((addr >> 16) & 0xFF);
    SPI_SwapByte((addr >> 8) & 0xFF);
    SPI_SwapByte(addr & 0xFF);
    W25Q_CS_Set(1);
    W25Q_WaitBusy();
}

void W25Q64_PageProgram(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    if(len > 256) len = 256;
    W25Q_WriteEnable();
    W25Q_CS_Set(0);
    SPI_SwapByte(W25Q_PAGE_WRITE);
    SPI_SwapByte((addr >> 16) & 0xFF);
    SPI_SwapByte((addr >> 8) & 0xFF);
    SPI_SwapByte(addr & 0xFF);
    for(i = 0; i < len; i++)
    {
        SPI_SwapByte(buf[i]);
    }
    W25Q_CS_Set(1);
    W25Q_WaitBusy();
}

void W25Q64_ReadData(uint32_t addr, uint8_t *buf, uint16_t len)
{
    uint16_t i;
    W25Q_CS_Set(0);
    SPI_SwapByte(W25Q_READ_DATA);
    SPI_SwapByte((addr >> 16) & 0xFF);
    SPI_SwapByte((addr >> 8) & 0xFF);
    SPI_SwapByte(addr & 0xFF);
    for(i = 0; i < len; i++)
    {
        buf[i] = SPI_SwapByte(W25Q_DUMMY);
    }
    W25Q_CS_Set(1);
}