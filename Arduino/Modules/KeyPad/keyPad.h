#ifdef __KEYPAD_H__
#define __KEYPAD_H__

#include "stddef.h"
#include "../Hal/write.h"

template<uint8_t ROWS, uint8_t COLS>
class KeyPad {
 private:
  const char        (&m_keypads)[ROWS][COLS]
  const uint8_t     (&m_rowPins)[ROWS]
  const uint8_t     (&m_colPins)[COLS]

  
 public:
  // Constructs the object + sets up everything
  explicit KeyPad(const char (&KeyPad)[ROWS][COLS],
                    const uint8_t (&rowPins)[ROWS], 
                    const uint8_t (&colPins)[COLS])
                    : m_keypads { KeyPad }
                    , m_rowPins { rowPins }
                    , m_colPins { colPins }
  {
    // Setting Row Pins to low
    for (uint8_t pin : m_rowpins) {
      pinmode(pin, true);
      digitalwrite(pin, false);
    }
    // Set colums Pin
    for (uint8_t pin : m_colPins) {
    pinmode(pin, true);
  }

  KeyPad& operator=(KeyPad&) = delete;
  KeyPad(KeyPad&) = delete;

  // @brief Returns the key that was pressed
  [[nodiscard]] char getKey() const noexcept;
};

#endif // __KEYPAD_H__
