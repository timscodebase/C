#include <stdio.h>
#include <stdlib.h>
#include "qr_util.h"

// Note: In the Wasm version, JavaScript will call our functions directly.
// The main() function isn't strictly necessary for the final product,
// but we keep it here to ensure the code compiles.
int main() {
    // We'll pass the text from JavaScript in the final version.
    const char* text = "Hello from Wasm!";
    char* qr_string = create_qr_string(text);
    if (qr_string != NULL) {
        printf("%s\n", qr_string);
        free(qr_string); // Clean up memory
    }
    return 0;
}