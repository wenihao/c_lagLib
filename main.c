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
int main(void)
{
  int8_t a = 1;
  int8_t b = 4;
  volatile int8_t c;
  volatile int8_t d = 127;
  volatile int8_t e = -128;
  volatile uint8_t x = 0x64;
  float m_c;
  volatile uint8_t r;
  volatile uint8_t z;
  z = r;
  printf("z = %d\r\n", z);
  m_c = (float)a / b;
  printf("m_c = %f\r\n", m_c);
  float temp = 20.5f;
  float f1 = 1.123f;
  float f2 = 1.345f;
  float f3 = f1 + f2;
  if (f1 + f2 == f3)
  {
    printf("sizeof(temp) = %d\r\n", sizeof(temp));
  }
  // volatile float temp1 = 20.5;
  // temp *= 1.2f;
  // temp1 *= 1.2;
  // printf("sizeof(temp) = %d\r\n",sizeof(temp));
  // printf("sizeof(temp1) = %d\r\n",sizeof(temp1));
  //*(uint8_t*)0x20000400 = 100;
  printf("a = %d\r\n", a);
  printf("b = %d\r\n", b);
  printf("b = %d\r\n", c);
  printf("b = %d\r\n", d);
  return 0;
}
