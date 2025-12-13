
Source         := Sketch/trafficLight.cpp
ModuleName     := main
MCU            := atmega328p
Flags  				 := -Os -Wall -Wextra -Wunused -Werror -W -fdata-sections
DF_CPU         := 16000000
BAUD_RATE      := 115200
PORT 					 := /dev/ttyACM0

default:
	avr-g++ $(Flags) -mmcu=$(MCU) -DF_CPU=$(DF_CPU) 					         \
		-c $(Source) -o $(ModuleName).o                  				         
	avr-g++ -mmcu=$(MCU) $(ModuleName).o -o $(ModuleName).elf          
	avr-objcopy -O ihex -R .eeprom $(ModuleName).elf $(ModuleName).hex

flash:
	avrdude -v -p $(MCU) -c arduino -P $(PORT) -b $(BAUD_RATE) -D \
		-U flash:w:main.hex:i

clean:
	rm -rf *.o *.elf *.hex
