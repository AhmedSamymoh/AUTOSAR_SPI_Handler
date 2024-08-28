
void GPIO_SPI_SlaveSelect (uint8 port, uint8 pin){
  
switch(port)
		{
		case PORTA:
			// Set PIN to  General purpose output mode
	GPIOA->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOA->MODER |=  (1 << ((pin*2)U));
			
	// Set PIN to  medium speed mode
	GPIOA->OSPEEDR |= (1<< (pin*2)U);

	// Set PIN to  no pull or push
	GPIOA->PUPDR &= ~( (0x3UL << ((pin*2)U)) );
	
      break;
		case PORTB:
			// Set PIN to  General purpose output mode
	GPIOB->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOB->MODER |=  (0x3UL << ((pin*2)U));


			// Set PIN to  medium speed mode
	GPIOB->OSPEEDR |= (1<< (pin*2)U);
			break;


			
		case PORTC:
			// Set PIN to  General purpose output mode
	GPIOC->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOC->MODER |=  (0x3UL << ((pin*2)U));
			
			// Set PIN to  medium speed mode
	GPIOC->OSPEEDR |= (1<< (pin*2)U);
			break;

			
			case PORTD:
			// Set PIN to  General purpose output mode
	GPIOD->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOD->MODER |=  (0x3UL << ((pin*2)U));
			
			// Set PIN to  medium speed mode
	GPIOD->OSPEEDR |= (1<< (pin*2)U);
			break;
			case PORTE:
			// Set PIN to  General purpose output mode
	GPIOE->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOE->MODER |=  (0x3UL << ((pin*2)U));
			
			// Set PIN to  medium speed mode
	GPIOE->OSPEEDR |= (1<< (pin*2)U);
			break;
			case PORTF:
			// Set PIN to  General purpose output mode
	GPIOF->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOF->MODER |=  (0x3UL << ((pin*2)U));
			
			// Set PIN to  medium speed mode
	GPIOF->OSPEEDR |= (1<< (pin*2)U);
			break;
				case PORTG:
			// Set PIN to  General purpose output mode
	GPIOG->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOG->MODER |=  (0x3UL << ((pin*2)U));
			
			// Set PIN to  medium speed mode
	GPIOG->OSPEEDR |= (1<< (pin*2)U);
			break;
    }


}

