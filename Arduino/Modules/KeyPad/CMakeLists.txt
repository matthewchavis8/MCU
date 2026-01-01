add_library(KeyPad
  STATIC
  keyPad.cpp
)

target_include_directories(KeyPad
  PUBLIC 
  ${CMAKE_CURRENT_SOURCE_DIR}
)
