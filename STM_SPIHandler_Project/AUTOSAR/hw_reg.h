/***********************************************************************************************
 * @file           : hw_reg.h
 * @brief          : Hardware Registers Memory mapped file.
 * @version        : 1.0.0
 * @module         : Standard Types
 * @platform       : stm32f446re
 * @sw_version     : 1.0.0
 * @created on     : Aug 20, 2024
 * @author         : AhmedSamy
 ***********************************************************************************************/

/*!< Peripheral base address in the alias region */
#define PERIPH_BASE                 0x40000000U 
/*!< Peripheral memory map */
#define APB1PERIPH_BASE             PERIPH_BASE
#define APB2PERIPH_BASE             (PERIPH_BASE + 0x00010000UL)
#define AHB1PERIPH_BASE             (PERIPH_BASE + 0x00020000UL)
#define AHB2PERIPH_BASE             (PERIPH_BASE + 0x10000000UL)

#define RCC_BASE                    (AHB1PERIPH_BASE + 0x3800)

#define RCC_APB2ENR_OFFSET          0x44U        

#define RCC_APB2ENR     			(*((volatile uint32 *) (RCC_BASE + RCC_APB2ENR_OFFSET)))
#define RCC_APB2ENR_SPI1EN          12U
#define RCC_APB2ENR_SPI2EN          14U
#define RCC_APB2ENR_SPI3EN          15U  


/*********************************************/
/*                  SPI                      */
/*********************************************/
#define SPI1_BASE              *((volatile uint32 *) 0x40013000)
#define SPI2_BASE              *((volatile uint32 *) 0x40003800)
#define SPI3_BASE              *((volatile uint32 *) 0x40013C00)
#define SPI4_BASE              *((volatile uint32 *) 0x40013400)

/*********************************************/
/*           Registers offsets               */
/*********************************************/
#define SPI_CR1_OFFSET          0x00
#define SPI_CR2_OFFSET          0x04
#define SPI_SR_OFFSET           0x08
#define SPI_DR_OFFSET           0x0C
#define SPI_CRCPR_OFFSET        0x10
#define SPI_RXCRCR_OFFSET       0x14
#define SPI_TXCRCR_OFFSET       0x18
#define SPI_I2SCFGR_OFFSET      0x1C
#define SPI_I2SPR_OFFSET        0x20


/*********************************************/
/*             SPI1 Registers                */
/*********************************************/
#define SPI1_CR1               *((volatile uint32 *) (SPI1_BASE + SPI_CR1_OFFSET))
#define SPI1_CR2               *((volatile uint32 *) (SPI1_BASE + SPI_CR2_OFFSET))
#define SPI1_SR                *((volatile uint32 *) (SPI1_BASE + SPI_SR_OFFSET))
#define SPI1_DR                *((volatile uint32 *) (SPI1_BASE + SPI_DR_OFFSET))
#define SPI1_CRCPR             *((volatile uint32 *) (SPI1_BASE + SPI_CRCPR_OFFSET))
#define SPI1_RXCRCR            *((volatile uint32 *) (SPI1_BASE + SPI_RXCRCR_OFFSET))
#define SPI1_TXCRCR            *((volatile uint32 *) (SPI1_BASE + SPI_TXCRCR_OFFSET))
#define SPI1_I2SCFGR           *((volatile uint32 *) (SPI1_BASE + SPI_I2SCFGR_OFFSET))
#define SPI1_I2SPR             *((volatile uint32 *) (SPI1_BASE + SPI_I2SPR_OFFSET))


/*********************************************/
/*             SPI2 Registers                */
/*********************************************/
#define SPI2_CR1               *((volatile uint32 *) (SPI2_BASE + SPI_CR1_OFFSET))
#define SPI2_CR2               *((volatile uint32 *) (SPI2_BASE + SPI_CR2_OFFSET))
#define SPI2_SR                *((volatile uint32 *) (SPI2_BASE + SPI_SR_OFFSET))
#define SPI2_DR                *((volatile uint32 *) (SPI2_BASE + SPI_DR_OFFSET))
#define SPI2_CRCPR             *((volatile uint32 *) (SPI2_BASE + SPI_CRCPR_OFFSET))
#define SPI2_RXCRCR            *((volatile uint32 *) (SPI2_BASE + SPI_RXCRCR_OFFSET))
#define SPI2_TXCRCR            *((volatile uint32 *) (SPI2_BASE + SPI_TXCRCR_OFFSET))
#define SPI2_I2SCFGR           *((volatile uint32 *) (SPI2_BASE + SPI_I2SCFGR_OFFSET))
#define SPI2_I2SPR             *((volatile uint32 *) (SPI2_BASE + SPI_I2SPR_OFFSET))


