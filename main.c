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
// #define APB2_BUS_BASE ((uint32_t)0x40010000U)  
// #define GPIO_BASE (APB2_BUS_BASE + 0x0000800U)  
// #define GPIOG (GPIO_BASE + 0x00001800U)  
// #define GPIO_CTLO(gpiox) (*(volatile uint32_t *)((uint32_t)(gpiox)+0x00U))  
// #define REG32(addr) ((volatile uint32_t *)(uint32_t)(addr)) 

#define WORK_BOOK 0
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

/**
 * @brief      计算两个整数相加
 *
 * @param       x
 * @param       y
 * @return      int
 */
int add(int x, int y)
{
  return x + y;
}

/**
 * @brief       计算两个整数相减
 *
 * @param       x
 * @param       y
 * @return      int
 */
int sub(int x, int y)
{
  return x - y;
}

uint32_t m_dateData_ui32 = 0x14180616;
uint32_t m_data_cunfang0_ui32;
uint32_t m_data_cunfang1_ui32;
uint32_t m_data_cunfang2_ui32;
uint8_t m_dayData_ui8;
uint8_t m_monthData_ui8;
uint8_t m_yearDataLow_ui8;
uint8_t m_yearDataHigh_ui8;
char mybuff[100];
uint16_t year = 2024;
uint8_t day;

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

void data_prea(char *s)
{
    if(strlen(s) == 0)
    {
        return;
    }
    for(uint8_t i = 0; i < strlen(s) - 1 ;i++)
    {
        if(s[i] == 'z')
        {
            s[i] = 'Z';
        }
    }
}

int m_kaobei(char *buf,int8_t len)
{
    if(len > 100)
    {
        return -1;
    }
    memcpy(mybuff,buf,len);
}
uint16_t m_sumNum(volatile uint16_t start,volatile uint16_t end);
uint16_t m_sumNum(volatile uint16_t start,volatile uint16_t end)
{
    uint16_t l_sum_ui16 = 0;
    for(uint16_t i = start; i <= end; i++)
    {
        l_sum_ui16 += i;
    }
    return l_sum_ui16;
}

