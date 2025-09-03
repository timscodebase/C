Of course. Here is the text converted into clean, correctly formatted Markdown.

````markdown
# C and WebAssembly Learning Projects

This repository contains a series of C projects that document a learning journey from native command-line applications to modern web development with WebAssembly (Wasm). The projects start with a simple C application and evolve into a high-performance web tool, demonstrating key concepts at each stage.

---
## 🚀 Projects

The two main projects in this repository are a command-line contact manager and a URL-to-QR code generator, both of which have been built for a native terminal environment and ported to the web.

---
### 1. QR Code Generator (`qr-generator`)

A tool that generates QR codes from user-provided text or URLs. This project focuses on integrating a third-party C library and separating C's computational strengths from JavaScript's UI/rendering strengths.

**Key Concepts Demonstrated:**
* **Modular C Design:** Structuring the code into a library (`qr_util.c`) and an application (`main.c`).
* **Third-Party Library Integration:** Using the `qrcodegen` library for the core QR code generation logic.
* **Build Automation:** Using a `Makefile` to manage the multi-file native build process.
* **C-to-JS Communication:** Passing data between JavaScript and C.
* **HTML5 Canvas:** Rendering the QR code data received from Wasm onto a `<canvas>` element for a clean, pixel-perfect display.

#### How to Build and Run

**Native Version (ASCII art in Terminal):**
```bash
# Navigate to the project directory
cd qr-generator

# Compile the project using the Makefile
make

# Run the application with a command-line argument
./qr_generator "[https://github.com/timscodebase](https://github.com/timscodebase)"
````

**WebAssembly Version (Canvas rendering in Browser):**

```bash
# Navigate to the project directory
cd qr-generator

# Compile with Emscripten
emcc src/main.c src/qr_util.c lib/qrcodegen.c -o qr_generator.js -O3 -s EXPORTED_FUNCTIONS='["_generate_qr_data", "_get_qr_size"]' -s EXPORTED_RUNTIME_METHODS='["cwrap"]' -s ALLOW_MEMORY_GROWTH=1

# Start a local web server (requires Python 3)
python3 -m http.server
# or
npx serve

# Open your browser to http://localhost:8000 and select the correct index.html
```

-----

### 2\. Contact Manager (`contacts-cli`)

A terminal-based application for managing a list of contacts. This project served as a foundation for learning core C programming concepts.

**Key Concepts Demonstrated:**

  * **C Fundamentals:** `structs` for data modeling, functions, and control flow.
  * **Dynamic Memory Management:** Using `malloc`, `realloc`, and `free` to manage a list of contacts that can grow in size.
  * **File I/O:** Persisting the contact list to a binary file (`contacts.dat`) using `fopen`, `fwrite`, and `fread`.
  * **WebAssembly Porting:** This project was ported to Wasm, which required a custom HTML/JS "terminal" and advanced Emscripten flags like `ASYNCIFY` and `NO_EXIT_RUNTIME`.

#### How to Build and Run

**Native Version (for macOS Terminal):**

```bash
# Navigate to the project directory
cd contacts-cli

# Compile the native C code
clang main_native.c -isysroot $(xcrun --sdk macosx --show-sdk-path) -o contacts-cli

# Run the application
./contacts-cli
```

**WebAssembly Version (for the Browser):**

```bash
# Navigate to the project directory
cd contacts-cli

# Compile with Emscripten
emcc main_web.c -o contacts.js -s ASYNCIFY -s NO_EXIT_RUNTIME=1

# Start a local web server that sends the required security headers
python3 server.py # (This assumes the custom server.py file is in the directory)
# or
npx serve

# Open your browser to http://localhost:8000
```

-----

## 🛠️ Technologies & Concepts Covered

This repository demonstrates a wide range of skills applicable to both native and web development:

  * **Languages:** C11, JavaScript (ES6+), HTML5
  * **C Fundamentals:** Pointers, memory management, `structs`, file I/O, build systems (`make`).
  * **WebAssembly Tooling:** Emscripten (`emcc`), linker flags (`-s`), exporting functions.
  * **C/Wasm Interaction:** `Module` object, `ccall`/`cwrap`, `EMSCRIPTEN_KEEPALIVE`, direct memory access (`HEAPU8`), and debugging runtime issues.
  * **Web Technologies:** HTML5 Canvas, DOM manipulation, asynchronous loading, and local web servers.

<!-- end list -->

```
```