/*********************************************/
/*             SPI3 Registers                */
/*********************************************/
#define SPI3_CR1               *((volatile uint32 *) (SPI3_BASE + SPI_CR1_OFFSET))
#define SPI3_CR2               *((volatile uint32 *) (SPI3_BASE + SPI_CR2_OFFSET))
#define SPI3_SR                *((volatile uint32 *) (SPI3_BASE + SPI_SR_OFFSET))
#define SPI3_DR                *((volatile uint32 *) (SPI3_BASE + SPI_DR_OFFSET))
#define SPI3_CRCPR             *((volatile uint32 *) (SPI3_BASE + SPI_CRCPR_OFFSET))
#define SPI3_RXCRCR            *((volatile uint32 *) (SPI3_BASE + SPI_RXCRCR_OFFSET))
#define SPI3_TXCRCR            *((volatile uint32 *) (SPI3_BASE + SPI_TXCRCR_OFFSET))
#define SPI3_I2SCFGR           *((volatile uint32 *) (SPI3_BASE + SPI_I2SCFGR_OFFSET))
#define SPI3_I2SPR             *((volatile uint32 *) (SPI3_BASE + SPI_I2SPR_OFFSET))


/*********************************************/
/*             SPI4 Registers                */
/*********************************************/
#define SPI4_CR1               *((volatile uint32 *) (SPI4_BASE + SPI_CR1_OFFSET))
#define SPI4_CR2               *((volatile uint32 *) (SPI4_BASE + SPI_CR2_OFFSET))
#define SPI4_SR                *((volatile uint32 *) (SPI4_BASE + SPI_SR_OFFSET))
#define SPI4_DR                *((volatile uint32 *) (SPI4_BASE + SPI_DR_OFFSET))
#define SPI4_CRCPR             *((volatile uint32 *) (SPI4_BASE + SPI_CRCPR_OFFSET))
#define SPI4_RXCRCR            *((volatile uint32 *) (SPI4_BASE + SPI_RXCRCR_OFFSET))
#define SPI4_TXCRCR            *((volatile uint32 *) (SPI4_BASE + SPI_TXCRCR_OFFSET))
#define SPI4_I2SCFGR           *((volatile uint32 *) (SPI4_BASE + SPI_I2SCFGR_OFFSET))
#define SPI4_I2SPR             *((volatile uint32 *) (SPI4_BASE + SPI_I2SPR_OFFSET))


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
/*              SPI_I2SCFGR Bits                 */
/*********************************************/
#define SPI_I2SCFGR_CHLEN           0
#define SPI_I2SCFGR_DATLEN          1
#define SPI_I2SCFGR_DATLEN          2
#define SPI_I2SCFGR_CKPOL           3
#define SPI_I2SCFGR_I2SSTD          4
#define SPI_I2SCFGR_I2SSTD          5

#define SPI_I2SCFGR_PCMSYNC          7
#define SPI_I2SCFGR_I2SCFG           8
#define SPI_I2SCFGR_I2SCFG           9
#define SPI_I2SCFGR_I2SE            10
#define SPI_I2SCFGR_I2SMOD          11
#define SPI_I2SCFGR_ASTREN          12





/*********************************************/
/*              SPI_I2SPR Bits                 */
/*********************************************/
#define SPI_I2SPR_I2SDIV           0
#define SPI_I2SPR_I2SDIV           1
#define SPI_I2SPR_I2SDIV           2
#define SPI_I2SPR_I2SDIV           3
#define SPI_I2SPR_I2SDIV           4
#define SPI_I2SPR_I2SDIV           5
#define SPI_I2SPR_I2SDIV           6
#define SPI_I2SPR_I2SDIV           7

#define SPI_I2SPR_ODD           8
#define SPI_I2SPR_MCKOE           9

/*********************************************/
/*              SPI_I2SCFGR Bits                 */
/*********************************************/
#define SPI_I2SCFGR_CHLEN           0
#define SPI_I2SCFGR_DATLEN          1
#define SPI_I2SCFGR_DATLEN          2
#define SPI_I2SCFGR_CKPOL           3
#define SPI_I2SCFGR_I2SSTD          4
#define SPI_I2SCFGR_I2SSTD          5

#define SPI_I2SCFGR_PCMSYNC          7
#define SPI_I2SCFGR_I2SCFG           8
#define SPI_I2SCFGR_I2SCFG           9
#define SPI_I2SCFGR_I2SE            10
#define SPI_I2SCFGR_I2SMOD          11
#define SPI_I2SCFGR_ASTREN          12



/*********************************************/
/*              SPI_I2SPR Bits                 */
/*********************************************/
#define SPI_I2SPR_I2SDIV           0
#define SPI_I2SPR_I2SDIV           1
#define SPI_I2SPR_I2SDIV           2
#define SPI_I2SPR_I2SDIV           3
#define SPI_I2SPR_I2SDIV           4
#define SPI_I2SPR_I2SDIV           5
#define SPI_I2SPR_I2SDIV           6
#define SPI_I2SPR_I2SDIV           7

#define SPI_I2SPR_ODD           8
#define SPI_I2SPR_MCKOE           9
