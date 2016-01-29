// Tests for protocol packing/unpacking

#include "cutest.h"
#include "protocol.h"

void test_pack_payload(void)
{
    uint8_t payload[] = { 0x78, 0x46, 0x02 };
    uint8_t *result = NULL;
    unsigned int length = 3;

    uint16_t total_length;

    total_length = pack_payload(payload, &result, length);
    TEST_CHECK_(result != NULL, "Result doesn't point to anything");
    TEST_CHECK_(total_length == 9, "Incorrect length: %d", total_length);
    TEST_CHECK(result[0] == 0x02);
    TEST_CHECK(result[8] == 0x03);
    TEST_CHECK_(result[1] == 3, "Incorrect LSB length: %d", result[1]);
    TEST_CHECK_(result[2] == 0, "Incorrect MSB length: %d", result[2]);
    TEST_CHECK_(result[6] == 0x3C, "Incorrect LRC: %#x", result[6]);
    TEST_CHECK_(result[7] == 0xC0, "Incorrect checksum:  %#x", result[7]);

    free(result);
}

void test_pack_payload2()
{
    uint8_t payload[] = {
        0x06, 0x35, 0x33, 0x39, 0x54, 0x30, 0x39, 0x34, 0x35, 0x38, 0x32
    };
    uint8_t *result = NULL;
    unsigned int length = 11;
    uint16_t total_length;

    total_length = pack_payload(payload, &result, length);

    TEST_CHECK_(result != NULL, "Result doesn't point to anything");
    TEST_CHECK_(total_length == 17, "Incorrect length: %d", total_length);
    TEST_CHECK(result[0] == 0x02);
    TEST_CHECK(result[total_length - 1] == 0x03);
    TEST_CHECK_(result[1] == 0x0B, "Incorrect LSB length: %d", result[1]);
    TEST_CHECK_(result[2] == 0, "Incorrect MSB length: %d", result[2]);
    TEST_CHECK_(result[total_length - 3] == 0x6F, "Incorrect LRC: %#x", result[total_length - 3]);
    TEST_CHECK_(result[total_length - 2] == 0x37, "Incorrect checksum:  %#x", result[total_length - 2]);

    free(result);
}

TEST_LIST = {
    { "pack_payload", test_pack_payload },
    { "pack_payload2", test_pack_payload2 },
    { 0 }
};
