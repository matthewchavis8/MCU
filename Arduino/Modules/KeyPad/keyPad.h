#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "stddef.h"
#include "../Hal/write.h"
#include <util/delay.h>

template<uint8_t ROWS, uint8_t COLS>
class KeyPad {
 private:
  const char        (&m_keypads)[ROWS][COLS];
  const uint8_t     (&m_rowPins)[ROWS];
  const uint8_t     (&m_colPins)[COLS];

  void setAllRowsLow() noexcept {
    for (uint8_t pin : m_rowPins)
      digitalWrite(pin, false);
  }

  [[nodiscard]] int8_t detectActiveColumn() noexcept {
     setAllRowsLow();
     _delay_us(5);

    for (int8_t col{}; col < COLS; col++) {
      if (!digitalRead(m_colPins[col]))
        return col;
    }

    return -1;
  }

  [[nodiscard]] char scanOnce() noexcept {
    int8_t col = detectActiveColumn();
    if (col < 0) return '\0';

    // confirm still active
    if (digitalRead(m_colPins[col])) return '\0';

    for (uint8_t r = 0; r < ROWS; r++) {
      setAllRowsLow();
      digitalWrite(m_rowPins[r], true);
      _delay_us(5);

      if (digitalRead(m_colPins[col])) {
        setAllRowsLow();
        return m_keypads[r][col];
      }
    }

    setAllRowsLow();
    return '\0';
  }
  
 public:
  // Constructs the object and intialize the keypad for reading
  explicit KeyPad(const char (&KeyPad)[ROWS][COLS], const uint8_t (&rowPins)[ROWS], const uint8_t (&colPins)[COLS])
  : m_keypads { KeyPad }
  , m_rowPins { rowPins }
  , m_colPins { colPins }
{
    // Setting Row Pins to low
    for (uint8_t pin : m_rowPins) {
      pinMode(pin, PinMode::Output);
      digitalWrite(pin, false);
    }

    // Set colums Pin to PullUp
    for (uint8_t pin : m_colPins) {
      pinMode(pin, PinMode::InputPullup);
    }
}

  KeyPad& operator=(KeyPad&) = delete;
  KeyPad(KeyPad&) = delete;

  // @brief Returns the key that was pressed
  [[nodiscard]] char getKey() noexcept {
    char k1 = scanOnce();
    if (k1 == '\0') return '\0';

    _delay_ms(20);                 // debounce time
    char k2 = scanOnce();
    if (k1 != k2) return '\0';

    while (scanOnce() != '\0') { _delay_ms(10); } // wait release
    _delay_ms(30);
    return k1;
  }
};

#endif // __KEYPAD_H__
