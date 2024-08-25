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

// Spi_ConfigType for SPI init 
typedef enum {
    SPI_UNINIT, SPI_IDLE, SPI_BUSY
    }Spi_StatusType;

typedef enum {
    SPI_JOB_OK, SPI_JOB_PENDING, SPI_JOB_FAILED, SPI_JOB_QUEUED
    }Spi_JobResultType;

typedef enum {
    SPI_SEQ_OK, SPI_SEQ_PENDING, SPI_SEQ_FAILED, SPI_SEQ_CANCELED 
    }Spi_SeqResultType;

typedef enum {
    SPI_POLLING_MODE, SPI_INTERRUPT_MODE
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



/************************************ Section : Global Variables Declarations ************************************/
uint8_t Spi_DataBufferType, Spi_ChannelType, Spi_SequenceType, Spi_HWUnitType;
uint16_t Spi_NumberOfDataType, Spi_JobType;

/************************************ Section : Macro Functions Declarations ************************************/


#define ENABLE_SPI1_CLOCK()      (RCC_APB2ENR |= RCC_APB2ENR_SPI1EN)


void Spi_Init(const Spi_ConfigType* ConfigPtr);





#endif /* SPI_H */
