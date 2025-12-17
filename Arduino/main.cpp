#include "Modules/UART/UART.h"
#include <util/delay.h>

int main() {


  Uart uart(115200);
  while (1) {
    uart.print("LOLLLL IS IT WORKING????\n");
    _delay_ms(1000);
  }
}
