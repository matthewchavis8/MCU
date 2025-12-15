
SOURCE        := UART.cpp
OBJFILES      := UART.o
LIBRARY       := libUART.a
Flags  				:= -Os -Wall -Wextra -Wunused -Werror -W -fdata-sections

MCU           := atmega328p
DF_CPU        := 16000000
BAUD_RATE     := 115200

$(LIBRARY): $(OBJFILES)
	avr-ar rcs $@ $^

$(OBJFILES): $(SOURCE)
	avr-g++ $(Flags) -mmcu=$(MCU) -DF_CPU=$(DF_CPU) -c $< -o $@
	

clean:
	rm $(OBJFILES) $(LIBRARY)
