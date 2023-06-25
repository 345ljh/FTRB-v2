#ifndef _BSP_CAN_H
#define _BSP_CAN_H
#include "stdint.h"
#include "can.h"

typedef void (*can_rx_callback)(uint32_t identifier, uint8_t* data,
                                uint32_t len);

typedef struct BSP_CanTypeDef_t {
    CAN_HandleTypeDef *device;  //自定义总线编号
    uint32_t tx_mailbox;
    can_rx_callback call_back;
    uint32_t bank_prefix;              //不同can对应的过滤器相关参数值
    uint16_t filters[56];  //按标准帧ID定义
} BSP_CanTypeDef;

extern BSP_CanTypeDef can_devices;

void BSP_CAN_Init();
void BSP_CAN_AddFilter(uint8_t can_id, uint16_t filter);
void BSP_CAN_RemoveFilter(uint8_t can_id, uint16_t filter);
void BSP_CAN_Send(uint8_t can_id, uint16_t identifier, uint8_t* data,
                  uint32_t len);
#endif