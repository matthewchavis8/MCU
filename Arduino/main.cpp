#include "Modules/Hal/Digital/write.h"
#include "Modules/Hal/Interrupt/interrupt.h"
#include "stddef.h"
#include <avr/interrupt.h>
#include <util/delay.h>

/*
 *
 * Learning a interrupt for the first time
 * */

int main() {
  constexpr uint8_t pinB0 { MAKE_PIN(PORT_B, 0) };
  constexpr uint8_t pinD2 { MAKE_PIN(PORT_D, 2) };

  pinMode(pinB0, PinMode::Output);
  pinMode(pinD2, PinMode::InputPullup);

  ButtonInt0 btn;
  btn.init();
  sei(); // Global interrupts on

  for (;;) {
    if (btn.take()) {
      digitalWrite(pinB0, !digitalRead(pinB0));
    }
  }
}
