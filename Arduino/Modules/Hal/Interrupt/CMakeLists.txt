add_library(
  Interrupt
  STATIC
  interrupt.cpp
)

target_include_directories(Interrupt
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
