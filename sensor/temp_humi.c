/**
 * *****************************************************************************
 * @file        tem.c
 * @brief       获取原始温度数据
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-17
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */

#include "temp_humi.h"

static float g_temCof = 1;
void SetTemCof(float temCof)
{
    g_temCof = temCof;
}

/**
 * @brief       求平均值
 * 
 * @param       data 
 * @param       len 
 * @return      float 
 */
static float CalRawAvg(float data[],UInt32 len)
{
    float l_res = 0;
    for(UInt8 i = 0 ; i < len; i++)
    {
        l_res += data[i];
    }
    return l_res / len;
}

/**
 * @brief       Get the Raw Tem object
 * 
 * @return      float 
 */
static float GetRawData(UInt32 sensorId)
{
    static UInt8 l_chgVal_ui8 = 0; // 静态变量只会进行1次初始化
    l_chgVal_ui8++;
    l_chgVal_ui8 = (l_chgVal_ui8 % 5); // 限制l_chgVal_ui8的范围为0-4
    return 20.0f + l_chgVal_ui8; // 20.0 ~ 24.0
}

/**
 * @brief       Get the cel Tem object
 * 
 * @return      float 
 */
float GetcelTem(UInt32 sensorId)
{
    #if 1
    float l_cel_flt;
    float l_num_flt[5] = {0};

    for(UInt8 i = 0; i < 5; i++)
    {
        l_num_flt[i] = GetRawData(sensorId);

    }
    l_cel_flt = CalRawAvg(l_num_flt,5);
    if(l_cel_flt < CEL_MIN_VALUE)
    {
        l_cel_flt = CEL_MIN_VALUE;
    }
    if(l_cel_flt > CEL_MAX_VALUE)
    {
        l_cel_flt = CEL_MAX_VALUE;
    }
    return l_cel_flt;
    #else
    volatile float l_cel_flt;
    l_cel_flt = GetRawData(sensorId);
    return l_cel_flt;
    #endif
}

/**
 * @brief       Get the Fahrenheit object
 * 
 * @return      float 
 */
float GetFahrenheit(UInt32 sensorId)
{
    float l_degree_flt;
    float l_fahrenheit_flt;
    l_degree_flt = GetcelTem(sensorId);
    l_fahrenheit_flt = CEL_TO_FAH(l_degree_flt); // ((t)* 1.8f +32)
    return l_fahrenheit_flt;
}

/**
 * @brief       Get the Humi Data object
 * 
 * @param       sensorId 
 * @return      UInt8 
 */
UInt8 GetHumiData(UInt32 sensorId)
{
    return 40;
}

/**
 * @brief       Get the Temp Humi object
 * 
 * @param       sensorId 
 * @param[out]  temp 
 * @param[out]  humi 
 * @return      Boolean 0：成功，-1：失败
 */
SInt8 GetTempHumi(TempHumiSensor *tempHumPtr)
{
    if (tempHumPtr != NULL)
    {
        //tempHumPtr->id = 0x1234;
        tempHumPtr->temp = GetcelTem(tempHumPtr->id);
        tempHumPtr->humi = GetHumiData(tempHumPtr->id);
        return 0;
    }
    else
    {
        return -1;
    }
}
