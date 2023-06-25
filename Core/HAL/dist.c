#include "dist.h"

//ADC测距

Dist_sensor* Dist_sensor_Create(Dist_sensor_config* config)
{
    Dist_sensor* obj = (Dist_sensor*)malloc(sizeof(Dist_sensor));
    HAL_ADC_Start(config->adc_base);
    return obj;
}

void Dist_sensor_Update(Dist_sensor* obj)
{
    obj->distance = 23596.0 / (HAL_ADC_GetValue(obj->config.adc_base) - 147.33);
    HAL_ADC_Start(obj->config.adc_base);
}