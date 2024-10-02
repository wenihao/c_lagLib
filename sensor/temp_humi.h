/**
 * *****************************************************************************
 * @file        tem.h
 * @brief       
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-17
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */
#include "sensor_common.h"
#ifndef TEM_HUMI_H 
#define TEM_HUMI_H 

#define CEL_MIN_VALUE (5.0f)
#define CEL_MAX_VALUE (55.0f)
#define CEL_TO_FAH(t) ((t)* 1.8f +32)

#define TEMP_SENSOR_NUM 3
#define TEMP_DATA_NUM 5

typedef struct
{
    UInt16 id;
    float temp;
    UInt8 humi;
}TempHumiSensor;

static float CalRawAvg(float data[],UInt32 len);
static float GetRawData(UInt32 sensorId);
float GetcelTem(UInt32 sensorId);
float GetFahrenheit(UInt32 sensorId);
float GetHmiDataTem(void);
void SetTemCof(float temCof);
UInt8 GetHumiData(UInt32 sensorId);
SInt8 GetTempHumi(TempHumiSensor *tempHumPtr);
#ifdef __cplusplus
extern "C"{
#endif

/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif	/* TEM_H */
