#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

#define STX         0x02
#define ETX         0x03

// Get LSB and MSB from a 16-bit word
#define LSB(x)  x & 0xFF
#define MSB(x)  x & ~0xFF

// Assemble a 16-bit word from two bytes
#define WORD(l, m)    l + (m << 8)

uint16_t pack_payload(uint8_t *, uint8_t **, unsigned int);

#endif



