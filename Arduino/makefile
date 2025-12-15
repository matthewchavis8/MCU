
Source         := main.cpp
ModuleName     := main
MCU            := atmega328p
Flags  				 := -Os -Wall -Wextra -Wunused -Werror -W -fdata-sections
DF_CPU         := 16000000
BAUD_RATE      := 115200
PORT 					 := /dev/ttyACM0

MODULES_DIR := Sketch/Modules

LINK_MODULES ?= UART

INCLUDES := $(foreach m,$(LINK_MODULES),-I$(MODULES_DIR)/$(m))
LIBS     := $(foreach m,$(LINK_MODULES),$(MODULES_DIR)/$(m)/lib$(m).a)

modules:
	@for m in $(LINK_MODULES); do \
		$(MAKE) -C $(MODULES_DIR)/$$m; \
	done

default: modules
	avr-g++ $(Flags) -mmcu=$(MCU) -DF_CPU=$(DF_CPU) $(INCLUDES) \
		-c $(Source) -o $(ModuleName).o
	avr-g++ -mmcu=$(MCU) $(ModuleName).o $(LIBS) -o $(ModuleName).elf
	avr-objcopy -O ihex -R .eeprom $(ModuleName).elf $(ModuleName).hex

flash: default
	avrdude -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD_RATE) -D \
		-U flash:w:$(ModuleName).hex:i

clean:
	rm -rf *.o *.elf *.hex
