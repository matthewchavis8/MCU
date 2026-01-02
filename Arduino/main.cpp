#include <avr/io.h>
#include <stddef.h>
#include <util/delay.h>
#include "Modules/Hal/write.h"

int main() {
  pinMode(PB0, PinMode::Output);
  
  while (true) {
    digitalWrite(PB0, true);
    _delay_ms(300);
    digitalWrite(PB0, false);
    _delay_ms(300);
  }
}
