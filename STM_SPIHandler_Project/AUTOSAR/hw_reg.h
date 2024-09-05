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

#include "Std_Types.h"

/* ================================================================ */
/* ====== AHBx and APBx Bus Peripheral Base Addresses ============= */
/* ================================================================ */

#define PERIPH_BASE			        0x40000000U		/* Peripheral base address in the alias region  */
#define APB1PERIPH_BASE		        PERIPH_BASE		/* Base address of APB1 peripheral memory */
#define APB2PERIPH_BASE		        0x40010000U		/* Base address of APB2 peripheral memory */
#define AHB1PERIPH_BASE		        0x40020000U		/* Base address of AHB1 peripheral memory */
#define AHB2PERIPH_BASE		        0x50000000U		/* Base address of AHB2 peripheral memory */


/* ================================================================ */
/* ============== Base Addresses for APB1 Peripherals ============= */
/* ================================================================ */

#define SPI2_BASE			(APB1PERIPH_BASE + 0x3800) /* SPI2 base address   */
#define SPI3_BASE			(APB1PERIPH_BASE + 0x3C00) /* SPI3 base address   */

/* ================================================================ */
/* ============== Base Addresses for APB2 Peripherals ============= */
/* ================================================================ */

#define SPI1_BASE			(APB2PERIPH_BASE + 0x3000) /* SPI1 base address   */
#define SPI4_BASE			(APB2PERIPH_BASE + 0x3400) /* SPI4 base address   */

#include "Std_Types.h"

/* ================================================================ */
/* ====== AHBx and APBx Bus Peripheral Base Addresses ============= */
/* ================================================================ */

#define PERIPH_BASE			        0x40000000U		/* Peripheral base address in the alias region  */
#define APB1PERIPH_BASE		        PERIPH_BASE		/* Base address of APB1 peripheral memory */
#define APB2PERIPH_BASE		        0x40010000U		/* Base address of APB2 peripheral memory */
#define AHB1PERIPH_BASE		        0x40020000U		/* Base address of AHB1 peripheral memory */
#define AHB2PERIPH_BASE		        0x50000000U		/* Base address of AHB2 peripheral memory */


/* ================================================================ */
/* ============== Base Addresses for APB1 Peripherals ============= */
/* ================================================================ */

#define SPI2_BASE			(APB1PERIPH_BASE + 0x3800) /* SPI2 base address   */
#define SPI3_BASE			(APB1PERIPH_BASE + 0x3C00) /* SPI3 base address   */

/* ================================================================ */
/* ============== Base Addresses for APB2 Peripherals ============= */
/* ================================================================ */

#define SPI1_BASE			(APB2PERIPH_BASE + 0x3000) /* SPI1 base address   */
#define SPI4_BASE			(APB2PERIPH_BASE + 0x3400) /* SPI4 base address   */


#define RCC_APB2ENR_SPI1EN          12U
#define RCC_APB2ENR_SPI4EN          13U
#define RCC_APB1ENR_SPI2EN          14U
#define RCC_APB1ENR_SPI3EN          15U  

/* ================================================================ */
/* ============== Base Addresses for AHB1 Peripherals ============= */
/* ================================================================ */

#define RCC_BASE			(AHB1PERIPH_BASE + 0x3800) /* RCC base address	 					*/
#define GPIOA_BASE			(AHB1PERIPH_BASE + 0x0000) /* GPIOA Base Address					*/
#define GPIOB_BASE			(AHB1PERIPH_BASE + 0x0400) /* GPIOB Base Address					*/
#define GPIOC_BASE			(AHB1PERIPH_BASE + 0x0800) /* GPIOC Base Address					*/
#define GPIOD_BASE			(AHB1PERIPH_BASE + 0x0C00) /* GPIOD Base Address					*/
#define GPIOE_BASE			(AHB1PERIPH_BASE + 0x1000) /* GPIOE Base Address					*/
#define GPIOF_BASE			(AHB1PERIPH_BASE + 0x1400) /* GPIOF Base Address					*/
#define GPIOG_BASE			(AHB1PERIPH_BASE + 0x1800) /* GPIOG Base Address					*/
#define GPIOH_BASE			(AHB1PERIPH_BASE + 0x1C00) /* GPIOH Base Address					*/



/* ================================================================ */
/* ================= Peripheral Registers RCC  ==================== */
/* ================================================================ */

