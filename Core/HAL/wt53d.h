#ifndef _WT53D_H
#define _WT53D_H

#include "usart.h"
#include "malloc.h"
#include "string.h"

typedef struct wt53d_config_t
{
    UART_HandleTypeDef *huart;
}WT53D_Config;

typedef struct wt53d_t {
    WT53D_Config config;
    uint8_t buf[7];	
    uint16_t distance;  //单位mm
}WT53D;

extern WT53D* wt53d[4];

WT53D* WT53D_Create(WT53D_Config* config);
void WT53D_UART_IRQHandler(UART_HandleTypeDef *huart);
void WT53D_Send_All(void);

#endif