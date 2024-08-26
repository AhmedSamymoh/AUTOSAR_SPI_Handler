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

/************************************ Section : Includes ************************************/

#include "../../AUTOSAR/Std_Types.h"

/************************************ Section: Data Type Declarations ************************************/

typedef struct{
	uint8 spiDeviceMode;    /*Device Mode (Master or Slave)*/
	uint8 spiBusConfig;     /*Bus Configuration (Full Duplex or Half Duplex)*/
	uint8 spiSclkSpeed;     /*Clock Speed*/
	uint8 spiDFF;           /*Data Frame Format*/
	uint8 spiCPOL;          /*Clock Polarity*/
	uint8 spiCPHA;          /*Clock Phase*/
}Spi_ConfigType;

/**
 * @brief Spi_StatusType
 * [SWS_Spi_00373] 
 */


typedef enum {
    SPI_JOB_OK,
    SPI_JOB_PENDING,
    SPI_JOB_FAILED,
    SPI_JOB_QUEUED
}Spi_JobResultType;

typedef enum {
    SPI_SEQ_OK,
    SPI_SEQ_PENDING,
    SPI_SEQ_FAILED, 
    SPI_SEQ_CANCELED 
}Spi_SeqResultType;

typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;



/************************************ Section: Macro Declarations ************************************/

/*
 * Data Frame Format
 */
#define SPI_DFF_8BITS		            0
#define SPI_DFF_16BITS		            1


/*
 * Clock Speed
 */
#define SPI_SCLK_SPEED_DIV2		        0
#define SPI_SCLK_SPEED_DIV4		        1
#define SPI_SCLK_SPEED_DIV8		        2
#define SPI_SCLK_SPEED_DIV16	        3
#define SPI_SCLK_SPEED_DIV32	        4
#define SPI_SCLK_SPEED_DIV64	        5
#define SPI_SCLK_SPEED_DIV128	        6
#define SPI_SCLK_SPEED_DIV256	        7


/*
 * Device Modes
 */
#define SPI_DEVICE_MODE_MASTER	        1
#define SPI_DEVICE_MODE_SLAVE	        0

/*
 * Bus Configuration
*/
#define SPI_BUS_CONFIG_FULL_DUPLEX		1
#define SPI_BUS_CONFIG_HALF_DUPLEX		0

/*
 * Clock Polarity
 */
#define SPI_CPOL_LOW			        0
#define SPI_CPOL_HIGH			        1


/*
 * Clock Phase
 */
#define SPI_CPHA_LOW			        0
#define SPI_CPHA_HIGH			        1


/*
 * SPI Module Version Info
 */
#define SPI_SW_vendor_ID        1u    
#define SPI_SW_moduleID         1u
#define SPI_SW_major_version    1u
#define SPI_SW_minor_version    1u 
#define SPI_SW_patch_version    1u




/************************************ Section : Global Variables Declarations ************************************/
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

/************************************ Section : Macro Functions Declarations ************************************/


#define ENABLE_SPI1_CLOCK()      (RCC_APB2ENR |= RCC_APB2ENR_SPI1EN)


void Spi_Init(const Spi_ConfigType* ConfigPtr);





<<<<<<< HEAD
#endif /* SPI_H */
=======
#endif /* SPI_H */
>>>>>>> 2b25b951808d7d455ee45e23c1ce88d5c000eaa0
