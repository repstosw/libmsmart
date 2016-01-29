#pragma once

#include <stdint.h>

// Start and end bytes
#define STX         0x02
#define ETX         0x03

// Buffer indices
#define STX_IDX         0
#define LEN_LSB_IDX     1
#define LEN_MSB_IDX     2
#define PAYLOAD_IDX     3
// Indices based upon the payload length
#define LRC_IDX(x)      x + 3
#define CHKSUM_IDX(x)   x + 4
#define ETX_IDX         x + 5


// Get LSB and MSB from a 16-bit word
#define LSB(x)  x & 0xFF
#define MSB(x)  x & ~0xFF

// Assemble a 16-bit word from two bytes
#define WORD(l, m)    l + (m << 8)

uint16_t pack_payload(uint8_t *, uint8_t **, unsigned int);

