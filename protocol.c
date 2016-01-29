#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "protocol.h"

/**
 * Pack an IDTech payload into the appropriate protocol frame for sending over
 * either USB or serial.
 *
 * Args:
 * src - Pointer to source buffer with payload data
 * dest - Pointer to a pointer to receive packed data. Memory will be allocated for this, and
 * must be free'd later.
 * length - Length of payload.
 *
 * Return:
 * Length of packed payload.
 *
 */
uint16_t pack_payload(uint8_t *src, uint8_t **dest, unsigned int length)
{

    // Structure of IDTech's payload:
    // STX (always 0x02)
    // Length LSB
    // Length MSB
    // Payload bytes
    // LRC
    // Checksum
    // ETX (always 0x03)

    // payload plus extras (STX, length, LRC, checksum, ETX)
    uint16_t total_length = length + 6;
    
    // Calculate LRC and checksum
    uint8_t checksum = 0;
    uint8_t lrc = 0;
    for (int i = 0; i < length; i++) 
    {
        lrc ^= src[i];
        checksum += src[i];
    }

    // Allocate total payload
    *dest = (uint8_t *) malloc(total_length);

    **dest = STX;
    *(*dest + 1) = GET_LSB(length);
    *(*dest + 2) = GET_MSB(length);
    memcpy((*dest + 3), src, length);

    *(*dest + (3 + length))  = lrc;
    *(*dest + (4 + length)) = checksum;
    *(*dest + (5 + length)) = ETX; 

    return total_length;
}

uint8_t *unpack_payload(uint8_t *src, unsigned int length)
{

    uint16_t payload_length = length - 6;

    // Allocate for payload size
    


}
