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
#include "../../../../Common/Std_Types.h"
#include "Spi.h"


/**************************************************************************************************************/
/***************************************** Section : User Configurations **************************************/
/**************************************************************************************************************/
#define SPI_Channel_1               0u
#define SPI_Channel_2               1u
#define SPI_Channel_3               2u
#define SPI_Channel_4               3u

#define SPI_Channels                4u
#define SPI_Jobs                    2u


/**************************************** Section: Data Type Declarations **************************************/








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

#define SPI1_PORT PORTA
#define SPI2_PORT PORTB
#define SPI3_PORT PORTC
#define SPI4_PORT PORTE


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
/**
 * nOT USED, BUT hw PIN AND SHOULD BE HERE
 * 
 */
#define PIN14 14
#define PIN15 15



/************************************ Section : Global Variables Definations ************************************/

extern Spi_HWUnitConfigType hwUnitConfig_Job_1;
extern Spi_HWUnitConfigType hwUnitConfig_Job_2;

extern Spi_ChannelConfigType channels[4];

extern Spi_JobConfigType jobConfig[2];

extern Spi_SeqConfigType Spi_SeqConfig;

extern Spi_ConfigType Spi_Config;
extern Spi_ConfigType * Spi_Config_Ptr;



/************************************* Section : Macro Functions Definations ************************************/




/*************************************** Section : Functions Declarations ***************************************/
void System_Init(void);
void GPIO_SPI_SlaveSelect_Init (uint8 port, uint8 pin);


#endif /* SPI_H */

