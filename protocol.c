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
    *(*dest + LEN_LSB_IDX) = LSB(length);
    *(*dest + LEN_MSB_IDX) = MSB(length);
    memcpy((*dest + PAYLOAD_IDX), src, length);

    *(*dest + LRC_IDX(length))  = lrc;
    *(*dest + CHKSUM_IDX(length)) = checksum;
    *(*dest + ETX_IDX(length)) = ETX; 

    return total_length;
}

/**
 * Extract a payload from a protocol frame.
 *
 * Args:
 * src - Source protocol frame
 * payload - Destination location to extract payload to. Memory for this
 * will be allocated and must be free'd later.
 * 
 * Returns:
 * Length of unpacked payload.
 *
 */
uint16_t unpack_payload(uint8_t *src, uint8_t **payload)
{

    uint16_t payload_length = WORD(src[LEN_LSB_IDX], src[LEN_MSB_IDX]);

    // Allocate for payload size
    *payload = malloc(payload_length);

    // Copy
    memcpy(*payload, src + PAYLOAD_IDX, payload_length);

    return payload_length;
}
