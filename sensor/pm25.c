/**
 * *****************************************************************************
 * @file        pm2.5.c
 * @brief       
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-17
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */

/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#include "pm25.h"

/**
 * @brief       Get the Raw Data Pm 2 5 object
 * 
 * @return      UInt16 
 */
static UInt16 GetRawDataPm25(void)
{
    return 20;
}

/**
 * @brief       Get the Pm 2.5 Level 1 object
 * 
 * @return      QualityLevel 
 */
QualityLevel GetPm25Level(void)
{
    volatile UInt16 l_raw_ui16;
    volatile QualityLevel level_ui16;
    l_raw_ui16 = GetRawDataPm25();
    // level_ui16 = l_raw_ui16 / 10;
    if(l_raw_ui16 < PM25_EXCELLENT)
    {
        level_ui16 = Excellent;
    }
    else if(l_raw_ui16 >= PM25_EXCELLENT && l_raw_ui16 < PM25_GOOD)
    {
        level_ui16 = Good;
    }
    else if(l_raw_ui16 >= PM25_GOOD && l_raw_ui16 < PM25_AVERAGE)
    {
        level_ui16 = Good;
    }
    else
    {
        level_ui16 = Poor;
    }
    return level_ui16;
}

/**
 * @brief       
 * 
 * @param       lv 
 */
void DisplayPm25Level(QualityLevel lv) 
{
    switch (lv)
    {
        case Excellent:
            printf("The air quality of pm2.5 is excellent.\r\n");
            break;
        case Good:
            printf("The air quality of pm2.5 is Good.\r\n");
            break;
        case Average:
            printf("The air quality of pm2.5 is Average.\r\n");
            break;
        default:
            printf("The air quality of pm2.5 is Poor.\r\n");
            break;
    }
}

/**
 * @brief       Get the Pm 2.5 Class object
 * 
 * @return      QualityLevel 
 */
QualityLevel GetPm25Class(void)
{
    QualityLevel l_vel;
    UInt16 l_GetRawDataPm25_ui32;
    l_GetRawDataPm25_ui32 = GetRawDataPm25();
    if(l_GetRawDataPm25_ui32 < PM25_EXCELLENT)
    {
        l_vel = Excellent;
    }
    else if(l_GetRawDataPm25_ui32 >= PM25_EXCELLENT && l_GetRawDataPm25_ui32 < PM25_GOOD)
    {
        l_vel = Good;
    }
    else if(l_GetRawDataPm25_ui32 >= PM25_GOOD && l_GetRawDataPm25_ui32 < PM25_AVERAGE)
    {
        l_vel = Average;
    }
    else
    {
        l_vel = Poor;
    }
    return l_vel;
}
