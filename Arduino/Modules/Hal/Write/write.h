#ifndef __WRITE_H__
#define __WRITE_H__

#include <avr/io.h>
#include <stdint.h>

enum : uint8_t { PORT_B, PORT_C, PORT_D };

// @brief clears the bits and only keeps the bit idx
// Tells us which wiill later reveal which port the pin sits in
constexpr uint8_t PIN_BIT(uint8_t pin)  { return pin & 7; }
// @brief detects the pin's Port
constexpr uint8_t PIN_PORT(uint8_t pin) { return pin >> 3; }

constexpr uint8_t MAKE_PIN(uint8_t portId, uint8_t bit) { return (portId << 3) | (bit & 7); }

enum class PinMode : uint8_t { Input, InputPullup, Output };

static inline volatile uint8_t* ddrReg(uint8_t pin) noexcept {
  uint8_t portId { PIN_PORT(pin) };

  switch (portId) { 
    case PORT_B: return &DDRB; 
    case PORT_C: return &DDRC; 
    case PORT_D: return &DDRD; 
    default: return nullptr;
  }
}

static inline volatile uint8_t* outputReg(uint8_t pin) noexcept {
  uint8_t portId { PIN_PORT(pin) };

  switch (portId) { 
    case PORT_B: return &PORTB; 
    case PORT_C: return &PORTC; 
    case PORT_D: return &PORTD;
    default: return nullptr; 
  }
}

static inline volatile uint8_t* readReg(uint8_t pin) noexcept {
  uint8_t portId { PIN_PORT(pin) };

  switch (portId) {
    case PORT_B: return &PINB;
    case PORT_C: return &PINC;
    case PORT_D: return &PIND;
    default: return nullptr;
  }
}

static inline void pinMode(uint8_t pin, PinMode mode) noexcept {
  auto* ddr  = ddrReg(pin);
  auto* port = outputReg(pin);

  if (!ddr || !port) return;

  uint8_t mask = (1u << PIN_BIT(pin));

  switch (mode) {
    case PinMode::Output: 
      *ddr |= mask; 
      break;
    case PinMode::Input:
      *ddr &= ~mask;
      *port &= ~mask;
      break;
    case PinMode::InputPullup: 
      *ddr &= ~mask;
      *port |= mask;
      break;
  }
}

static inline void digitalWrite(uint8_t pin, bool high) noexcept {
  auto* port = outputReg(pin);
  if (!port)
    return;

  uint8_t mask = (1u << PIN_BIT(pin));

  if (high) {
    *port |= mask;
    return;
  }
  
  *port &= ~mask;
}

[[nodiscard]] static inline bool digitalRead(uint8_t pin) noexcept {
  auto* in = readReg(pin); 
  
  if (!in)
    return false;

  uint8_t mask = (1u << PIN_BIT(pin));
  return (*in & mask) != 0;
}

#endif // !__WRITE_H__
