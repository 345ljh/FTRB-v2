#ifndef _APP_H
#define _APP_H

#include "app.h"
#include "malloc.h"
#include "stdlib.h"

typedef enum position_e{
    position_center = 0, 
    position_edge, 
    position_fall
}Position;

typedef enum target_e{
    target_none = 0,
    target_robot,
    target_block, 
    target_enemyblock
}Target;

typedef struct robot_t{
    //状态量
    Position position;
    Target target;

    //传感器
    WT53E* dist_forward_l;
    WT53E* dist_forward_r;
    WT53E* dist_left;
    WT53E* dist_right;
    Dist_sensor* dist_up;   //位于forword上方的测距
    Grayscale* grayscale;

    //电机与舵机
    Motor* motor_lf;
    Motor* motor_rf;
    Motor* motor_lb;
    Motor* motor_rb;
    Servo* servo_l;
    Servo* servo_r;

    Openmv* openmv;
}Robot;

#endif