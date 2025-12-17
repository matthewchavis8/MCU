#include "UART.h"
#include <avr/io.h>
#include <stddef.h>

#ifndef F_CPU
#  error "Define F_CPU (e.g. -DF_CPU=16000000UL)"
#endif

void Uart::uartInit(uint32_t baud) {
  auto ubrrFromBaud = [](uint32_t baud) {
     return static_cast<uint16_t>((F_CPU / (8UL * baud)) - 1UL);
  };

  UCSR0A = (1 << U2X0);

  uint16_t ubrr = ubrrFromBaud(baud);
  UBRR0H = static_cast<uint8_t>(ubrr >> 8);
  UBRR0L = static_cast<uint8_t>(ubrr & 0xFF);
 
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
  UCSR0B = (1 << TXEN0);
}
