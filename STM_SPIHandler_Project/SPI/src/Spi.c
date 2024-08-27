/**
 * @file SPI.c
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Serial Perpheral Interface Source File
 * @version info : @ module : SPI Handler/Driver @ Platform : stm32f446re @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 */

/********************************************** Section : Includes ********************************************/
#include "../inc/Spi.h"

/**************************************** Section: Data Type Declarations **************************************/


/************************************ Section : Global Variables Definations ************************************/

/************************************* Section : Macro Functions Definations ************************************/


////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief 
 * 
 * @param ConfigPtr 
 */
void Spi_Init(const Spi_ConfigType* ConfigPtr)
{
    /* Enable SPI1 Clock */
    ENABLE_SPI1_CLOCK();

    /* GPIO Port Enabling SPI1 To be alternative pin*/

    /* Reset SPI1 Configuration */
    SPI1_CR1 = 0;

    /* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
    SET_BIT(SPI1_CR1, 2);

    /*SPI_CR1_LSBFIRST = 0 for MSB first*/
    CLR_BIT( SPI1_CR1 , 7 );

    /*SPI_CR1_SSM = 0 for Hardware Slave Management*/
    CLR_BIT( SPI1_CR1 , 9 );

    /* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
    CLR_BIT(SPI1_CR1, 15);

    SPI1_CR2 = 0 ;

    /* Configure SPI Clock Polarity */
    if (ConfigPtr->spiCPOL == SPI_CPOL_LOW){
        CLR_BIT(SPI1_CR1, 1); // SPI_CR1_CPOL = 1
    }else{
        SET_BIT(SPI1_CR1, 1); // SPI_CR1_CPOL = 0
    }

    /* Configure SPI Clock Phase */
    if (ConfigPtr->spiCPHA == SPI_CPHA_LOW){
        CLR_BIT(SPI1_CR1, 0); // SPI1_CR1_CPHA = 0
    }else{
        SET_BIT(SPI1_CR1, 0); // SPI1_CR1_CPHA = 1
    }

    /* Configure SPI Clock Speed */
    /* Clear the bits for clock speed <Mask bits 5:3> */
    SPI1_CR1 &= ~(0x7U << 3);
    /* BR[2:0] bits for Baud Rate */
    SPI1_CR1 |= (ConfigPtr->spiSclkSpeed << 3);

    /* Configure Data Frame Format SPI_CR1_DFF = 1 for 16-bit data frame */
    if (ConfigPtr->spiDFF == SPI_DFF_16BITS){
        SET_BIT(SPI1_CR1, 11);
    }else{
        CLR_BIT(SPI1_CR1, 11);
    }

    /* Enable SPI1 */
    SET_BIT(SPI1_CR1, 6); // SPI_CR1_SPE = 1 to enable SPI

    SPI1_DR = 0xFFFF; // Dummy data to clear RXNE flag
}

////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief This service returns the version information of this module.
 *  - Service ID [hex] 0x09
 *  - Spi_GetVersionInfo
 *  - [SWS_Spi_00184]
 * @param VersionInfo 
 */
void Spi_GetVersionInfo(Std_VersionInfoType *VersionInfo)
{

    if (VersionInfo == NULL_PTR)
    {
        /*Det_ReportError*/
    }
    else
    {
        VersionInfo->moduleID = SPI_SW_moduleID;
        VersionInfo->sw_major_version = SPI_SW_major_version;
        VersionInfo->sw_minor_version = SPI_SW_minor_version;
        VersionInfo->sw_patch_version = SPI_SW_patch_version;
        VersionInfo->vendorID = SPI_SW_vendor_ID;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////