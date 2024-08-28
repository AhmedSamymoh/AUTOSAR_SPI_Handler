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




/********************************************** Section : Includes ********************************************/

#include "../../AUTOSAR/Std_Types.h"

/**************************************** Section: Data Type Declarations **************************************/
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


/*
 * Async Mode
 */
typedef enum {
    SPI_POLLING_MODE,
    SPI_INTERRUPT_MODE
}Spi_AsyncModeType;

/*
 * CS Port
 */
typedef uint8 Spi_CS_Port;


/*
 * CS Pin
 */
typedef uint8 Spi_CS_Pin;





/************************************ Section: Macro Declarations ************************************/





/************************************ Section : Global Variables Definations ************************************/

/************************************* Section : Macro Functions Definations ************************************/


#define ENABLE_SPI1_CLOCK()      (RCC_APB2ENR |= (1 << RCC_APB2ENR_SPI1EN))




/*************************************** Section : Functions Declarations ***************************************/


#endif /* SPI_H */

