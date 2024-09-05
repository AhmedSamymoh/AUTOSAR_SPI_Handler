C = arm-none-eabi-gcc
OBJCOPY = arm-none-eabi-objcopy
OBJDUMP = arm-none-eabi-objdump
SIZE = arm-none-eabi-size

# Directories
 SRC_DIR = Src
 INC_DIR = Inc
 OBJ_DIR = Debug/obj
 BIN_DIR = Debug/bin

SOURCES = $(wildcard $(SRC_DIR)/*.c) $(wildcard SPI/src/*.c) $(wildcard AUTOSAR/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SOURCES))


CFLAGS = -I$(INC_DIR) -I$(SRC_DIR) -mcpu=cortex-m4 -mthumb -O0 -g3 -ffunction-sections -fdata-sections
LDFLAGS = -T STM32F446RETX_FLASH.ld -nostartfiles -Wl,--gc-sections

all: $(BIN_DIR)/SPIHandler_Project.elf


$(BIN_DIR)/SPIHandler_Project.elf: $(OBJECTS)
	    $(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	    $(CC) $(CFLAGS) -c $< -o $@

clean:
	    rm -f $(OBJ_DIR)/*.o $(BIN_DIR)/*.elf $(BIN_DIR)/*.bin

size: $(BIN_DIR)/SPIHandler_Project.elf
	    $(SIZE) $<

.PHONY: all clean size
