/**
 * *****************************************************************************
 * @file        main.c
 * @brief
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-01-23
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */
#include <stdio.h>
#include "ARMCM4.h"
#include "stdint.h"
#include <string.h>
#include <stdbool.h>
#include "sensor/temp_humi.h"
#include "sensor/co2.h"
#include "sensor/pm25.h"
#include "sensor/sensor_common.h"

#define WORK_BOOK 0
#if 1
// #define APB2_BUS_BASE ((UInt32)0x40010000U)  
// #define GPIO_BASE (APB2_BUS_BASE + 0x0000800U)  
// #define GPIOG (GPIO_BASE + 0x00001800U)  
// #define GPIO_CTLO(gpiox) (*(volatile UInt32 *)((UInt32)(gpiox)+0x00U))  
// #define REG32(addr) ((volatile UInt32 *)(UInt32)(addr)) 
struct __FILE
{
  int handle; /* Add whatever needed */
};
FILE __stdout;
FILE __stdin;

int fputc(int ch, FILE *f)
{
  return ITM_SendChar(ch);
}

volatile int32_t ITM_RxBuffer = ITM_RXBUFFER_EMPTY;
int fgetc(FILE *f)
{
  while (ITM_CheckChar() != 1)
    __NOP();
  return (ITM_ReceiveChar());
}
int ferror(FILE *f)
{
  /* Your implementation of ferror */
  return EOF;
}

void _ttywrch(int ch)
{
  fputc(ch, &__stdout);
}

// int __backspace()
//{
//	return 0;
// }
void _sys_exit(int return_code)
{
  while (1)
    ; /* endless loop */
}
#endif

float g_temCof_flt;
float GetTemCofHmi(void)
{
  return 1.2f;
}

float GetHmiDataTem(void)
{
  return g_temCof_flt;
}

void DisPlayAirQuality(AirQuality airQuaLity)
{
    for(UInt8 i = 0 ; i < TEMP_SENSOR_NUM; i++)
    {
        airQuaLity.tempHumiData[i].temp = GetcelTem(airQuaLity.tempHumiData[i].id);
        airQuaLity.tempHumiData[i].humi = GetHumiData(airQuaLity.tempHumiData[i].id);
    }
    DisplayPm25Level(airQuaLity.pm25Level);
    DisplayCo2Level(airQuaLity.co2Level);
}

typedef __packed struct
{
    uint8_t id;
    uint8_t humi;
    float temp;
} TempHumiSensor1;

int main(void)
{
    volatile Boolean l_flag = TRUE;
    volatile UInt32 l_c = 0XF0F0F0F0;
    volatile UInt32 *l_b = NULL;
    l_b = &l_c;
    //printf("sizeof(l_b) = %d,sizeof(l_c) = %d\r\n",sizeof(l_b),sizeof(l_c));
    //volatile UInt32 l_d = 0xf0f0f0f0;
#if WORK_BOOK
    // 第五章，多个鞋码对应的脚长,
    const float SCALE  = 0.3333f;
    const float ADJUST = 7.31f;
    UInt8 shoe       = 0; // 鞋码
    while (shoe < 20)
    {
        foot[shoe] = shoe * SCALE + ADJUST; // 不同的鞋码输出20只脚
        shoe++;
    }
#else
    float l_celTem_flt;
    float l_celTem1_flt = 0.0f;
    UInt16 x = 9, y = 10;
    UInt8 l_byte_ui8 = 0;
    l_byte_ui8 = sizeof(TempHumiSensor1);
    volatile Studentinfo stuInfo;
    volatile QualityLevel l_qualityLevel_eum;
    volatile QualityLevel l_GetPm25Level1_eum;
    AirQuality airQuaLity;
    airQuaLity.tempHumiData[0].id = 0x1234;
    airQuaLity.tempHumiData[1].id = 0x2345;
    airQuaLity.tempHumiData[2].id = 0x3456;
    if(x < y)
    {
      EXCH(x,y);
      printf("x = %d,y = %d\r\n",x,y);
    }
    else
    {
      printf("x is not smaller than y.\r\n");
    }
    //g_temCof_flt = GetTemCofHmi();
    UInt8 l_sensorId = 3;
    SetTemCof(GetTemCofHmi());
    l_celTem_flt = GetcelTem(l_sensorId);
    l_celTem1_flt = GetFahrenheit(l_sensorId);
    airQuaLity.co2Level = GetCo2Level1();
    airQuaLity.pm25Level = GetPm25Level();
    DisPlayAirQuality(airQuaLity);
    printf("Current CO2 Quality Level: %d\n", airQuaLity.co2Level);
    printf("Current PM25 Quality Level: %d\n", airQuaLity.pm25Level);
    printf("l_celTem1_flt is %.1f cel degrees.\n", l_celTem1_flt);
    printf("l_celTem_flt is %.1f cel degrees.\n", l_celTem_flt);
    UInt32 tmp[5] = {1,2,3,4,5};
    printf("&tmp = %p,sizeof(tmp) = %d\n",tmp,sizeof(tmp));
    for (uint8_t i = 0; i < 5; i++)
    {
        printf("&tmp[%d] = %p,sizeof(tmp) = %d\n",i,&tmp[i],sizeof(tmp));
    }
    volatile UInt8 l_buff[] = {2,5,1,3,4,7};
    volatile UInt8 l_n_ui8 = 0;
    l_n_ui8 = sizeof(l_buff) / 2;
    for(UInt32 i = 0 ; i < 6;i++)
    {
        l_n_ui8 +=l_buff[i];
    }

    volatile int32_t sum;
    volatile uint8_t l_x = 100, l_y = 200;
    volatile int32_t nums[4];
    for (uint8_t i = 0; i < 4; i++) 
    {
      nums[i] = i;
    }
    sum = l_x + l_y;
    printf("sum = %d.\n", sum);

    
#endif
    return 0;
}

