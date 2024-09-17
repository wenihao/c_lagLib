/**
 * *****************************************************************************
 * @file        tem.c
 * @brief       获取原始温度数据
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-17
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */

#include "tem.h"
/**
 * @brief       Get the Raw Tem object
 * 
 * @return      float 
 */
static float GetRawData(void)
{
    return 25.5f;
}

/**
 * @brief       Get the cel Tem object
 * 
 * @return      float 
 */
float GetcelTem(void)
{
    float l_cel_flt;
    l_cel_flt = GetRawData();
    if(l_cel_flt < CEL_MIN_VALUE)
    {
        l_cel_flt = CEL_MIN_VALUE;
    }
    if(l_cel_flt > CEL_MAX_VALUE)
    {
        l_cel_flt = CEL_MAX_VALUE;
    }
    return l_cel_flt;
}

/**
 * @brief       Get the Fahrenheit object
 * 
 * @return      float 
 */
float GetFahrenheit(void)
{
    float l_degree_flt;
    float l_fahrenheit_flt;
    l_degree_flt = GetcelTem();
    l_fahrenheit_flt = CEL_TO_FAH(l_degree_flt); // ((t)* 1.8f +32)
    return l_fahrenheit_flt;
}
