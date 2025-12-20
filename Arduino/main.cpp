#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>
#include "Modules/Hal/write.h"


int main() {
  constexpr uint8_t ledPins[] = { PB0, PB1, PB2, PB3, PB4, PB5 };
  for (auto pin : ledPins)
    DDRB |= (1 << pin);

  for (;;) {
    for (auto pin : ledPins) {
      digitalWrite(pin, true);
      _delay_ms(100);
      digitalWrite(pin, false);
      _delay_ms(100);
    }
  }
}
