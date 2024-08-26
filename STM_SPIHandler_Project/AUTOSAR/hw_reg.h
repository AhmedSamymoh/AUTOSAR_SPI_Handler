/***********************************************************************************************
 * @file           : hw_reg.h
 * @brief          : Hardware Registers Memory mapped file.
 * @version        : 1.0.0
 * @module         : Standard Types
 * @platform       : stm32f446re
 * @sw_version     : 1.0.0
 * @created on     : Aug 20, 2024
 * @author         : AhmedSamy - Rana Mohamed
 ***********************************************************************************************/

#ifndef HW_REG_H
#define HW_REG_H

#include "std_types.h"


typedef struct{
volatile uint32 CR1;
volatile uint32 CR2;
volatile uint32 SR;
volatile uint32 DR;
volatile uint32 CRCPR;
volatile uint32 RXCRCR;
volatile uint32 TXCRCR;
}SPI_Registers;


#define SPI1 ((SPI_Registers*)0x40013000)
#define SPI2 ((SPI_Registers*)0x40003800)
#define SPI3 ((SPI_Registers*)0x40003C00)
#define SPI4 ((SPI_Registers*)0x40013400)


/*********************************************/
/*              SPI_CR1 Bits                 */
/*********************************************/
#define SPI_CR1_CPHA        0
#define SPI_CR1_CPOL        1
#define SPI_CR1_MSTR        2
#define SPI_CR1_BR0         3
#define SPI_CR1_BR1         4
#define SPI_CR1_BR2         5
#define SPI_CR1_SPE         6
#define SPI_CR1_LSBF        7
#define SPI_CR1_SSI         8
#define SPI_CR1_SSM         9
#define SPI_CR1_RXONLY      10
#define SPI_CR1_DFF         11
#define SPI_CR1_CRCNXT      12
#define SPI_CR1_CRCEN       13
#define SPI_CR1_BIDIOE      14
#define SPI_CR1_BIDIMODE    15

/*********************************************/
/*              SPI_CR2 Bits                 */
/*********************************************/
#define SPI_CR2_RXDMAEN     0
#define SPI_CR2_TXDMAEN     1
#define SPI_CR2_SSOE        2

#define SPI_CR2_FRF         4
#define SPI_CR2_ERRIE       5
#define SPI_CR2_RXNEIE      6
#define SPI_CR2_TXEIE       7


/*********************************************/
/*              SPI_SR Bits                 */
/*********************************************/
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8

/*********************************************/
/*              SPI_SR Bits                 */
/*********************************************/
#define SPI_SR_RXNE         0
#define SPI_SR_TXE          1
#define SPI_SR_CHSIDE       2
#define SPI_SR_UDR          3
#define SPI_SR_CRCERR       4
#define SPI_SR_MODF         5
#define SPI_SR_OVR          6
#define SPI_SR_BSY          7
#define SPI_SR_FRE          8



/*
typedef struct{

volatile uint32 CR1;
volatile uint32 CR2;
volatile uint32 SR;
volatile uint32 DR;
volatile uint32 CRCPR;
volatile uint32 RXCRCR;
volatile uint32 TXCRCR;
volatile uint32 I2SCFGR;
volatile uint32 I2SPR;
}SPI_Registers;
*/
#endif
