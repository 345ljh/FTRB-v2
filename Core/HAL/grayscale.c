#include "grayscale.h"

Grayscale* Grayscale_Create(Grayscale_config* config){
    Grayscale* obj = (Grayscale*)malloc(sizeof(Grayscale));
    obj->config = *config;
    HAL_ADC_Start_IT(&obj->config.hadc);
    return obj;
}