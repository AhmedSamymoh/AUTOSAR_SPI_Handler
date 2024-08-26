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

#include "../inc/Spi.h"

void Spi_Init(const Spi_ConfigType* ConfigPtr)
{
    /* Enable SPI1 Clock */
    ENABLE_SPI1_CLOCK();

    /* Reset SPI1 Configuration */
    SPI1_CR1 = 0;

    /* Configure SPI Device Mode SPI_CR1_MSTR = 1 for Master Mode */
    SET_BIT(SPI1_CR1, 2);

    /* Configure SPI Bus Configuration SPI_CR1_BIDIMODE = 0 for Full Duplex */
    CLR_BIT(SPI1_CR1, 15);

    /* Configure SPI Clock Polarity */
    if (ConfigPtr->spiCPOL == SPI_CPOL_LOW){
        CLR_BIT(SPI1_CR1, 1); // SPI_CR1_CPOL = 1
    }else{
        SET_BIT(SPI1_CR1, 1); // SPI_CR1_CPOL = 0
    }

    /* Configure SPI Clock Phase */
    if (ConfigPtr->spiCPHA == SPI_CPHA_LOW){
        CLR_BIT(SPI1_CR1, 0); // SPI1_CR1_CPOL = 0
    }else{
        SET_BIT(SPI1_CR1, 0); // SPI1_CR1_CPOL = 1
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

}
