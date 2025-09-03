#include <emscripten.h>
#include <stdlib.h> // For malloc
#include <stdio.h>  // For sprintf
#include <string.h> // <-- FIX: Added this for strlen()

// C needs to allocate memory for the new string.
EMSCRIPTEN_KEEPALIVE
char* get_greeting(char* name) {
    // Allocate space for "Hello, [name]!" + null terminator
    char* buffer = (char*)malloc(strlen(name) + 10);
    sprintf(buffer, "Hello, %s!", name);
    return buffer;
}