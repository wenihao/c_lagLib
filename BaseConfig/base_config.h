/**
 * *****************************************************************************
 * @file        base_config.h
 * @brief       
 * @author      wenbo.zhang (1992552138@qq.com)
 * @date        2024-09-18
 * @copyright   xxxx技有限公司
 * *****************************************************************************
 */

/*----------------------------------include-----------------------------------*/

/*-----------------------------------macro------------------------------------*/

/*----------------------------------typedef-----------------------------------*/

/*----------------------------------variable----------------------------------*/

/*-------------------------------------os-------------------------------------*/

/*----------------------------------function----------------------------------*/

/*------------------------------------test------------------------------------*/

#ifndef _BASE_CONFIG_H_
#define _BASE_CONFIG_H_


#define EXTERN extern
#define DG_STATIC static
#ifndef VISIBILITY
#define VISIBILITY static
#endif
#ifndef SW_OFF
#define SW_OFF (0)  // 2
#endif

#ifndef SW_ON
#define SW_ON (1)  // 1
#endif

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef NULL
#define NULL (0)
#endif

#ifndef NULL_PTR
#define NULL_PTR ((void *)0)
#endif

#define _1_ (1)
#define _0_ (0)

// Maximum and Minimum values for all supported data types
#ifndef gd_MAX_ui8
//! Maximum for unsigned 8 Bit value (UInt8)
#define gd_MAX_ui8 ((UInt8)0xFF)
#endif
#ifndef gd_MIN_ui8
//! Minimum for unsigned 8 Bit value (UInt8)
#define gd_MIN_ui8 ((UInt8)0x00)
#endif
#ifndef gd_MAX_ui16
//! Maximum for unsigned 16 Bit value (UInt16)
#define gd_MAX_ui16 ((UInt16)0xFFFF)
#endif
#ifndef gd_MIN_ui16
//! Minimum for unsigned 16 Bit value (UInt16)
#define gd_MIN_ui16 ((UInt16)0x0000)
#endif
#ifndef gd_MAX_ui32
//! Maximum for unsigned 32 Bit value (UInt32)
#define gd_MAX_ui32 ((UInt32)0xFFFFFFFF)
#endif
#ifndef gd_MIN_ui32
//! Minimum for unsigned 32 Bit value (UInt32)
#define gd_MIN_ui32 ((UInt32)0x00000000)
#endif

#ifndef gd_MAX_si8
//! Maximum for signed 8 Bit value (SInt8)
#define gd_MAX_si8 ((SInt8)127)
#endif
#ifndef gd_MIN_si8
//! Minimum for signed 8 Bit value (SInt8)
#define gd_MIN_si8 ((SInt8)-128)
#endif
#ifndef gd_MAX_si16
//! Maximum for signed 16 Bit value (SInt16)
#define gd_MAX_si16 ((SInt16)32767)
#endif
#ifndef gd_MIN_si16
//! Minimum for signed 16 Bit value (SInt16)
#define gd_MIN_si16 ((SInt16)-32768)
#endif
#ifndef gd_MAX_si32
//! Maximum for signed 32 Bit value (SInt32)
#define gd_MAX_si32 ((SInt32)2147483647)
#endif
#ifndef gd_MIN_si32
//! Minimum for signed 32 Bit value (SInt32)
#define gd_MIN_si32 (-gd_MAX_si32 - 1)
#endif

#define INL_OPT
/*--------------------------------------------------------------------------*/
/*- Type  define                                                           -*/
/*--------------------------------------------------------------------------*/
typedef signed char SInt8;      //        -128 .. +127         ARREF:PLATFORM016
typedef unsigned char UInt8;    //           0 .. 255          ARREF:PLATFORM013
typedef signed short SInt16;    //      -32768 .. +32767       ARREF:PLATFORM017
typedef unsigned short UInt16;  //           0 .. 65535        ARREF:PLATFORM014
typedef signed int SInt32;      // -2147483648 .. +2147483647  ARREF:PLATFORM018
typedef unsigned int UInt32;    //           0 .. 4294967295   ARREF:PLATFORM015
typedef unsigned long long UInt64;
typedef signed long long SInt64;
typedef unsigned char Boolean;
typedef unsigned int Bitfield;
typedef unsigned char
    Bitfield8;  // supported by GHS compiler (build_v800.pdf page 499)
typedef unsigned short
    Bitfield16;  // supported by GHS compiler (build_v800.pdf page 499)
typedef unsigned int
    Bitfield32;  // supported by GHS compiler (build_v800.pdf page 499)

#endif /* _BASE_CONFIG_H_ */
/* END OF FILE */
