/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "../COM/MCAL/SPI/inc/Spi.h"




void SPI_TransmitReceive(uint8 *txData, uint8 *rxData, int size)
{
    int i = 0;

    while (i < size)
    {
        // 1. Wait for the TXE bit to set in the Status Register (indicates buffer is empty)
        while (!(SPI1->SR & (1 << 1))) {}

        // 2. Write the data to the Data Register
        SPI1->DR = txData[i];

        // 3. Wait for the RXNE bit to set in the Status Register (indicates data is received)
        while (!(SPI1->SR & (1 << 0))) {}

        // 4. Read the received data from the Data Register
        rxData[i] = SPI1->DR;

        i++;
    }

    // 5. After the data has been transmitted, wait for the BSY bit to reset in Status Register
    while (!(SPI1->SR & (1 << 1))) {} // Wait for TXE bit to set
    while ((SPI1->SR & (1 << 7))) {}  // Wait for BSY bit to reset

    // 6. Clear the Overrun flag by reading DR and SR
    uint8_t temp = SPI1->DR;
    temp = SPI1->SR;
}

uint8 rxData = 0;
uint8 txData = 0xAA;
uint8 * Data_tx = &txData;
uint8 * Data_rx = &rxData;
extern Spi_ConfigType Spi_Config;

int main(void)
{
    //System_Init();
	Spi_Init(&Spi_Config);

	//Spi_WriteIB(SPI_Channel_0, (uint16)Data_rx);
    /* Loop forever */
	while(1){
		SPI_TransmitReceive(Data_tx, Data_rx, 20);
	}
}
