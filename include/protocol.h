#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define STX         0x02
#define ETX         0x03

// this presumes a 16-bit word
#define GET_LSB(x)  x & 0xFF
#define GET_MSB(x)  x & ~0xFF

uint16_t pack_payload(uint8_t *, uint8_t **, unsigned int);

#endif



