#include "stddef.h"
#include "../Digital/write.h"
#include "interrupt.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>


static uint8_t pin { MAKE_PIN(PORT_D, 2) };

volatile uint8_t ButtonInt0::s_pressed{};
uint8_t ButtonInt0::s_pin { pin };

void ButtonInt0::init() noexcept {
  pinMode(s_pin, PinMode::InputPullup);

  // Interrupt triggered on falling edge
  EICRA &= ~(1 << ISC00);
  EICRA |=  (1 << ISC01);

  // Clear pending
  EIFR |= (1 << INTF0);
  EIMSK |= (1 << INT0);

  // Clear Event Flag
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    s_pressed = 0;
  }
}

[[nodiscard]] bool ButtonInt0::take() noexcept {
  uint8_t state {};
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    state = ButtonInt0::s_pressed;
    ButtonInt0::s_pressed = 0;
  }
  return state != 0;

  return state != 0;
}

ISR(INT0_vect) {
  ButtonInt0::isrOnPress();
}
