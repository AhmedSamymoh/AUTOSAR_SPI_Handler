/**
 * @file Spi_Cfg.c
 * @author Ahmed Samy - Ahmed Wagdy - Rana Mohamed - Mohamed Farouk
 * @brief  Serial Perpheral Interface Configuration Source file
 * @version info : @ module : SPI Handler/Driver @ Platform : stm32f446re @ AUTOSAR_version: R23-11
 * @date 2024-08-25
 *
 * @copyright Brightskies Copyright (c) 2024
 *
 */



/********************************************** Section : Includes ********************************************/

#include "../../AUTOSAR/Std_Types.h"
#include "../inc/Spi_Cfg.h"     
#include "../inc/Spi.h" 

#include <stdint.h>




/**
 * @brief system initialization for mcu clock
 *  using RCC_CR register for using HSI clock source
 */
void System_Init(void){

	RCC->CFGR = 0x00000000;
	RCC->CR &= 0xFEF6FFFF;
	RCC->CR |= 1;
	while(READ_BIT((RCC->CR), 0));
}


/**
 * @brief 
 * 
 * @param port 
 * @param pin 
 */
void GPIO_SPI_SlaveSelect (uint8 port, uint8 pin){

	switch(port){
			case PORTA:
			
				// Set PIN to  General purpose output mode
				GPIOA->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOA->MODER |=  (1 << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOA->OSPEEDR |= (1<< (pin*2));

				// Set PIN to  no pull or push
				GPIOA->PUPDR &= ~( (0x3UL << ((pin*2))) );
			break;


			case PORTB:
				// Set PIN to  General purpose output mode
				GPIOB->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOB->MODER |=  (0x3UL << ((pin*2)));
				// Set PIN to  medium speed mode
				GPIOB->OSPEEDR |= (1<< (pin*2));
				// Set PIN to  no pull or push
				GPIOA->PUPDR &= ~( (0x3UL << ((pin*2))) );
				break;


				
			case PORTC:
				// Set PIN to  General purpose output mode
				GPIOC->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOC->MODER |=  (0x3UL << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOC->OSPEEDR |= (1<< (pin*2));
				break;

				
			case PORTD:
				// Set PIN to  General purpose output mode
				GPIOD->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOD->MODER |=  (0x3UL << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOD->OSPEEDR |= (1<< (pin*2));
				break;


			case PORTE:
				// Set PIN to  General purpose output mode
				GPIOE->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOE->MODER |=  (0x3UL << ((pin*2)));
						
				// Set PIN to  medium speed mode
				GPIOE->OSPEEDR |= (1<< (pin*2));
				break;


			case PORTF:
				// Set PIN to  General purpose output mode
				GPIOF->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOF->MODER |=  (0x3UL << ((pin*2)));
				
				// Set PIN to  medium speed mode
				GPIOF->OSPEEDR |= (1<< (pin*2));
				break;



			case PORTG:
				// Set PIN to  General purpose output mode
				GPIOG->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOG->MODER |=  (0x3UL << ((pin*2)));

				// Set PIN to  medium speed mode
				GPIOG->OSPEEDR |= (1<< (pin*2));
				break;


			case PORTH:
				// Set PIN to  General purpose output mode
				GPIOH->MODER &= ~( (0x3UL << ((pin*2))) | ( 0x3UL << (((pin*2)+1)) ) );
				GPIOH->MODER |=  (0x3UL << ((pin*2)));
				
				// Set PIN to  medium speed mode
				GPIOH->OSPEEDR |= (1<< (pin*2));
				break;
	}

}
