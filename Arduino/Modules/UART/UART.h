#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include <avr/io.h>
#include <stddef.h>

class Uart {
private:
  void uartInit(uint32_t baud);
  
public:
  explicit Uart(uint32_t baud) { uartInit(baud); }

  Uart(Uart&) = delete;
  Uart& operator=(Uart&) = delete;

  static inline void putCh(char c) {
      // Make sure its clear idk something it tweaks
      while (!(UCSR0A & (1 << UDRE0))) {}
      UDR0 = static_cast<uint8_t>(c);
  }

  static inline void print(const char* str) noexcept {
    for (; *str; ++str) {
      if (*str == '\n')
        putCh('\r');
      putCh(*str);
    }
  }
};

#endif // !__UART_H__
