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
typedef enum{
    SPI_UNINIT = 0,
    SPI_IDLE = 1,
    SPI_BUSY = 2
}Spi_StatusType;

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
uint8 DataBufferType;
uint8 ChannelType;
uint8 SequenceType;
uint8 HWUnitType;

uint16 NumberOfDataType;
uint16 JobType;


/************************************ Section : Macro Functions Declarations ************************************/


#define ENABLE_SPI1_CLOCK()      (RCC_APB2ENR |= RCC_APB2ENR_SPI1EN)


void Spi_Init(const Spi_ConfigType* ConfigPtr);





#endif /* SPI_H */
