/***********************************************************************************************
 * @file           : STD_TYPES.h
 * @brief          : Standard Types header file.
 * @version        : 1.0.0
 * @module         : Standard Types
 * @platform       : stm32f446re
 * @autosar_version: R23-11
 * @sw_version     : 1.0.0
 * @created on     : Aug 20, 2024
 * @author         : AhmedSamy
 ***********************************************************************************************/

#ifndef STD_TYPES_H /* File guard */
#define STD_TYPES_H


/************************************ Section : Includes ************************************/

#include "Platform_Types.h"
#include "hw_reg.h"

/************************************ Section: Data Type Declarations ************************************/

/*
* (SRS_BSW_00004)
* Std_VersionInfoType :
* All Basic SW Modules shall perform a pre-processor 
* check of the versions of all imported include files
*/
typedef struct {
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;

/*Questions*/
#define vendorID            0xBCBCu    
#define moduleID            0x01u
#define sw_major_version    23u
#define sw_minor_version    11u 
#define sw_patch_version    

/*
* Std_ReturnType
* [SWS_Std_00005]
*/
typedef uint8               Std_ReturnType;

/************************************ Section: Macro Declarations ************************************/

/*
* [SWS_Std_00007] 
*/
#define STD_HIGH            0x01u /* Physical state 5V or 3.3V */
#define STD_LOW             0x00u /* Physical state 0V */

/*
* [SWS_Std_00013]
*/
#define STD_ACTIVE          0x01u /* Logical state active */
#define STD_IDLE            0x00u /* Logical state idle */

/*
* [SWS_Std_00031]
*/
#define NULL_PTR            ((void *)0)

/*
* [SWS_Std_00010]
*/
#define STD_ON              0x01u
#define STD_OFF             0x00u

#define BIT_MASK            0x01

#define E_OK            ((Std_ReturnType)0x00U)      /* Function Return OK */
#define E_NOT_OK        ((Std_ReturnType)0x01U)      /* Function Return NOT OK */

/************************************ Section : Macro Functions Declarations ************************************/


/**
 * @brief Bit Math Macros for setting, clearing, toggling and reading a bit.
 */
#define HWREG8(_address)                ( *((volatile uint8*)(_address)) )

#define SET_BIT(REG , BIT_POSN)         (REG |=  (BIT_MASK << BIT_POSN))
#define CLR_BIT(REG , BIT_POSN)         (REG &= ~(BIT_MASK << BIT_POSN))
#define TOG_BIT(REG , BIT_POSN)         (REG ^=  (BIT_MASK << BIT_POSN))
#define READ_BIT(REG , BIT_POSN)        ((REG >> BIT_POSN ) & BIT_MASK )





#endif /* STD_TYPES_H_ */
