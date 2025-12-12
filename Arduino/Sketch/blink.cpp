#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void flashPin(uint8_t pin) {
  DDRB |= (1 << pin);

  for (;;) {
    // PORT is hard coded this is mapped to some MMIO
    PORTB ^= (1 << pin);
    _delay_ms(1000);
  }
}

int main() {
  // Setting the Data Direction Register for PORT b pin 5 to output
  flashPin(PB3);
}
