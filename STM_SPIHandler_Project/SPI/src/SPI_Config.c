#define PORTA 1
#define PORTB 2
#define PORTC 3


#define PIN0 0
#define PIN0 1
#define PIN0 2
#define PIN0 3
#define PIN0 4
#define PIN0 5
#define PIN0 6
#define PIN0 7
#define PIN0 8
#define PIN0 9
#define PIN0 10
#define PIN0 11
#define PIN0 12
#define PIN0 13
#define PIN0 14
#define PIN0 15

void GPIO_SPI_SlaveSelect (uint8 port, uint8 pin){
  
// Set PIN to  General purpose output mode

  
switch(port)
		{
		case PORTA:
	GPIOA->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOA->MODER |=  (0x3UL << ((pin*2)U));
      break;
		case PORTB:
	GPIOB->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOB->MODER |=  (0x3UL << ((pin*2)U));
			break;
		case PORTC:
	GPIOC->MODER &= ~( (0x3UL << ((pin*2)U)) | ( 0x3UL << (((pin*2)+1)U) ) );
	GPIOC->MODER |=  (0x3UL << ((pin*2)U));
			break;
    }


}

