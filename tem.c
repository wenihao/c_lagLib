/**
 * *****************************************************************************
 * @file        tem.c
 * @brief       
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
    return GetRawData();
}