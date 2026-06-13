#ifndef __W25Q64_H
#define __W25Q64_H

#include "stdint.h"

void W25Q64_Init(void);
void W25Q64_ReadID(uint8_t *MID, uint16_t *DID);
void W25Q64_SectorErase(uint32_t addr);
void W25Q64_PageProgram(uint32_t addr, uint8_t *buf, uint16_t len);
void W25Q64_ReadData(uint32_t addr, uint8_t *buf, uint16_t len);

#endif