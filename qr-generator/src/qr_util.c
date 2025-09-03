#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "../lib/qrcodegen.h"
#include "qr_util.h"

char* create_qr_string(const char *text) {
    uint8_t qrcode[qrcodegen_BUFFER_LEN_MAX];
    uint8_t tempBuffer[qrcodegen_BUFFER_LEN_MAX];

    bool success = qrcodegen_encodeText(text, tempBuffer, qrcode, qrcodegen_Ecc_MEDIUM,
        qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true);

    if (!success) {
        return NULL;
    }

    int size = qrcodegen_getSize(qrcode);
    int border = 4;
    
    // Allocate memory for the output string.
    // (size + 2*border) for width, *2 for block chars, +1 for newline.
    int string_size = ((size + 2 * border) * 2 + 1) * (size + 2 * border) + 1;
    char *result = (char*)malloc(string_size);
    if (result == NULL) return NULL;
    strcpy(result, ""); // Start with an empty string

    for (int y = -border; y < size + border; y++) {
        for (int x = -border; x < size + border; x++) {
            if (qrcodegen_getModule(qrcode, x, y)) {
                strcat(result, "██"); // Append black blocks
            } else {
                strcat(result, "  "); // Append white space
            }
        }
        strcat(result, "\n"); // Append newline at the end of a row
    }
    return result;
}