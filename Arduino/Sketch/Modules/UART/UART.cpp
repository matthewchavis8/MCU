#include "UART.h"
#include <avr/io.h>
#include <stddef.h>

#define BAUD_RATE  115200

static inline uint16_t ubrrFromBaud(uint32_t baud) {
  return static_cast<uint32_t>((BAUD_RATE / (8UL * baud)) - 1UL);
}

void uartInit(uint32_t baud) {
  UCSR0A = (1 << U2X0);

  uint16_t ubrr = ubrrFromBaud(baud);
  UBRR0H = static_cast<uint8_t>(ubrr >> 8);
  UBRR0L = static_cast<uint8_t>(ubrr & 0xFF);

  UCSR0B = (1 << TXEN0);
}

void uartPutCh(char c) {
  while (!(UCSR0A & (1 << UDRE0))) {}

  UDR0 = static_cast<uint8_t>(c);
}

template <size_t N>
void print(const char (&str)[N]) {
  static_assert(N > 0, "NULL String");
  static_assert(str[N - 1], "String must be null terminated");

  for (auto ch : str)
    uartPutCh(ch);
}
