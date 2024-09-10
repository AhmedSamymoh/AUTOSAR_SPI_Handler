/**
 * @file det.c
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Default Error Tracer Source file
 * @version info : @ module : Default Error Tracer @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 *//*========================================================================*/

/********************************************** Section : Includes ********************************************/

#include "det.h"        


/************************************ Section : Global Variables Definations ************************************/

Det_ConfigType Det_Error_Buffer[DET_MAX_ERROR_BUFFER];

static boolean Det_Init_Flag = FALSE;

static uint8 Det_Error_Buffer_index = 0;

/************************************* Section : Macro Functions Definations ************************************/

/*************************************** Section : Functions Declarations ***************************************/

/**
 * @brief  Service to start the Development Error Tracer.
 * 
 */
void Det_Init (const Det_ConfigType* ConfigPtr){
    Det_Init_Flag = TRUE;
}




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
Std_ReturnType Det_ReportError( uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId)
{
 
    /* There is more space in the buffer */
    if (Det_Error_Buffer_index < DET_MAX_ERROR_BUFFER)
    {
        Det_Error_Buffer->ApiId = ApiId;
        Det_Error_Buffer->ErrorId=ErrorId;
        Det_Error_Buffer->InstanceId=InstanceId;
        Det_Error_Buffer->ModuleId =ModuleId;
    }
    else
    {
        /* Not enough buffer space */
        for(;;);

        return E_NOT_OK;
    }

    /* Error data stored in buffer */
    return E_OK;
}

/**
 * @brief Returns the version information of this module
 * 
 * @param versioninfo : Pointer to where to store the version information of this module.
 */
void Det_GetVersionInfo (Std_VersionInfoType* versioninfo){

    versioninfo->moduleID = DET_SW_moduleID;
    versioninfo->sw_major_version = DET_SW_major_version;
    versioninfo->sw_minor_version = DET_SW_minor_version;
    versioninfo->sw_patch_version = DET_SW_patch_version;
    versioninfo->vendorID = DET_SW_vendor_ID;
}
