#include "motor.h"

Motor* motors[4];

void PID_Calc(PID* obj){
    obj->last_error = obj->error;
    obj->error = obj->ref - obj->fdb;
    obj->error_sum += obj->error;

    if(obj->error_sum > obj->config.error_sum_max) obj->error_sum = obj->config.error_sum_max; 	//Clamp Error Sum to Max Value
    else if(obj->error_sum < -obj->config.error_sum_max) obj->error_sum = -obj->config.error_sum_max;

    obj->output = obj->config.kp * obj->error + obj->config.ki * obj->error_sum + obj->config.kd * (obj->error - obj->last_error);

    if(obj->output > obj->config.output_max) obj->output = obj->config.output_max; 	//Clamp Output To Max Value
    else if(obj->output < -obj->config.output_max) obj->output = -obj->config.output_max;	//Clamp Output
}

Motor* Motor_Create(Motor_config* config){
    static uint8_t isregisted = 0;
    if(!isregisted) {
        can_devices.call_back = CanMotor_RxCallBack;
        isregisted = 1; 		//Registering Successful
    }

    Motor* obj = (Motor*)malloc(sizeof(Motor));
    memset(obj, 0, sizeof(Motor));
    obj->config = *config;
    obj->pid.config = config->pid_config;
    obj->fdb_pos = -10000;

    BSP_CAN_AddFilter(0, 0x200 + obj->config.motor_id);
    obj->enable = 0;
    return obj;
}

void Motor_Update(Motor* obj){
    obj->pid.fdb = obj->fdb_speed / 60.0 * 6.28 * obj->config.radius;	//转换单位ref->m/s
    obj->pid.ref = obj->ref_speed;
    PID_Calc(&obj->pid);
    obj->buffer = (uint16_t)obj->pid.output * obj->enable;
}

void Motor_Send(void){
    static uint8_t send_data[8];
    send_data[0] = (uint8_t)(motors[0]->buffer >> 8);
    send_data[1] = (uint8_t)(motors[0]->buffer & 0xFF);
    send_data[2] = (uint8_t)(motors[1]->buffer >> 8);
    send_data[3] = (uint8_t)(motors[1]->buffer & 0xFF);
    send_data[4] = (uint8_t)(motors[2]->buffer >> 8);
    send_data[5] = (uint8_t)(motors[2]->buffer & 0xFF);
    send_data[6] = (uint8_t)(motors[3]->buffer >> 8);
    send_data[7] = (uint8_t)(motors[3]->buffer & 0xFF);
    BSP_CAN_Send(0, 0x200, send_data, 8);
}

void CanMotor_RxCallBack(uint32_t identifier, uint8_t *data, uint32_t len){
    if(identifier >= 0x201 && identifier <= 0x204){
        uint8_t id = identifier - 0x200 - 1;
        motors[id]->fdb_pos = ((uint16_t)data[0] << 8) | data[1];
        motors[id]->fdb_speed = ((uint16_t)data[2] << 8) | data[3];
        motors[id]->fdb_curr = ((uint16_t)data[4] << 8) | data[5];
    }
}

void Motor_Send_Empty(void){
    uint8_t data[8];
    data[0] = 0;
    data[1] = 0;
    data[2] = 0x0E;
    data[3] = 0X0F;
    data[4] = 0;
    data[5] = 0;
    data[6] = 0;
    data[7] = 0;
    BSP_CAN_Send(0, 0x200, data, 8);
}