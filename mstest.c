#include <stdio.h>
#include <stdlib.h>

#include <hidapi/hidapi.h>

#include "protocol.h"

int main()
{
    printf("minismart test tool:\n");

    hid_device *device;

    device = hid_open(0x0ACD, 0x3410, NULL);

    if (device == NULL) {
        printf("Can't open HID device.\n");
        exit(1);
    }

    hid_close(device);

    return 0;
}


