#ifndef _DIST_H
#define _DIST_H

#include "adc.h"
#include "malloc.h"

typedef struct dist_sensor_config_t {
    ADC_HandleTypeDef* adc_base;
}Dist_sensor_config;


typedef struct dist_sensor_t {
    Dist_sensor_config config;
    float distance;
}Dist_sensor;

#endif