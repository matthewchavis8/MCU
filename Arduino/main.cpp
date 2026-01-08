#include "Modules/Hal/Digital/write.h"
#include "Modules/Hal/Interrupt/interrupt.h"
#include "stddef.h"
#include <util/delay.h>


int main() {
  constexpr uint8_t pinB0 { MAKE_PIN(PORT_B, 0) };
  constexpr uint8_t pinD2 { MAKE_PIN(PORT_D, 2) };

  pinMode(pinB0, PinMode::Output);
  pinMode(pinD2, PinMode::InputPullup);


  for (;;) {
    bool btnState { digitalRead(pinD2) };

    if (!btnState) {
      digitalWrite(pinB0, true);
      _delay_ms(100);
      digitalWrite(pinB0, false);
      _delay_ms(100);
    }

    _delay_ms(100);
  }
}
