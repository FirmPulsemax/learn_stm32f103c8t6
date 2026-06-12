#ifndef __KEY_H
#define __KEY_H

#include "main.h"

typedef enum {
    KEY_NONE = 0,
    KEY_1,
    KEY_2
} Key_ID;

void KEY_Init(void);
Key_ID KEY_Scan(void);

#endif