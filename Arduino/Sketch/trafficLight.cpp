// Turning Port B pin 0 to output
#include <util/delay.h>
#include <avr/io.h>

int main() {

  for (;;) {
    // Turning the Red LED on PORT B pin 0 on
    DDRB |= (1 << PB0);
    PORTB ^= (1 << PB0);
    _delay_ms(1000);
    DDRB &= ~(1 << PB0);

    // Turning the Yellow LED on PORT D pin 4 on
    DDRD |= (1 << PD4);
    PORTD ^= (1 << PD4);
    _delay_ms(200);
    DDRB &= ~(1 << PD4);

    // Turning the Green LED on PORT D pin 3 on
    DDRD |= (1 << PD3);
    PORTD ^= (1 << PD3);
    _delay_ms(2000);
    DDRB &= ~(1 << PD3);
  }

  return 0;
}
