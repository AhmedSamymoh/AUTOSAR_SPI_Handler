/***********************************************************************************************
 * @file           : Platform_Types.h
 * @brief          : Platform Types header file.
 * @version        : 1.0.0
 * @module         : Platform Types
 * @platform       : stm32f446re
 * @autosar_version: R23-11
 * @sw_version     : 1.0.0
 * @created on     : Aug 20, 2024
 * @author         : AhmedSamy
 ***********************************************************************************************/

#ifndef PLATFORM_TYPES_H /* File guard */
#define PLATFORM_TYPES_H



/************************************ Section : Includes ************************************/



/************************************ Section: Macro Declarations ************************************/

/*
[SWS_Platform_00064] 
According to the register width of the CPU used,
CPU_TYPE shall be assigned to one of the symbols: 
CPU_TYPE_8, CPU_TYPE_16, CPU_TYPE_32 or CPU_TYPE_64
*/
/******************/
#define CPU_TYPE            CPU_TYPE_32
/******************/
#define CPU_TYPE_8          8
#define CPU_TYPE_16         16
#define CPU_TYPE_32         32
#define CPU_TYPE_64         64


/*
[SWS_Platform_00038] 
 CPU_BIT_ORDER
*/
/******************/
#define CPU_BIT_ORDER        LSB_FIRST
/******************/
#define MSB_FIRST            0
#define LSB_FIRST            1

/*
[SWS_Platform_00039]
 CPU_BYTE_ORDER : The byte order of the CPU
 Within uint16:
 - the low byte is located before the high byte  HIGH_BYTE_FIRST
 - the high byte is located after the low byte   LOW_BYTE_FIRST
*/ 
/******************/
#define CPU_BYTE_ORDER       LSB_FIRST
/******************/
#define HIGH_BYTE_FIRST            0
#define LOW_BYTE_FIRST            1

/************************************ Section: Data Type Declarations ************************************/


/*
[SWS_Platform_00039]
 Type definitions
*/ 
typedef unsigned char       boolean;

typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned long       uint32;
typedef unsigned long long  uint64;
typedef unsigned short      uint8_least;
typedef unsigned short      uint16_least;
typedef unsigned long       uint32_least;

typedef signed char         sint8;
typedef signed short        sint16;
typedef signed long         sint32;
typedef signed long long    sint64;
typedef signed short        sint8_least;
typedef signed short        sint16_least;
typedef signed long         sint32_least;
typedef float               float32;
typedef double              float64;



/************************************ Section : Macro Functions Declarations ************************************/




#endif /* PLATFORM_TYPES_H */