typedef struct
{
	volatile uint32 CR;				    /* RCC clock control register, 	    							Address offset: 0x00 	*/
	volatile uint32 PLLCFGR;			/* RCC PLL configuration register, 	    						Address offset: 0x04 	*/
	volatile uint32 CFGR;				/* RCC clock configuration register, 	   						Address offset: 0x08 	*/
	volatile uint32 CIR;				/* RCC clock interrupt register, 	    						Address offset: 0x0C 	*/
	volatile uint32 AHB1RSTR;			/* RCC AHB1 peripheral reset register, 	    					Address offset: 0x10 	*/
	volatile uint32 AHB2RSTR;			/* RCC AHB2 peripheral reset register, 	    					Address offset: 0x14 	*/
	volatile uint32 AHB3RSTR;			/* RCC AHB3 peripheral reset register, 	    					Address offset: 0x18 	*/
	uint32  Reserved_0;	                /* RCC reserved register, 										Address offset: 0x1C 	*/
	volatile uint32 APB1RSTR;			/* RCC APB1 peripheral reset register, 	    					Address offset: 0x20 	*/
	volatile uint32 APB2RSTR;			/* RCC APB2 peripheral reset register, 	    					Address offset: 0x24 	*/
	uint32  Reserved_1[2];              /* RCC reserved register, 										Address offset: 0x28-2C */
	volatile uint32 AHB1ENR;			/* RCC AHB1 peripheral clock enable register, 	    			Address offset: 0x30 	*/
	volatile uint32 AHB2ENR;			/* RCC AHB2 peripheral clock enable register, 	    			Address offset: 0x34 	*/
	volatile uint32 AHB3ENR;			/* RCC AHB3 peripheral clock enable register, 	    			Address offset: 0x38 	*/
	uint32  Reserved_2;	                /* RCC reserved register, 										Address offset: 0x3C 	*/
	volatile uint32 APB1ENR;			/* RCC APB1 peripheral clock enable register, 	    			Address offset: 0x40 	*/
	volatile uint32 APB2ENR;			/* RCC APB2 peripheral clock enable register, 	    			Address offset: 0x44 	*/
    uint32 Reserved_3[2];               /* RCC reserved register, 										Address offset: 0x48-4C */
    volatile uint32 AHB1LPENR;		    /* RCC AHB1 peripheral clock enable in low power mode register,	Address offset: 0x50 	*/
    volatile uint32 AHB2LPENR;		    /* RCC AHB2 peripheral clock enable in low power mode register,	Address offset: 0x54 	*/
    volatile uint32 AHB3LPENR;		    /* RCC AHB3 peripheral clock enable in low power mode register,	Address offset: 0x58 	*/
	uint32  Reserved_4;	                /* RCC reserved register, 										Address offset: 0x5C 	*/
	volatile uint32 APB1LPENR;		    /* RCC APB1 peripheral clock enable in low power mode register,	Address offset: 0x60 	*/
	volatile uint32 APB2LPENR;		    /* RCC APB2 peripheral clock enable in low power mode register,	Address offset: 0x64 	*/
	uint32  Reserved_5[2];              /* RCC reserved register, 										Address offset: 0x68-6C */
	volatile uint32 BDCR;				/* RCC back up domain control register, 						Address offset: 0x70 	*/
	volatile uint32 CSR;				/* RCC clock control & status register, 						Address offset: 0x74 	*/
	uint32  Reserved_6[2];              /* RCC reserved register, 										Address offset: 0x78-7C */
	volatile uint32 SSCGR;			    /* RCC spread spectrum clock generation register, 				Address offset: 0x80 	*/
	volatile uint32 PLLI2SCFGR;		    /* RCC PLLI2S configuration register, 							Address offset: 0x84 	*/
	volatile uint32 PLLSAICFGR;		    /* RCC PLL configuration register, 								Address offset: 0x88 	*/
	volatile uint32 DCKCFGR;			/* RCC dedicated clock configuration register, 					Address offset: 0x8C 	*/
	volatile uint32 CKGATENR;			/* RCC clock gated enable register, 							Address offset: 0x90 	*/
}RCC_Registers;

/* ================================================================ */
/* ================= Peripheral Registers GPIO ==================== */
/* ================================================================ */

