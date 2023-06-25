#ifndef _MOTOR_H
#define _MOTOR_H

#include "can.h"
#include "malloc.h"
#include "bsp_can.h"
#include "string.h"

typedef struct pid_config_t
{
    float kp;
    float ki;
    float kd;
    float error_sum_max;
    float output_max;
}PID_config;

typedef struct pid_t
{
    PID_config config;
    float ref;
    float fdb;
    float error;
    float error_sum;
    float last_error;
    float output;
}PID;

typedef struct motor_config_t
{
    uint16_t motor_id;
    PID_config pid_config;
    float radius;    //轮径
}Motor_config;

typedef struct motor_t
{
    Motor_config config;
    uint16_t motor_id;
    uint8_t enable;  // =1时使能电机
    int16_t fdb_pos;
    int16_t fdb_speed;
    int16_t fdb_curr;
    float ref_speed;
    PID pid;
    uint16_t buffer;
}Motor;

extern Motor* motors[4];

void CanMotor_RxCallBack(uint32_t identifier, uint8_t *data, uint32_t len);
Motor* Motor_Create(Motor_config* config);
void Motor_Send_Empty(void);

#endif