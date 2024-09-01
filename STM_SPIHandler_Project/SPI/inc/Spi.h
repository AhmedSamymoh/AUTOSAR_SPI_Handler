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
#include "../../AUTOSAR/det.h"      


/**************************************** Section: Data Type Declarations **************************************/


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief   Spi_HWUnitType
 * [SWS_Spi_00381]
 * Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
 * SPI1_HW_UNIT / SPI2_HW_UNIT / SPI3_HW_UNIT / SPI4_HW_UNIT
 */
typedef uint8       Spi_HWUnitType; 

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_ChannelType
 * [SWS_Spi_00378]
 * Specifies the identification (ID) for a Channel.
 */
typedef uint8       Spi_ChannelType;   
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_JobType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint16      Spi_JobType;     
////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief    Spi_SequenceType
 * [SWS_Spi_00380]
 * Specifies the identification (ID) for a sequence of jobs.
 */
typedef uint8       Spi_SequenceType;     
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief     Spi_DataBufferType
 * [SWS_Spi_00376]
 * Type of application data buffer elements.
 * Usage 0:  only Internal Buffers. (8 or 16 bits for SPIx_DR) 
 * Usage 1:  only External Buffers. (9, 17 or 5 Bits.. User defined )
 * Usage 2:  both buffers types : Internal and External Buffers.
 * Spi_DataBufferType = 8 / 16 > SPI1_CR1_DFF = 0/1
 */
typedef uint8       Spi_DataBufferType;     
////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief      Spi_NumberOfDataType
 * [SWS_Spi_00377]
 * Type for defining the number of data elements to send and / or receive by Channel
 */
typedef uint16      Spi_NumberOfDataType;     

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
* @brief   The enumeration containing the designated values for buffer types (internal or external).
*
*/
typedef enum
{
    InternalBuffer = 0,     /* Configured using Internal Buffer. */
    ExternalBuffer          /* Configured using External Buffer. */
} Spi_BufferType;   

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  
 * 
 */
typedef struct{
    /* SpiPrescaller Clock Speed                SPI_SCLK_SPEED_DIV2 : SPI_SCLK_SPEED_DIV256 */
    Spi_ClockSpeed       SpiPrescaller;         
    /* Clock Polarity                           SPI_CPOL_LOW : SPI_CPOL_HIGH */
	Spi_ClockPolarity    spiCPOL;
    /* Clock Phase                              SPI_CPHA_LOW : SPI_CPHA_HIGH */               
	Spi_ClockPhase       spiCPHA;               
    /*Chip Select Port                          PORTA : PORTH */
    Spi_CS_Port          spiCSPort;             
    /*Chip Select Pin                           PIN0 : PIN15 */
    Spi_CS_Pin           spiCSPin;              
} Spi_HWUnitConfigType;


typedef struct
{
    Spi_ChannelType      SpiChannelId;          /* Channel ID used with APIs */
    Spi_BufferType       BufferType;            /* Buffer Type InternalBuffer/ExternalBuffer. */
    Spi_DataFrameFormat  spiDFF;                /* Data Frame Format: SPI_DFF_8BITS : SPI_DFF_16BITS */
    uint32               DefaultTransmitValue;  /* Default Transmit Value. */ 
    Spi_NumberOfDataType Length;                /* size of . */
    Spi_StatusType       Status;                /* channel internal state. */

} Spi_ChannelConfigType;


typedef struct 
{   
    Spi_JobType           SpiJobId;             /* Job ID used with APIs */
    Spi_HWUnitType        spiHWUint;            /*SPI Hardware Unit: SPI1/SPI4/SPI3/SPI4 */
    uint8                 JobPriority;          /* Job Priority ranging from 0 (Lowest) to 3 (Highest)*/ 
    Spi_ChannelConfigType *ChannelsPtr;         /* Ptr to channels asscociated with the job */ 
    Spi_HWUnitConfigType  *SpiHWUnitConfig;     /* Pointer to HW unit configuration */  
}Spi_JobConfigType;

////////////////////////////////////////////////////////////////////////////////////////////
typedef struct 
{
    Spi_JobConfigType     *JobLinkPtr;           /* Ptr to jobs IDs asscociated with the Sequence*/
    Spi_JobType           NoOfJobs;			     /* Number of Jobs configured */
    Spi_SequenceType      SpiSeqId;              /* Sequence ID used with APIs */ 
}Spi_SeqConfigType;

////////////////////////////////////////////////////////////////////////////////////////////

typedef struct Spi_ConfigType
{
    /* Number of Channels configured */
    Spi_ChannelType NoOfChannels;
    
    /* pointer to job configuration */
    Spi_JobConfigType * Spi_JobConfigPtr; 
   
    /* Pointer to channel configuration  */
    Spi_ChannelConfigType * Spi_ChannelConfigPtr ;   

}Spi_ConfigType;

/************************************ Section: Macro Declarations ************************************/
                                                                                    
/*
 * SPI Module Version Info
 */
#define SPI_SW_vendor_ID                1u    
#define SPI_SW_moduleID                 1u
#define SPI_SW_major_version            1u
#define SPI_SW_minor_version            1u 
#define SPI_SW_patch_version            1u


/*
 * SPI Hardware Units 
 * @Spi_HWUnitType
 */
#define Spi_HWUnit_SPI1                 (Spi_HWUnitType)1u
#define Spi_HWUnit_SPI2                 (Spi_HWUnitType)2u
#define Spi_HWUnit_SPI3                 (Spi_HWUnitType)3u
#define Spi_HWUnit_SPI4                 (Spi_HWUnitType)4u



/*
 * Spi_ErrorCodes_define
 * [SWS_Spi_91001]
 */
/* APIs called with an unexpected value for the pointer */
#define SPI_E_PARAM_POINTER             ((uint8)0x10u)
/* API service called with wrong hardware unit */
#define SPI_E_PARAM_UNIT                ((uint8)0x0Eu)
/* API SPI_Init service called while the SPI driver has been already initialized */
#define SPI_E_ALREADY_INITIALIZED       ((uint8)0x4Au)
/* API service called with wrong lenghth for EB */
#define SPI_E_PARAM_LENGTH              ((uint8)0x0Du)


/**
 * @brief Service ID for Spi_Init 
 */
#define SPI_INIT_SID                    ((uint8)0x00u)

/**
 * @brief Service ID for Spi_DeInit 
 */
#define SPI_DEINIT_SID                  ((uint8)0x01u)

/**
 * @brief Service ID for Spi_GetVersionInfo 
 */
#define SPI_GET_VERSION_INFO_SID        ((uint8)0x09u)

/**
 * @brief Service ID for Spi_GetHWUnitStatus 
 */
#define SPI_GET_HW_UNIT_STATUS_SID      ((uint8)0x0bu)


/************************************ Section : Global Variables Definations ************************************/

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
 * @brief 
 * Spi_Init : [SWS_Spi_00184]
 * 
 * @param ConfigPtr 
 */
void Spi_Init(const Spi_ConfigType* ConfigPtr);



/**
 * @brief This service returns the status of the specified SPI Har
 * dware microcontroller 
 * peripheral.
 * Spi_GetHWUnitStatus : [SWS_Spi_00186]
 * 
 * @param HWUnit 
 * @return Spi_StatusType : SPI_UNINIT, SPI_IDLE, SPI_BUSY
 */
Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit);


/**
 * @brief This service returns the version information of this module.
 * Spi_GetVersionInfo : [SWS_Spi_00184]
 * 
 * @param VersionInfo 
 */
void Spi_GetVersionInfo(Std_VersionInfoType *VersionInfo);




#endif /* SPI_H */

