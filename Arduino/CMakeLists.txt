cmake_minimum_required(VERSION 3.20)
project(Arduino_Baremetal CXX)

set(MCU atmega328p)
set(F_CPU 16000000UL)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(AVRDUDE_PORT "/dev/ttyACM0")
set(AVRDUDE_BAUD "115200")

add_compile_options(
  -mmcu=${MCU}
  -DF_CPU=${F_CPU}
  -Os -Wall -Wextra -Werror
  -ffunction-sections -fdata-sections
  -fno-exceptions -fno-rtti
)

add_link_options(
  -mmcu=${MCU}
  -Wl,--gc-sections
)

add_subdirectory(Modules/UART)
add_subdirectory(Modules/Hal/Interrupt)

add_executable(main.elf
  main.cpp
)

# Link any static Libs
target_link_libraries(main.elf
 PRIVATE
 UART
 Interrupt
)

# Flash Stuff is here
add_custom_command(TARGET main.elf POST_BUILD
  COMMAND avr-objcopy -O ihex -R .eeprom
          $<TARGET_FILE:main.elf> ${CMAKE_CURRENT_BINARY_DIR}/main.hex
  BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/main.hex
)


add_custom_target(flash
  COMMAND avrdude -v -p ${MCU} -c arduino -P ${AVRDUDE_PORT} -b ${AVRDUDE_BAUD} -D
          -U flash:w:${CMAKE_CURRENT_BINARY_DIR}/main.hex:i
  DEPENDS main.elf
  USES_TERMINAL
)

