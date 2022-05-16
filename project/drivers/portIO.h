#ifndef PORT_IO
#define PORT_IO
#include "../utility/typedefs.h"

uint8_t b_in(uint16_t port);
void b_out(uint16_t port, uint8_t data);
uint16_t w_in(uint8_t port);
void w_out(uint16_t port, uint16_t data);

#endif