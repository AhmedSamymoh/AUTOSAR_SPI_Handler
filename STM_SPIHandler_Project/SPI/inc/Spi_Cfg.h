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



/**************************************************************************************************************/
/***************************************** Section : User Configurations **************************************/
/**************************************************************************************************************/
#define SPI_Channel_1               1u
#define SPI_Channel_2               2u
#define SPI_Channel_3               3u


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


/*
 * Device Modes
 * [SWS_Spi_00040] The SPI Handler/Driver handles only the Master mode.
 */
#define SPI_DEVICE_MODE_MASTER         1u

/*
 * Bus Configuration
 * [SWS_Spi_00050] ⌈The SPI Handler/Driver only supports full-duplex mode.
 */
#define SPI_BUS_CONFIG_FULL_DUPLEX     1u



#define PORTA 0
#define PORTB 1
#define PORTC 2
#define PORTD 3
#define PORTE 4 
#define PORTF 5
#define PORTG 6
#define PORTH 7


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



/************************************ Section : Global Variables Definations ************************************/

/************************************* Section : Macro Functions Definations ************************************/




/*************************************** Section : Functions Declarations ***************************************/
void System_Init(void);
void GPIO_SPI_SlaveSelect_Init (uint8 port, uint8 pin);


#endif /* SPI_H */

