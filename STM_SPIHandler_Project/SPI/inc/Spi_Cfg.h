/**
 * @file Spi.h
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Serial Perpheral Interface Configurations Header file
 * @version info : @ module : SPI Handler/Driver @ Platform : stm32f446re @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 */

#ifndef SPI_CFG_H /* File guard */
#define SPI_CFG_H
/**************************************************************************************************************/

#define PORTA 1
#define PORTB 2
#define PORTC 3

#define PIN0 0
#define PIN1 1
#define PIN2 2
#define PIN3 3
#define PIN4 4
#define PIN5 5
#define PIN6 6
#define PIN7 7
#define PIN8 8
#define PIN9 9
#define PIN10 10
#define PIN11 11
#define PIN12 12
#define PIN13 13
#define PIN14 14
#define PIN15 15


/********************************************** Section : Includes ********************************************/

#include "../../AUTOSAR/Std_Types.h"

/**************************************** Section: Data Type Declarations **************************************/



/*************************************************Global variables***********************************************/
typedef SPI_SlaveSelect SlaveSelect;


/*******************************************************1*****************************************************/


/*
 * Data Frame Format
 */
typedef enum {
    SPI_DFF_8BITS,
     SPI_DFF_16BITS
}Spi_DataFrameFormat;

/********************************************************2****************************************************/

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


/*******************************************************3*****************************************************/


/*
 * Device Modes
 */

typedef enum {
    SPI_DEVICE_MODE_SLAVE,
    SPI_DEVICE_MODE_MASTER
}Spi_DeviceModes;


/*******************************************************4*****************************************************/


/*
 * Bus Configuration
*/
typedef enum {
    SPI_BUS_CONFIG_HALF_DUPLEX, 
    SPI_BUS_CONFIG_FULL_DUPLEX
}Spi_BusConfiguration;


/*******************************************************5*****************************************************/


/*
 * Clock Polarity
 */
typedef enum {
   SPI_CPOL_LOW, 
   SPI_CPOL_HIGH
}Spi_ClockPolarity;


/******************************************************6******************************************************/

/*
 * Clock Phase
 */
typedef enum {
   SPI_CPHA_LOW	, 
   SPI_CPHA_HIGH
}Spi_ClockPhase;

/************************************************************************************************************/



/**********************************************Struct Declaration****************************************************/

typedef struct{
	Spi_DataFrameFormat  spiDFF;          /*Data Frame Format*/
	Spi_ClockSpeed       spiSclkSpeed;    /*Clock Speed*/
	Spi_DeviceModes      spiDeviceMode;   /*Device Mode (Master or Slave)*/
	Spi_BusConfiguration spiBusConfig;    /*Bus Configuration (Full Duplex or Half Duplex)*/
	Spi_ClockPolarity    spiCPOL;         /*Clock Polarity*/
	Spi_ClockPhase       spiCPHA;         /*Clock Phase*/
} Spi_Config;




#endif /* SPI_H */

