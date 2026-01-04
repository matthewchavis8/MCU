#ifndef __KEYPAD_H__
#define __KEYPAD_H__

#include "stddef.h"
#include "../Hal/write.h"
#include <util/delay.h>

template <uint8_t ROW, uint8_t COL>
class KeyPad {
 private:
  const char        (&m_keypads)[ROW][COL];
  const uint8_t     (&m_rowPins)[ROW];
  const uint8_t     (&m_colPins)[COL];

  void setAllRowsLow() {
    for (uint8_t pin : m_rowPins)
      digitalWrite(pin, false);
  }

  [[nodiscard]] int8_t detectActiveColumn() noexcept {
     setAllRowsLow();
     _delay_us(1);

    for (int8_t col{}; col < COL; col++) {
      // If column are all set to LOW then we found the active one
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

    for (uint8_t r = 0; r < ROW; r++) {
      setAllRowsLow();
      digitalWrite(m_rowPins[r], true);

      // Okay double check delay is defintly needed here lol
      _delay_us(1);

      // If pin is HIGH then we found key pressed
      if (digitalRead(m_colPins[col])) {
        setAllRowsLow();
        return m_keypads[r][col];
      }
    }

    return '\0';
  }
  
 public:
  // Constructs the object and intialize the keypad for reading
  explicit KeyPad(
    const char (&KeyPad)[ROW][COL],
    const uint8_t (&rowPins)[ROW],
    const uint8_t (&colPins)[COL])
      : m_keypads { KeyPad }
      , m_rowPins { rowPins }
      , m_colPins { colPins }
  {
    // Setting Row Pins to low
    for (uint8_t pin{}; pin < ROW; pin++) {
      pinMode(m_rowPins[pin], PinMode::Output);
      digitalWrite(m_rowPins[pin], false);
    }

    // Set colums Pin to PullUp
    for (uint8_t pin{}; pin < COL; pin++) {
      pinMode(m_colPins[pin], PinMode::InputPullup);
    }
  }

  KeyPad& operator=(KeyPad&) = delete;
  KeyPad(KeyPad&) = delete;

  // @brief Returns the key that was pressed
  [[nodiscard]] char getKey() noexcept {
    char key { scanOnce() };
    if (key == '\0')
      return '\0';

    // Delay until scanOnce finishes above
    while (scanOnce() != '\0') { _delay_us(1); }

    return key;
  }
};

#endif // __KEYPAD_H__
