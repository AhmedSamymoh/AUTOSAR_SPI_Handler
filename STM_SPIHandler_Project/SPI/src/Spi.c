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
void GPIO_Spi_Init(void){

	/*===================================================================*/
	// Set PA5, PA6, and PA7 to alternate function mode (AF5 for SPI1)
	GPIOA->MODER &= ~( (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)) | (0x3UL << (18U)) ); // Clear mode bits
	GPIOA->MODER |= ( (0x2UL << (10U)) | (0x2UL << (12U)) | (0x2UL << (14U)) | (0x2UL << (18U)) ); // Set to alternate function

	// Set alternate function to AF5 (SPI1)
	GPIOA->AFR[0] &= ~((0xF << (4 * 4)) | (0xF << (5 * 4)) | (0xF << (6 * 4)) | (0xF << (7 * 4))); // Clear AFR bits
	GPIOA->AFR[0] |= (5 << (4 * 4)) | (5 << (5 * 4)) | (5 << (6 * 4)) | (5 << (7 * 4)); // Set AF5 for PA5, PA6, PA7

	// Set PA5, PA6, and PA7 to very high speed
	GPIOA->OSPEEDR |= (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)) | (0x3UL << (18U));

	// Set PA5, PA6, and PA7 to no pull-up/pull-down
	GPIOA->PUPDR &= ~((0x3UL << (4U)) | (0x3UL << (10U)) | (0x3UL << (12U)) | (0x3UL << (14U)));
	/*===================================================================*/
}

void Spi_Init(const Spi_ConfigType* ConfigPtr)
{
	/* GPIO Port Enabling SPI1 To be alternative pin*/
	GPIO_Spi_Init();

	/* Reset SPI1 Configuration */
	SPI1->CR1 = 0;

	/* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
	SET_BIT(SPI1->CR1, SPI_CR1_MSTR );

	/*SPI_CR1_LSBFIRST = 0 for MSB first*/
	CLR_BIT( SPI1->CR1 , SPI_CR1_LSBF );

	/* SSM=1, SSi=1 -> Software Slave Management Setting SSI, > to avoid MODF Error*/
	SET_BIT( SPI1->CR1 , SPI_CR1_SSM );
	SET_BIT( SPI1->CR1 , SPI_CR1_SSI );

	/* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
	CLR_BIT(SPI1->CR1, SPI_CR1_BIDIMODE);

	SPI1->CR2 = 0 ;

	/* Configure SPI Clock Polarity */
	if (ConfigPtr->spiCPOL == SPI_CPOL_LOW){
		CLR_BIT(SPI1->CR1, SPI_CR1_CPOL); /* 0: CK to 0 when idle */
	}else{
		SET_BIT(SPI1->CR1, SPI_CR1_CPOL); /* 1: CK to 1 when idle */
	}

	/* Configure SPI Clock Phase */
	if (ConfigPtr->spiCPHA == SPI_CPHA_LOW){
		CLR_BIT(SPI1->CR1, SPI_CR1_CPHA); /* 0: The first clock transition is the first data capture edge*/
	}else{
		SET_BIT(SPI1->CR1, SPI_CR1_CPHA); /* 1: The second clock transition is the first data capture edge */
	}

	/* Configure SPI Clock Speed */
	/* Clear the bits for clock speed <Mask bits 5:3> */
	SPI1->CR1 &= ~(0x7U << SPI_CR1_BR0);
	/* BR[2:0] bits for Baud Rate */
	SPI1->CR1 |= (ConfigPtr->spiSclkSpeed << SPI_CR1_BR0);

	/* Configure Data Frame Format SPI_CR1_DFF = 1 for 16-bit data frame */
	if (ConfigPtr->spiDFF == SPI_DFF_16BITS){
		SET_BIT(SPI1->CR1, SPI_CR1_DFF);
	}else{
		CLR_BIT(SPI1->CR1, SPI_CR1_DFF);
	}

	/* Enable SPI1 */
	SET_BIT(SPI1->CR1, SPI_CR1_SPE); // SPI_CR1_SPE = 1 to enable SPI
    
	SPI1->DR = 0xFFFF; // Dummy data to clear RXNE flag
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