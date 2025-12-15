#include "Sketch/Modules/UART/UART.h"
#include <util/delay.h>

int main() {

  uartInit(115200);

  while (1) {
    print("Hello World\n");
    _delay_ms(1000);
  }
}
