#include "app.h"

#define DIST_EDGE 1000 //检测是否在边缘
#define DIST_AREA 700 //检测是否在台上
#define GRAY_EDGE 128 

Robot* Robot_Create(void) {
    Robot* obj = malloc(sizeof(Robot));
    memset(obj, 0, sizeof(Robot));

    //创建各种外设

    return obj;
}

void Robot_Update(Robot* obj){
    
    /* 状态判断 */
    if(obj->dist_forward_l.distance < DIST_EDGE || obj->dist_forward_r.distance < DIST_EDGE || obj->dist_left.distance < DIST_EDGE || obj->dist_right.distance < DIST_EDGE) {
        if(obj->grayscale.value < GRAY_EDGE) {
            if(obj->dist_forward_l.distance < DIST_AREA || obj->dist_forward_r.distance < DIST_AREA || obj->dist_left.distance < DIST_AREA || obj->dist_right.distance < DIST_AREA) {
                obj->position = position_fall;
            } else obj->position = position_edge;
        } else {
            obj->position = position_center;
            obj->target = target_block;
        }
    } else {
        obj->position = position_center;
        obj->target = target_none;
    }

    if(obj->target == target_block) {
        //进一步判断, 前面设置为2仅表示识别到目标
        //判断具体识别到目标的测距
    }

    /* 控制指令 */
    if(obj->position == position_center) {
        if(obj->target == target_robot) {
            //攻击
        } else if(obj->target == target_block) {
            if(/*已对准*/) {
                //前进
            } else {
                //转向
            }
        } else {
            //巡逻
            //进入巡逻模式下向前，直到测距小于一定距离,然后根据左右测距大小比较决定自旋方向，直到前方测距大于一定值（此方法轨迹不一定为矩形或圆形
        }
    } else if(obj->position == position_edge) {
        //旋转,直到前方测距大于一定值
        //考虑目标判断在位置判断之前？
    } else {
        //考虑刚掉下去的时候将某个flag置0，当准备进入后退状态时flag置1，当flag=0并且方向正确时向前冲
        //存在问题:车在角落时判断可能存在错误,或者不便于旋转
        if(obj->dist_left + obj->dist_right > 3800 - 300) {
            if(obj->dist_forward_l < 100) //后退
            else //前进
        } else //旋转
    }
}