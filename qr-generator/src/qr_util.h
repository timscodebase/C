#ifndef QR_UTIL_H
#define QR_UTIL_H

#include <stdbool.h>

// Generates a QR code and returns it as a string of ASCII art.
// The caller is responsible for freeing the returned string's memory.
char* create_qr_string(const char *text);

#endif