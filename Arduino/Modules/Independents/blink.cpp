#include <avr/io.h>
#include <util/delay.h>


int main() {
  // Setting the Data Direction Register for PORT b pin 0 to output
  DDRB |= (1 << DDB0);

  for (;;) {
    PORTB ^= (1 << PB0);
    _delay_ms(1000);
  }
}
