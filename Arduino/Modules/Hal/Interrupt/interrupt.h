#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__
#include "stddef.h"
#include <avr/io.h>


class ButtonInt0 {
  private:
    static volatile uint8_t s_pressed;
    static uint8_t s_pin;

    friend void INT0_vect_handler() noexcept;

  public:
    void init() noexcept;
    [[nodiscard]] bool take() noexcept;

    // Helpers
    static inline void enable() noexcept  { EIMSK |=  (1 << INT0); }
    static inline void disable() noexcept { EIMSK &= ~(1 << INT0); }

    // Enable Flag
    static inline void isrOnPress() noexcept { s_pressed = 1; }
};


#endif // !__INTERRUPT_H__
