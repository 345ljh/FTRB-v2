#include "wt53d.h"

//50 03 00 34 00 01 C8 45

uint8_t send_data[8] = {0x50, 0x03, 0x00, 0x34, 0x00, 0x01, 0xC8, 0x45};

WT53D* wt53d[4];   //对应uart1~4

WT53D* WT53D_Create(WT53D_Config* config){
    WT53D* obj = (WT53D*)malloc(sizeof(WT53D));
    memset(obj, 0, sizeof(WT53D));
    obj->config = *config;
    HAL_UART_Receive_IT(obj->config.huart, obj->buf, 7);
    return obj;
}

void WT53D_RxCallBack(UART_HandleTypeDef *huart){
    for(int i = 0; i <= 3; i++){
        if(huart == wt53d[i]->config.huart){   //判断串口对应测距模块
            wt53d[i]->distance = (uint16_t)(wt53d[i]->buf[3] << 8) + (wt53d[i]->buf[4]);
            HAL_UART_Receive_IT(wt53d[i]->config.huart, wt53d[i]->buf, 7);
        }
    }
}

void WT53D_UART_IRQHandler(UART_HandleTypeDef *huart) {
    WT53D_RxCallBack(huart);
}

void WT53D_Send_All(void){
    for(int i = 0; i <= 3; i++) HAL_UART_Transmit(wt53d[i]->config.huart, send_data, 8, 1000);
}