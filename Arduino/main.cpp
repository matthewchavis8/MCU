#include "Sketch/Modules/UART/UART.h"

int main() {

  uartInit(115200);
  print("Hello World\n");

  while (1) {}
}
