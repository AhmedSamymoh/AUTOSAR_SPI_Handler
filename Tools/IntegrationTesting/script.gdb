file C:/Users/ahmed/Desktop/AUTOSAR/SPIHandler/AUTOSAR_SPI_Handler/STM_SPIHandler_Project/Debug/SPIHandler_Project.elf
target extended-remote :3333
monitor reset halt
break Spi.c:625
continue
print (SPI1->CR1 >> 6) & 1