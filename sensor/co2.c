/**
 * *****************************************************************************
 * @file        co2.c
 * @brief       
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-17
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */

#include "co2.h"
/**
 * @brief       Get the Raw Tem object
 * 
 * @return      int32_t 
 */
static UInt16 GetRawDataCo2(void)
{
    return 500;
}


/**
 * @brief       Get the Co 2 Level 1 object
 * 
 * @return      UInt16 
 */
QualityLevel GetCo2Level1(void)
{
    volatile UInt16 l_raw_ui16;
    volatile UInt16 level_ui16;
    l_raw_ui16 = GetRawDataCo2();
    level_ui16 = l_raw_ui16 / 100;
    return (QualityLevel)level_ui16;
}

/**
 * @brief       
 * 
 * @param       lv 
 */
void DisplayCo2Level(QualityLevel lv) 
{
    switch (lv)
    {
        case Excellent:
            printf("The air quality of co2 is excellent.\r\n");
            break;
        case Good:
            printf("The air quality of co2 is Good.\r\n");
            break;
        case Average:
            printf("The air quality of co2 is Average.\r\n");
            break;
        default:
            printf("The air quality of co2 is Poor.\r\n");
            break;
    }
}
/**
 * @brief       Get the Co 2 Class object
 * 
 * @return      QualityLevel 
 */
QualityLevel GetCo2Level(void)
{
    QualityLevel l_vel;
    UInt16 l_GetRawDataCo2_ui32;
    l_GetRawDataCo2_ui32 = GetRawDataCo2();
    if(l_GetRawDataCo2_ui32 < CO2_EXCELLENT)
    {
        l_vel = Excellent;
    }
    else if(l_GetRawDataCo2_ui32 >= CO2_EXCELLENT && l_GetRawDataCo2_ui32 < CO2_GOOD)
    {
        l_vel = Good;
    }
    else if(l_GetRawDataCo2_ui32 >= CO2_GOOD && l_GetRawDataCo2_ui32 < CO2_AVERAGE)
    {
        l_vel = Average;
    }
    else
    {
        l_vel = Poor;
    }
    printf("CO2 Level: %d\n", l_vel);
    return l_vel;
}
