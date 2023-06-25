#include "app.h"

#define DIST_EDGE 1000 //检测是否在边缘
#define DIST_AREA 700 //检测是否在台上
#define GRAY_EDGE 128 

Robot* robot;

Robot* Robot_Create(void) {
    Robot* obj = malloc(sizeof(Robot));
    memset(obj, 0, sizeof(Robot));

    //创建各种外设
    WT53D_Config dist_forward_l_config;
    dist_forward_l_config.huart = &huart1;
    obj->dist_forward_l = WT53D_Create(&dist_forward_l_config);
    wt53d[0] = obj->dist_forward_l;

    WT53D_Config dist_forward_r_config;
    dist_forward_r_config.huart = &huart2;
    obj->dist_forward_r = WT53D_Create(&dist_forward_r_config);
    wt53d[1] = obj->dist_forward_r;

    WT53D_Config dist_l_config;
    dist_l_config.huart = &huart3;
    obj->dist_left = WT53D_Create(&dist_l_config);
    wt53d[2] = obj->dist_left;

    WT53D_Config dist_r_config;
    dist_r_config.huart = &huart4;
    obj->dist_right = WT53D_Create(&dist_r_config);
    wt53d[3] = obj->dist_right;

    PID_config motor_lf_pid_config;
    motor_lf_pid_config.kp = 10;
    motor_lf_pid_config.ki = 0;
    motor_lf_pid_config.kd = 0;
    motor_lf_pid_config.error_sum_max = 5000;
    motor_lf_pid_config.output_max = 20000;
    Motor_config motor_lf_config;
    motor_lf_config.motor_id = 1;
    motor_lf_config.radius = 40;
    motor_lf_config.pid_config = motor_lf_pid_config;
    obj->motor_lf = Motor_Create(&motor_lf_config);
    motors[0] = obj->motor_lf;

    PID_config motor_lb_pid_config;
    motor_lb_pid_config.kp = 10;
    motor_lb_pid_config.ki = 0;
    motor_lb_pid_config.kd = 0;
    motor_lb_pid_config.error_sum_max = 5000;
    motor_lb_pid_config.output_max = 20000;
    Motor_config motor_lb_config;
    motor_lb_config.motor_id = 2;
    motor_lb_config.radius = 40;
    motor_lb_config.pid_config = motor_lb_pid_config;
    obj->motor_lb = Motor_Create(&motor_lb_config);
    motors[1] = obj->motor_lb;

    PID_config motor_rb_pid_config;
    motor_rb_pid_config.kp = 10;
    motor_rb_pid_config.ki = 0;
    motor_rb_pid_config.kd = 0;
    motor_rb_pid_config.error_sum_max = 5000;
    motor_rb_pid_config.output_max = 20000;
    Motor_config motor_rb_config;
    motor_rb_config.motor_id = 3;
    motor_rb_config.radius = 40;
    motor_rb_config.pid_config = motor_rb_pid_config;
    obj->motor_rb = Motor_Create(&motor_rb_config);
    motors[2] = obj->motor_rb;

    PID_config motor_rf_pid_config;
    motor_rf_pid_config.kp = 10;
    motor_rf_pid_config.ki = 0;
    motor_rf_pid_config.kd = 0;
    motor_rf_pid_config.error_sum_max = 5000;
    motor_rf_pid_config.output_max = 20000;
    Motor_config motor_rf_config;
    motor_rf_config.motor_id = 4;
    motor_rf_config.radius = 40;
    motor_rf_config.pid_config = motor_rf_pid_config;
    obj->motor_rf = Motor_Create(&motor_rf_config);
    motors[3] = obj->motor_rf;

    return obj;
}

void Robot_Update(Robot* obj){
    
    // /* 状态判断 */
    // if(obj->dist_forward_l->distance < DIST_EDGE || obj->dist_forward_r->distance < DIST_EDGE || obj->dist_left->distance < DIST_EDGE || obj->dist_right->distance < DIST_EDGE) {
    //     if(obj->grayscale->value < GRAY_EDGE) {
    //         if(obj->dist_forward_l->distance < DIST_AREA || obj->dist_forward_r->distance < DIST_AREA || obj->dist_left->distance < DIST_AREA || obj->dist_right->distance < DIST_AREA) {
    //             obj->position = position_fall;
    //         } else obj->position = position_edge;
    //     } else {
    //         obj->position = position_center;
    //         obj->target = target_block;
    //     }
    // } else {
    //     obj->position = position_center;
    //     obj->target = target_none;
    // }

    // if(obj->target == target_block) {
    //     //进一步判断, 前面设置为2仅表示识别到目标
    //     //判断具体识别到目标的测距
    // }

    // /* 控制指令 */
    // if(obj->position == position_center) {
    //     if(obj->target == target_robot) {
    //         //攻击
    //     } else if(obj->target == target_block) {
    //         if(/*已对准*/) {
    //             //前进
    //         } else {
    //             //转向
    //         }
    //     } else {
    //         //巡逻
    //         //进入巡逻模式下向前，直到测距小于一定距离,然后根据左右测距大小比较决定自旋方向，直到前方测距大于一定值（此方法轨迹不一定为矩形或圆形
    //     }
    // } else if(obj->position == position_edge) {
    //     //旋转,直到前方测距大于一定值
    //     //考虑目标判断在位置判断之前？
    // } else {
    //     //考虑刚掉下去的时候将某个flag置0，当准备进入后退状态时flag置1，当flag=0并且方向正确时向前冲
    //     //存在问题:车在角落时判断可能存在错误,或者不便于旋转
    //     if(obj->dist_left->distance + obj->dist_right->distance > 3800 - 300) {
    //         if(obj->dist_forward_l->distance < 100) //后退
    //         else //前进
    //     } else //旋转
    // }
}