#ifndef _GRAYSCALE_H
#define _GRAYSCALE_H

#include "adc.h"
#include "malloc.h"
#include "string.h"

typedef struct grayscale_config_t{
    ADC_HandleTypeDef hadc;
}Grayscale_config;

typedef struct grayscale{
    Grayscale_config config;
    uint16_t raw_data;
    float value;
}Grayscale;

#endif