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

#include "base_config.h"
#include <stdio.h>
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
