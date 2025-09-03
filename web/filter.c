#include <emscripten.h>

EMSCRIPTEN_KEEPALIVE
void grayscale(unsigned char* image_data, int width, int height) {
    for (int i = 0; i < width * height * 4; i += 4) {
        unsigned char gray = (image_data[i] + image_data[i + 1] + image_data[i + 2]) / 3;
        
        image_data[i]     = gray;
        image_data[i + 1] = gray;
        image_data[i + 2] = gray;
    }
}