#include "Modules/KeyPad/keyPad.h"
#include "UART.h"
#include <util/delay.h>

constexpr uint8_t PB0_ENC { MAKE_PIN(PORT_B, 0) };
constexpr uint8_t PB1_ENC { MAKE_PIN(PORT_B, 1) };
constexpr uint8_t PD2_ENC { MAKE_PIN(PORT_D, 2) };
constexpr uint8_t PD3_ENC { MAKE_PIN(PORT_D, 3) };
constexpr uint8_t PD4_ENC { MAKE_PIN(PORT_D, 4) };
constexpr uint8_t PD5_ENC { MAKE_PIN(PORT_D, 5) };
constexpr uint8_t PD6_ENC { MAKE_PIN(PORT_D, 6) };
constexpr uint8_t PD7_ENC { MAKE_PIN(PORT_D, 7) };

static constexpr char keys[4][4] {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'},
};

static constexpr uint8_t rowPins[4] { PB1_ENC, PB0_ENC, PD7_ENC, PD6_ENC };
static constexpr uint8_t colPins[4] { PD5_ENC, PD4_ENC, PD3_ENC, PD2_ENC };

int main() {
  KeyPad<4, 4> keyPad(keys, rowPins, colPins);
  Uart uart(115200);

  constexpr char passWrd[5] = "1234";

  for (;;) {
    uint8_t tries{};
    bool isCorrect { false };


    while (tries < 4 || !isCorrect) {
      char keysEntered[5] = {};
      uint8_t idx{};
      uart.print("Please Enter passKey\n");
      
      while (idx < 4) {
        char key = keyPad.getKey();

        if (key == '\0')
          continue;

         uart.putCh(key);
         keysEntered[idx++] = key;
         keysEntered[idx] = '\0';
      }

      bool match { true };
      for (uint8_t i{}; i < 4; i++) {
        if (keysEntered[i] != passWrd[i]) {
          match = false;
          break;
        }
      }

      if (match) {
        uart.print("\nCongrats you have entered the apartment\n");
        isCorrect = true;
      } else {
        uart.print("\nYou entered the wrong password\n");
        tries++;
      }

      tries++;
    }

    if (!isCorrect)
      uart.print("exceeded attempts\n");
  }
}
