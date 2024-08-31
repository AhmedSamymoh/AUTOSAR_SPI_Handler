/**
 * @file det.h
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Default Error Tracer Header file
 * @version info : @ module : Default Error Tracer @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 *//*========================================================================*/

#ifndef DET_H /* File guard */
#define DET_H

/********************************************** Section : Includes *********************************************/

#include "Std_Types.h"        


/***************************************** Section: Data Type Declarations *************************************/

/**
 * @brief Det_ConfigType
 * [SWS_Det_00210] Configuration data structure of the Det module
 */
typedef struct det
{
    uint16 ModuleId;
    uint8 InstanceId;
    uint8 ApiId;
    uint8 ErrorId;
} Det_ConfigType;


/****************************************** Section: Macro Declarations ****************************************/

/*
 * SPI Module Version Info
 */
#define DET_SW_vendor_ID                1u    
#define DET_SW_moduleID                 1u
#define DET_SW_major_version            1u
#define DET_SW_minor_version            1u 
#define DET_SW_patch_version            1u



/**
 * @brief Maximum Error The Buffer can handle
 * 
 */
#define DET_MAX_ERROR_BUFFER            3u



/************************************ Section : Global Variables Definations ************************************/

Std_VersionInfoType Det_VersionInfo = {
    .vendorID = DET_SW_vendor_ID,
    .moduleID = DET_SW_moduleID,
    .sw_major_version = DET_SW_major_version,
    .sw_minor_version = DET_SW_minor_version,
    .sw_patch_version = DET_SW_patch_version
};

/************************************* Section : Macro Functions Definations ************************************/

/*************************************** Section : Functions Declarations ***************************************/

/**
 * @brief Service to initialize the Default Error Tracer
 * 
 * @param ConfigPtr 
 */
void Det_Init (const Det_ConfigType* ConfigPtr);


/**
 * @brief Service to start the Default Error Tracer
 * 
 */
void Det_Start (void);


/**
 * @brief Service to report development errors.
 * 
 * @param ModuleId : Module ID of calling module.
 * @param InstanceId : The identifier of the index based instance of a module
 * @param ApiId : ID of API service in which error is detected
 * @param ErrorId : ID of detected development error (defined in SWS of calling module).
 * @return Std_ReturnType : never returns a value, but has a return type for compatibility with
                            services and hooks
 */
Std_ReturnType Det_ReportError (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);



/**
 * @brief Returns the version information of this module
 * 
 * @param versioninfo : Pointer to where to store the version information of this module.
 */
void Det_GetVersionInfo (Std_VersionInfoType* versioninfo);



#endif /* DET_H */