typedef struct
{
	uint32 MODER;  		/* GPIO port mode register, 	    			Address offset: 0x00 */
	uint32 OTYPER; 		/* GPIO port output type register,  			Address offset: 0x04 */
	uint32 OSPEEDR;  	/* GPIO port output speed register, 			Address offset: 0x08 */
	uint32 PUPDR; 		/* GPIO port pull-up/down register, 			Address offset: 0x0C */
	uint32 IDR; 		/* GPIO port input data register,    			Address offset: 0x10 */
	uint32 ODR; 		/* GPIO port output data register, 	 			Address offset: 0x14 */
	uint32 BSRR; 		/* GPIO port bit set/reset register, 			Address offset: 0x18 */
	uint32 LCKR; 		/* GPIO port configuration lock register,		Address offset: 0x1C */
	uint32 AFR[2];		/* AFR[0]: GPIO alternate function low register,
						   AFR[1]: GPIO alternate function high register,	Address offset: 0x20-24 */
}GPIO_Registers;

/* ================================================================ */
/* ===================         SPI          ======================= */
/* ================================================================ */
typedef struct{
    volatile uint32 CR1;
    volatile uint32 CR2;
    volatile uint32 SR;
    volatile uint32 DR;
    volatile uint32 CRCPR;
    volatile uint32 RXCRCR;
    volatile uint32 TXCRCR;
} SPI_Registers;

/* ================================================================ */
/* =================== Peripheral Instants  ======================= */
/* ================================================================ */

#define GPIOA 			((GPIO_Registers *) GPIOA_BASE)
#define GPIOB 			((GPIO_Registers *) GPIOB_BASE)
#define GPIOC 			((GPIO_Registers *) GPIOC_BASE)
#define GPIOD			((GPIO_Registers *) GPIOD_BASE)
#define GPIOE 			((GPIO_Registers *) GPIOE_BASE)
#define GPIOF 			((GPIO_Registers *) GPIOF_BASE)
#define GPIOG 			((GPIO_Registers *) GPIOG_BASE)
#define GPIOH 			((GPIO_Registers *) GPIOH_BASE)

#define RCC				((RCC_Registers *) RCC_BASE)

#define SPI1            ((SPI_Registers*)SPI1_BASE)
#define SPI2            ((SPI_Registers*)SPI2_BASE)
#define SPI3            ((SPI_Registers*)SPI3_BASE)
#define SPI4            ((SPI_Registers*)SPI4_BASE)

/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ==============          Clock Enable           ================= */
/* ================================================================ */

/* ============ GPIOx peripherals ============ */
#define GPIOA_PCLK_EN()		( RCC->AHB1ENR |= (1 << 0) ) /* GPIOA peripheral clock enabled */
#define GPIOB_PCLK_EN()		( RCC->AHB1ENR |= (1 << 1) ) /* GPIOB peripheral clock enabled */
#define GPIOC_PCLK_EN()		( RCC->AHB1ENR |= (1 << 2) ) /* GPIOC peripheral clock enabled */
#define GPIOD_PCLK_EN()		( RCC->AHB1ENR |= (1 << 3) ) /* GPIOD peripheral clock enabled */
#define GPIOE_PCLK_EN()		( RCC->AHB1ENR |= (1 << 4) ) /* GPIOE peripheral clock enabled */
#define GPIOF_PCLK_EN()		( RCC->AHB1ENR |= (1 << 5) ) /* GPIOF peripheral clock enabled */
#define GPIOG_PCLK_EN()		( RCC->AHB1ENR |= (1 << 6) ) /* GPIOG peripheral clock enabled */
#define GPIOH_PCLK_EN()		( RCC->AHB1ENR |= (1 << 7) ) /* GPIOH peripheral clock enabled */


/* ============ SPIx peripherals  ============ */
#define SPI1_PCLK_EN()      ( RCC->APB2ENR |= (1 << RCC_APB2ENR_SPI1EN))
#define SPI4_PCLK_EN()      ( RCC->APB2ENR |= (1 << RCC_APB2ENR_SPI4EN))
#define SPI2_PCLK_EN()      ( RCC->APB1ENR |= (1 << RCC_APB1ENR_SPI2EN))
#define SPI3_PCLK_EN()      ( RCC->APB1ENR |= (1 << RCC_APB1ENR_SPI3EN))

#define SPI1_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << RCC_APB2ENR_SPI1EN))
#define SPI4_PCLK_DI()      ( RCC->APB2ENR &= ~(1 << RCC_APB2ENR_SPI4EN))
#define SPI2_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << RCC_APB1ENR_SPI2EN))
#define SPI3_PCLK_DI()      ( RCC->APB1ENR &= ~(1 << RCC_APB1ENR_SPI3EN))



/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ================================================================ */
/* ================================================================ */

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



#endif
