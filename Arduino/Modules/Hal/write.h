#ifndef __WRITE_H__
#define __WRITE_H__

#include <avr/io.h>

static inline void digitalWrite(const uint8_t pin, bool mode) {
  if (mode)
    PORTB |= (1 << pin);
  else 
    PORTB &= ~(1 << pin);
}

#endif // !__WRITE_H__