bool islower(char c)
{
    if(c >= 'a' && c <= 'z')
    {
        printf("c = %c\r\n",c);
        return true;
    }
    printf("%c is not lower",c);
    return false;
}
#define MAX_BUFF (50u)
float foot[20] = {0}; // 脚长
int main(void)
{
    uint16_t l_sum1_ui16 = 0;
    uint16_t l_sum2_ui16 = 0;
    uint16_t l_sum3_ui16 = 0;
    volatile uint16_t l_a = 201;
    volatile uint16_t l_b = 300;

#if WORK_BOOK
    // 第五章，多个鞋码对应的脚长,
    const float SCALE  = 0.3333f;
    const float ADJUST = 7.31f;
    uint8_t shoe       = 0; // 鞋码
    while (shoe < 20)
    {
        foot[shoe] = shoe * SCALE + ADJUST; // 不同的鞋码输出20只脚
        shoe++;
    }
#else
    bool t                = -2;
    bool f                = 3;
    bool ds               = 0;
    uint8_t s             = sizeof(ds);
    uint8_t zwb           = 10;
    uint8_t ln            = 9;
    char input[]          = "";
    char buffer[MAX_BUFF] = {0x00};
    for (uint8_t i = 0; i < MAX_BUFF; i++)
    {
        buffer[i] = i;
    }
    printf("start = %s", input);
    data_prea(input);
    printf("end = %s", input);
    m_kaobei(buffer, sizeof(buffer));
    m_dayData_ui8      = m_dateData_ui32; // 16
    m_dateData_ui32    = m_dateData_ui32 >> 8;
    m_monthData_ui8    = m_dateData_ui32; // 141806 // 06
    m_dateData_ui32    = m_dateData_ui32 >> 8;
    m_yearDataLow_ui8  = m_dateData_ui32; // 1418 // 18
    m_dateData_ui32    = m_dateData_ui32 >> 8;
    m_yearDataHigh_ui8 = m_dateData_ui32; // 14
    volatile uint8_t a = 20;
    volatile int8_t b  = 127;
    b++;
    a = 255;
    a++;
    a |= 1 << 2;
    // volatile int8_t b = -20;
    volatile int8_t q   = a + b;
    volatile float c    = 5.5f;
    volatile char d     = 'z';
    volatile char e[]   = "abcdefghijklmnopqrstuvwxyz";
    volatile char zw    = 20;
    volatile char g     = 20;
    volatile uint32_t h = a;
    volatile uint8_t i  = 0;
    i--;
    volatile uint8_t l_digit_ui8     = 0;
    volatile uint8_t l_dec10_ui8[16] = {0};
    volatile uint8_t l_digit1_ui8    = 10;
    volatile uint8_t l_c_ui8         = 0;
    l_c_ui8 = l_digit1_ui8 < 10 ? l_digit1_ui8 + 48 : l_digit1_ui8 + 97 - 10;
    if (l_digit_ui8 < 10)
    {
        for (l_digit_ui8 = 0; l_digit_ui8 < 10; l_digit_ui8++)
        {
            l_dec10_ui8[l_digit_ui8] = l_digit_ui8 + 48;
        }
    }
    if (l_digit_ui8 > 9 && l_digit_ui8 < 16)
    {
        for (l_digit_ui8 = 10; l_digit_ui8 < 16; l_digit_ui8++)
        {
            l_dec10_ui8[l_digit_ui8] = l_digit_ui8 + 97 - 10;
        }
    }
    printf(
        "m_dayData_ui8 = %d,m_monthData_ui8 = %d,m_yearDataLow_ui8 = %d, "
        "m_yearDataHigh_ui8 = %d\r\n",
        m_dayData_ui8, m_monthData_ui8, m_yearDataLow_ui8, m_yearDataHigh_ui8);
    printf("a = %u,b = %d, c = %.0f, d = %c, e = %s, f = %#x, &g = %p\r\n", a, b, c, d, e,
           f, &g);
    printf("123");
    int8_t x = 0x7f;
    int8_t y = 0x05;
    int8_t r = x * y;
    if (0x7f == x)
    {
        x++;
    }
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
    {
        day = 29;
    }
    else
    {
        day = 28;
    }
    if (10 != zwb && ln++ == 10)
    {
        zwb++;
    }
    printf("ln = %d\r\n", ln);
    if (10 != zwb || ++ln == 10)
    {
        zwb++;
    }
    printf("ln = %d\r\n", ln);
#endif
#if 0
    char l_gradeNum_ui8 = 'C';
   switch (l_gradeNum_ui8)
   {
       case 'A':
           printf("Excellent\r\n");
           break;
       case 'B':
           printf("good\r\n");
           break;
       case 'C':
           printf("Fail\r\n");
           break;
       case 'D':
           printf("Poor\r\n");
           break;
       default:
           printf("Invalid value\r\n");
           break;
   }
    if('A' == l_gradeNum_ui8)
    {
        printf("Excellent\r\n");
    }
    else if('B' == l_gradeNum_ui8)
    {
        printf("good\r\n");
    }
    else if('C' == l_gradeNum_ui8)
    {
        printf("Fail\r\n");
    }
    else if('D' == l_gradeNum_ui8)
    {
        printf("Poor\r\n");
    }
    else
    {
        printf("Invalid value\r\n");
    }
#endif
    uint16_t l_year_ui16 = 2024;
    enum Month l_month_ui8  = JAN;
    uint8_t l_day_ui8    = 0;
    printf("l_year_ui16 = %d && l_month_ui8 = %d\r\n", l_year_ui16, l_month_ui8);
    switch (l_month_ui8)
    {
        case FEB:
            if ((l_year_ui16 % 4 == 0 && l_year_ui16 % 100 != 0) ||
                (l_year_ui16 % 400 == 0))
            {
                l_day_ui8 = 29;
            }
            else
            {
                l_day_ui8 = 28;
            }
            printf("l_day_ui8 = %d\r\n", l_day_ui8);
            break;
        case JAN:
        case MAR:
        case MAY:
        case JUL:
        case AUG:
        case OCT:
        case DEC:
            l_day_ui8 = 31;
            printf("l_day_ui8 = %d\r\n", l_day_ui8);
            break;
        case APR:
        case JUN:
        case SEP:
        case NOV:
            l_day_ui8 = 30;
            printf("l_day_ui8 = %d\r\n", l_day_ui8);
            break;
        default:
            printf("Invalid month\r\n");
            break;
    }
    enum Colour col = BLUE;
    // for (uint8_t j = 1; j < 6; j++)
    // {
    //     // printf("j = %d",j);
    //     printf("*");
    // }
    printf("\n");
    uint16_t l_sum_ui16 = 0;
    uint16_t l_num_ui16 = 1;
    // l_sum_ui16 = (l_num_ui16 * (l_num_ui16 + 1)) / 2;
    // printf("l_sum_ui16 = %d\r\n",l_sum_ui16);
    // for (l_num_ui16 = 1; l_num_ui16 <= 100; l_num_ui16++)
    // {
    //     l_sum_ui16 += l_num_ui16;
    // }
    // while (l_num_ui16 <= 100)
    // {
    //     l_sum_ui16 += l_num_ui16;
    //     l_num_ui16++;
    // }
    do
    {
        l_sum_ui16 += l_num_ui16;
        l_num_ui16++;
    } while (l_num_ui16 <= 100);

    printf("l_sum_ui16 = %d\r\n", l_sum_ui16);
    for (uint8_t i = 0; i < 4; i++) // 行数
    {
        for (uint8_t j = 0; j < i + 1; j++) // 列数
        {
            printf("*");
        }
        printf("\r\n");
    }
    for (uint8_t i = 4; i > 0; i--) // 行数
    {
        for (uint8_t j = i; j > 0; j--) // 列数
        {
            printf("*");
        }
        printf("\r\n");
    }
    for (uint8_t i = 1; i < 10; i++)
    {
        if (i % 3 == 0)
        {
            break;
        }
        printf("1-2:%d\r\n", i);
    }
    printf("Main end\r\n");
    uint8_t l_i = 0; // 行数
    uint8_t l_j = 0; // 列数 //打印4行5列*
    while (1)
    {
        if(l_i >= 4)
        {
            break;
        }
        while(1)
        {
            if(l_j >= 5)
            {
                break;
            }
            printf("*");
            l_j++;
        }
        l_j = 0;
        printf("\r\n");
        l_i++;
    }
    for(uint8_t i = 1; i < 10; i++)
    {
        if(i % 3 == 0)
        {
            continue;
        }
        printf("i = %d\r\n",i);
    }
    // for(uint8_t i = 1; i <= 100; i++)
    // {
    //     l_sum1_ui16 += i;
    // }
    // printf("l_sum1_ui16 = %d\n",l_sum1_ui16);
    // for(uint16_t i = 201; i <= 300; i++)
    // {
    //     l_sum2_ui16 += i;
    // }
    // printf("l_sum2_ui16 = %d\n",l_sum2_ui16);
    // for(uint16_t i = 401; i <= 500; i++)
    // {
    //     l_sum3_ui16 += i;
    // }
    // printf("l_sum3_ui16 = %d\n",l_sum3_ui16);
    
    l_sum1_ui16 = m_sumNum(l_a,l_b);
    l_sum2_ui16 = m_sumNum(201,300);
    l_sum3_ui16 = m_sumNum(401,500);
    printf("l_sum1_ui16 = %d\n",l_sum1_ui16);
    
    islower('b');
    islower('1');
    float l_celTem_flt;
    uint32_t l_celTem1_flt = 0;
    l_celTem_flt = GetcelTem();
    printf("l_celTem1_flt is %d cel degrees.\n", l_celTem1_flt);
    printf("l_celTem_flt is %.1f cel degrees.\n", l_celTem_flt);
    return 0;
}

