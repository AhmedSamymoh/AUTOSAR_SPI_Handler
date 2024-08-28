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


/**************************************** Section: Data Type Declarations **************************************/


////////////////////////////////////////////////////////////////////////////////////////////
/**
 * @brief   Spi_HWUnitType
 * [SWS_Spi_00381]
 * Specifies the identification (ID) for a SPI Hardware microcontroller peripheral (unit).
 * SPI1_HW_UNIT / SPI2_HW_UNIT / SPI3_HW_UNIT / SPI4_HW_UNIT
 */
typedef uint8       Spi_HWUnitType; 

/*
 * SPI Hardware Units
 */
#define Spi_HWUnit_SPI1                 (Spi_HWUnitType)1u
#define Spi_HWUnit_SPI2                 (Spi_HWUnitType)2u
#define Spi_HWUnit_SPI3                 (Spi_HWUnitType)3u
#define Spi_HWUnit_SPI4                 (Spi_HWUnitType)4u

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief    Spi_JobType
 * [SWS_Spi_00379]
 * Specifies the identification (ID) for a Job.
 */
typedef uint16      Spi_JobType;     
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
    InternalBuffer = 0,     /**< @brief The Channel is configured using Internal Buffer. */
    ExternalBuffer          /**< @brief The Channel is configured using External Buffer. */
} Spi_BufferType;   

////////////////////////////////////////////////////////////////////////////////////////////

typedef struct{
    Spi_HWUnitType       spiHWuint;       /*SPI Hardware Unit: SPI1/SPI4/SPI3/SPI4 */
	Spi_BusConfiguration spiBusConfig;    /*Bus Configuration (Full Duplex or Half Duplex)*/
	Spi_ClockSpeed       spiSclkSpeed;    /*Clock Speed*/
	Spi_DataFrameFormat  spiDFF;          /*Data Frame Format*/
	Spi_ClockPolarity    spiCPOL;         /*Clock Polarity*/
	Spi_ClockPhase       spiCPHA;         /*Clock Phase*/
    Spi_CS_Port          spiCSPort;       /*Chip Select Port*/
    Spi_CS_Pin           spiCSPin;        /*Chip Select Pin*/
} Spi_HWUnitConfigType;

typedef struct
{
    Spi_BufferType BufferType;   /* Buffer Type InternalBuffer/ExternalBuffer. */
    uint8 FrameSize;             /** Data frame size. */   
    boolean Lsb;                 /** Bite order (MSB/LSB). */
    uint32 DefaultTransmitValue; /* Default Transmit Value. */
    Spi_NumberOfDataType Length; /* Data length. */
    Spi_StatusType Status;       /* channel internal state. */
} Spi_ChannelConfigType;


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

uint8 Spi_ChannelType;
uint8 Spi_SequenceType;

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
 * 
 */

/**
 * @brief 
 * Spi_Init : [SWS_Spi_00184]
 * 
 * @param ConfigPtr 
 */
void Spi_Init(const Spi_HWUnitConfigType* ConfigPtr);



/**
 * @brief This service returns the version information of this module.
 * Spi_GetVersionInfo : [SWS_Spi_00184]
 * 
 * @param VersionInfo 
 */
void Spi_GetVersionInfo(Std_VersionInfoType *VersionInfo);


/**
 * @brief This service returns the status of the specified SPI Hardware microcontroller 
 * peripheral.
 * Spi_GetHWUnitStatus : [SWS_Spi_00186]
 * 
 * @param HWUnit 
 * @return Spi_StatusType : SPI_UNINIT, SPI_IDLE, SPI_BUSY
 */
Spi_StatusType Spi_GetHWUnitStatus (Spi_HWUnitType HWUnit);






void Spi_Ipw_Init(const Spi_HWunitType HWUnitId, const Spi_HWUnitConfigType * HWUnit);



#endif /* SPI_H */

