#ifndef __WRITE_H__
#define __WRITE_H__

#include <avr/io.h>

static inline void digitalWrite(const uint8_t pin, bool isHigh) noexcept {
  isHigh ? PORTB |= (1 << pin) : PORTB &= ~(1 << pin);
}

[[nodiscard]] static inline bool digitalRead(uint8_t pin) noexcept {
  return (PINB & (1 << pin)) != 1;
}

#endif // !__WRITE_H__
