/**
 * @file Spi.h
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Serial Perpheral Interface Header file
 * @version info : @ module : SPI Handler/Driver @ Platform : stm32f446re @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 */

#ifndef SPI_H /* File guard */
#define SPI_H

/********************************************** Section : Includes ********************************************/

#include "../../AUTOSAR/Std_Types.h"
#include "Spi_Cfg.h"        


/************************************ Section : Global Variables Definations ************************************/

////////////////////////////////////////////////////////////////////////////////////////////



/**
 * @brief   Spi_HWUnitType
 * [SWS_Spi_00381]
 * Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
 * SPI1_HW_UNIT / SPI2_HW_UNIT / SPI3_HW_UNIT / SPI4_HW_UNIT
 */
typedef uint8       Spi_HWunitType; 
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_JobType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint16      Spi_JobType;     


////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_DataBufferType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint8 Spi_DataBufferType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_ChannelType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint8 Spi_ChannelType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_SequenceType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint8 Spi_SequenceType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_NumberOfDataType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */

typedef uint16 Spi_NumberOfDataType;





/**************************************** Section: Data Type Declarations **************************************/

////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Spi_StatusType
 * [SWS_Spi_00373] 
 * This type defines a range of specific status for SPI Handler/Driver.
 */
typedef enum{
    SPI_UNINIT,         /*  not initialized or not usable      */
    SPI_IDLE,           /* not currently transmitting any Job. */
    SPI_BUSY,           /* performing a SPI Job (transmit).    */
} Spi_StatusType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Spi_JobResultType
 * [SWS_Spi_00374]
 * This type defines a range of specific Jobs status for SPI Handler/Driver.
 */
typedef enum {
    SPI_JOB_OK,          /* Job has been finished */   
    SPI_JOB_PENDING,     /* The meaning of this status is equal to @SPI_BUSY. */    
    SPI_JOB_FAILED,      /* the Job has failed. */       
    SPI_JOB_QUEUED       /*  An asynchronous transmit Job has been accepted, while 
                             actual transmission for this Job has not started yet.*/       
}Spi_JobResultType;

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Spi_SeqResultType
 * [SWS_Spi_00375]
 * This type defines a range of specific Sequences status for SPI Handler/Driver.
 */
typedef enum {
    SPI_SEQ_OK,                 
    SPI_SEQ_PENDING,                
    SPI_SEQ_FAILED,                 
    SPI_SEQ_CANCELED            
}Spi_SeqResultType;            



////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Spi_AsyncModeType
 * [SWS_Spi_00375]
 * This type defines a range of specific Sequences status for SPI Handler/Driver.
 */
typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;


////////////////////////////////////////////////////////////////////////////////////////////
typedef struct {
Spi_StatusType Status;
Spi_JobResultType JobResult;   
Spi_SeqResultType SpiSeqResult;

Spi_DataBufferType SpiDataBuffer;
Spi_NumberOfDataType SpiNumberOfData;
Spi_ChannelType SpiChannel;
Spi_JobType SpiJob;
Spi_SequenceType SpiSequence;
Spi_HWunitType SpiHWunit;

Spi_AsyncModeType SpiAsyncMode ;
}Spi_ConfigType;

// typedef struct 
// {
//     Spi_JobType SpiJobId;                           // Job ID used with APIs
//     uint8 JobPriority;                              // Job Priority ranging from 0 (Lowest) to 3 (Highest) 
//     Spi_ChannelType *ChnlLinkPtrPhysical;           // Ptr to channels asscociated with the job 
//     Spi_HWunitType  SpiHwUnit;                      // SP1 / SPI2 HW unit
//     Spi_ClkPolType SpiClkPol;                       // SPI_CLK_POL_LOW / SPI_CLK_POL_HIGH
//     Spi_ClkPhaseType SpiClkPhase;                   // SPI_CLK_PHASE_FIRST / SPI_CLK_PHASE_SECOND
//     Spi_BaudRateType SpiBaudRate;                   // SPIBAUD_RATE_CLK_DIVx
//     Spi_CS_Pin SpiCSPin;                            // DIO_CHANNEL_xx
//     boolean SpiCsOn;                                // TRUE = Chip Select Functionality ON (HW handling)
// }Spi_JobConfigType;


/************************************ Section: Macro Declarations ************************************/

/*
 * SPI Module Version Info
 */
#define SPI_SW_vendor_ID                1u    
#define SPI_SW_moduleID                 1u
#define SPI_SW_major_version            1u
#define SPI_SW_minor_version            1u 
#define SPI_SW_patch_version            1u





/************************************ Section : Global Variables Definations ************************************/
uint8 Spi_DataBufferType;
uint8 Spi_ChannelType;
uint8 Spi_SequenceType;
uint8 Spi_HWUnitType;
uint16 Spi_NumberOfDataType;


Std_VersionInfoType Spi_VersionInfo = {
    .vendorID = SPI_SW_vendor_ID,
    .moduleID = SPI_SW_moduleID,
    .sw_major_version = SPI_SW_major_version,
    .sw_minor_version = SPI_SW_minor_version,
    .sw_patch_version = SPI_SW_patch_version
};

/************************************* Section : Macro Functions Definations ************************************/

/*************************************** Section : Functions Declarations ***************************************/


/**
 *  - Spi_Init
 *  - [SWS_Spi_00184]
 */
void Spi_Init(const Spi_ConfigType* ConfigPtr);

/**
 *  - Spi_GetVersionInfo
 *  - [SWS_Spi_00184]
 */
void Spi_GetVersionInfo(Std_VersionInfoType *VersionInfo);


#endif /* SPI_H */

