#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>
#include "../Hal/write.h"

int main() {
   
  // Flashing Multiple LED
  // Turning Pins to Output
  constexpr uint8_t ledPins[] = { PB1, PB2, PB3, PB4, PB5 };
  for (auto pin : ledPins)
    DDRB |= (1 << pin);

  constexpr uint8_t btnPin = PB0;
  PORTB |= (1 << btnPin);
  
  while (true) {
    bool btnState = digitalRead(btnPin);
    
    if (btnState) {
      for (auto pin : ledPins) {

        digitalWrite(pin, true);
        _delay_ms(30);

        digitalWrite(pin, false);
        _delay_ms(30);
      }
    }
    _delay_ms(100);
  }
}
