#include <emscripten.h>

// This macro makes the function visible to JavaScript
EMSCRIPTEN_KEEPALIVE
void generate_mandelbrot(unsigned char* image_buffer, int width, int height, int max_iterations) {
    // Iterate over each pixel in the image
    for (int py = 0; py < height; py++) {
        for (int px = 0; px < width; px++) {
            // Map the pixel coordinates to the complex plane
            double x0 = (px - width / 2.0) * 4.0 / width;
            double y0 = (py - height / 2.0) * 4.0 / height;

            double x = 0.0;
            double y = 0.0;
            int iteration = 0;

            // The core Mandelbrot set calculation
            while (x * x + y * y <= 4.0 && iteration < max_iterations) {
                double xtemp = x * x - y * y + x0;
                y = 2 * x * y + y0;
                x = xtemp;
                iteration++;
            }

            // Determine the color based on how many iterations it took to escape
            int index = (py * width + px) * 4; // Each pixel has 4 bytes (R, G, B, A)
            unsigned char color = (iteration == max_iterations) ? 0 : (255 * iteration) / max_iterations;

            image_buffer[index] = color;        // Red
            image_buffer[index + 1] = color / 2;  // Green (for a fiery look)
            image_buffer[index + 2] = 0;          // Blue
            image_buffer[index + 3] = 255;      // Alpha (fully opaque)
        }
    }
}