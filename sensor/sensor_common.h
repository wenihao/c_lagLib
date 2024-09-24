/**
 * *****************************************************************************
 * @file        sensor_common.h
 * @brief       
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-18
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */

#ifndef SENSOR_COMMON_H 
#define SENSOR_COMMON_H 

#include "BaseConfig/base_config.h"
#include <stdio.h>
#include "temp_humi.h"

#define MAX(a,b) ((a > b) ? (a) : (b))
#define MIN(a,b) ((a < b) ? (a) : (b))
#define EXCH(x, y)  \
    do              \
    {               \
        UInt16 tmp; \
        tmp = (x);  \
        (x) = (y);  \
        (y) = tmp;  \
    } while (0)

typedef enum
{
    Excellent,
    Good,
    Average,
    Poor,
    Max
}QualityLevel;

enum Colour
{
    RED,
    YELLOW,
    GREEN,
    BLUE,
    ORANGE,
    WHITE
};

enum Month
{
    JAN = 1,
    FEB,
    MAR,
    APR,
    MAY,
    JUN,
    JUL,
    AUG,
    SEP,
    OCT,
    NOV,
    DEC,
    max
};

typedef struct
{
    char name[12];
    UInt8 id;
    char sex[10];
    UInt8 age;
    float score;
} Studentinfo;

typedef struct
{
    TempHumiSensor tempHumiData[TEMP_SENSOR_NUM];
    QualityLevel co2Level;
    QualityLevel pm25Level;
}AirQuality;
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

#endif	/* SENSOR_COMMON_H */
