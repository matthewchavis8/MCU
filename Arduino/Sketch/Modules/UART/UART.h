
#ifndef __PRINT_H__
#define __PRINT_H__

#define BAUD_RATE  115200

#include <stdint.h>
#include <avr/io.h>

void uartInit(uint32_t baud);
void uartPutCh(char c);

void print(const char* str);

#endif // !__PRINT_H__
