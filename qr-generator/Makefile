# Compiler
CC = clang

# --- THE FIX IS HERE ---
# Automatically find the path to the macOS SDK
SDKROOT = $(shell xcrun --sdk macosx --show-sdk-path)

# Compiler flags. We add the -isysroot flag to point to the SDK.
CFLAGS = -std=c11 -Wall -Wextra -O2 -isysroot $(SDKROOT)

# Source files
SRCS = src/main.c src/qr_util.c lib/qrcodegen.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# The final executable name
TARGET = qr_generator

# Default target: build the executable
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile a .c file into a .o file
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to clean up build files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean