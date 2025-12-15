
#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>
#include <avr/io.h>
#include <stddef.h>

void uartInit(uint32_t baud);
void uartPutCh(char c);


template <size_t N>
inline void print(const char (&str)[N]) {

  for (auto ch : str)
    uartPutCh(ch);
}

#endif // !__UART_H__
