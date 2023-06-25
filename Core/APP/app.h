#ifndef _APP_H
#define _APP_H

#include "app.h"
#include "malloc.h"
#include "stdlib.h"
#include "string.h"


#include "wt53d.h"
#include "motor.h"

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
    WT53D* dist_forward_l;
    WT53D* dist_forward_r;
    WT53D* dist_left;
    WT53D* dist_right;
    // Dist_sensor* dist_up;   //位于forword上方的测距
    // Grayscale* grayscale;

    //电机与舵机
    Motor* motor_lf;
    Motor* motor_rf;
    Motor* motor_lb;
    Motor* motor_rb;
    // Servo* servo_l;
    // Servo* servo_r;

    // Openmv* openmv;
}Robot;

extern Robot* robot;

Robot* Robot_Create(void);
#endif