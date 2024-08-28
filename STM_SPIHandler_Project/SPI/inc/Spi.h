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
typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;

////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Data Frame Format
 */
typedef enum {
    SPI_DFF_8BITS,
     SPI_DFF_16BITS
}Spi_DataFrameFormat;

/*
 * Clock Speed
 */
typedef enum {
    SPI_SCLK_SPEED_DIV2,
    SPI_SCLK_SPEED_DIV4,
    SPI_SCLK_SPEED_DIV8,
    SPI_SCLK_SPEED_DIV16,
    SPI_SCLK_SPEED_DIV32,
    SPI_SCLK_SPEED_DIV64,
    SPI_SCLK_SPEED_DIV128,
    SPI_SCLK_SPEED_DIV256
}Spi_ClockSpeed;


/*
 * Device Modes
 */

typedef enum {
    SPI_DEVICE_MODE_SLAVE,
    SPI_DEVICE_MODE_MASTER
}Spi_DeviceModes;

/*
 * Bus Configuration
*/
typedef enum {
    SPI_BUS_CONFIG_HALF_DUPLEX, 
    SPI_BUS_CONFIG_FULL_DUPLEX
}Spi_BusConfiguration;

/*
 * Clock Polarity
 */

typedef enum {
   SPI_CPOL_LOW, 
   SPI_CPOL_HIGH
}Spi_ClockPolarity;

/*
 * Clock Phase
 */
typedef enum {
   SPI_CPHA_LOW	, 
   SPI_CPHA_HIGH
}Spi_ClockPhase;




typedef struct{
	Spi_DeviceModes spiDeviceMode;         /*Device Mode (Master or Slave)*/
	Spi_BusConfiguration spiBusConfig;     /*Bus Configuration (Full Duplex or Half Duplex)*/
	Spi_ClockSpeed spiSclkSpeed;           /*Clock Speed*/
	Spi_DataFrameFormat spiDFF;            /*Data Frame Format*/
	Spi_ClockPolarity spiCPOL;             /*Clock Polarity*/
	Spi_ClockPhase spiCPHA;                /*Clock Phase*/
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




/************************************ Section : Global Variables Definations ************************************/
uint8 Spi_DataBufferType;
uint8 Spi_ChannelType;
uint8 Spi_SequenceType;
uint8 Spi_HWUnitType;

uint16 Spi_NumberOfDataType;
uint16 Spi_JobType;


Std_VersionInfoType Spi_VersionInfo = {
    .vendorID = SPI_SW_vendor_ID,
    .moduleID = SPI_SW_moduleID,
    .sw_major_version = SPI_SW_major_version,
    .sw_minor_version = SPI_SW_minor_version,
    .sw_patch_version = SPI_SW_patch_version
};

/************************************* Section : Macro Functions Definations ************************************/


#define ENABLE_SPI1_CLOCK()      (RCC_APB2ENR |= (1 << RCC_APB2ENR_SPI1EN))




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

