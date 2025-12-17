add_library(UART
  STATIC
  UART.cpp
)

target_include_directories(UART
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
