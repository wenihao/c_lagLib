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
#include "tem.h"
#include "co2.h"
#include "pm25.h"
#include "sensor_common.h"

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

int main(void)
{
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
    float l_celTem1_flt = 0;
    QualityLevel l_qualityLevel_eum;
    QualityLevel l_GetPm25Level1_eum;
    l_celTem_flt = GetcelTem();
    l_celTem1_flt = GetFahrenheit();
    l_qualityLevel_eum = GetCo2Level1();
    l_GetPm25Level1_eum = GetPm25Level();
    DisplayPm25Level(l_GetPm25Level1_eum);
    DisplayCo2Level(l_qualityLevel_eum);
    printf("Current CO2 Quality Level: %d\n", l_qualityLevel_eum);
    printf("l_celTem1_flt is %.1f cel degrees.\n", l_celTem1_flt);
    printf("l_celTem_flt is %.1f cel degrees.\n", l_celTem_flt);
#endif
    return 0;
}

