# AMXX Bcrypt Module

This is a simple AMX Mod X module that provides native functions for hashing and verifying passwords using the **bcrypt** algorithm. This is much more secure than the commonly used MD5 or SHA algorithms for password storage.

This module uses the C++ bcrypt implementation from [hilch/Bcrypt.cpp](https://github.com/hilch/Bcrypt.cpp).

## Natives

### `native bcrypt_hash(const password[], cost_factor, hash_output[], output_len);`

Hashes a password string using bcrypt.

-   **password**: The plain-text password to hash.
-   **cost_factor**: The work factor for the algorithm. Higher numbers are more secure but slower. A value between **8** and **12** is recommended.
-   **hash_output**: The string buffer to store the resulting hash.
-   **output_len**: The maximum size of the `hash_output` buffer. **Must be at least 61.**
-   **Returns**: `1` on success, `0` on failure.

### `native bool:bcrypt_check(const password[], const hash[]);`

Verifies a plain-text password against a bcrypt hash.

-   **password**: The plain-text password to check.
-   **hash**: The bcrypt hash to check against.
-   **Returns**: `true` if the password matches the hash, `false` otherwise.

## Installation

1.  Download the latest release from the [Releases](https://github.com/Drakunovu/bcrypt/releases) page.
2.  Choose the correct binary for your server's operating system:
    -   `bcrypt_amxx.dll` for **Windows**
    -   `bcrypt_amxx_i386.so` for **Linux**
3.  Place the binary in your server's `amxmodx/modules/` directory.
4.  Open `amxmodx/configs/modules.ini` and add the following line:
   
    ```
    bcrypt
    ```

## For developers (Scripting)

1.  Copy the `bcrypt.inc` file to your `amxmodx/scripting/include/` directory.
2.  Include it in your script with `#include <bcrypt>`.

## Building from Source

This project uses CMake to build on both Windows and Linux.

### Prerequisites

* [Git](https://git-scm.com/)
* [CMake](https://cmake.org/download/) (3.10 or higher)
* **Windows**: [Visual Studio 2017](https://visualstudio.microsoft.com/vs/older-downloads/) or later (with "Desktop development with C++" workload)
* **Linux**: `g++-multilib` and `build-essential` (`sudo apt-get install g++-multilib build-essential cmake`)
### Steps

1.  **Clone the repository and submodules:**
    ```bash
    git clone [https://github.com/Drakunovu/bcrypt.git](https://github.com/Drakunovu/bcrypt.git)
    cd bcrypt
    git submodule update --init --recursive
    ```

2.  **Configure with CMake:**

    * **On Windows (for 32-bit DLL):**
        ```bash
        cmake -B build -G "Visual Studio 17 2022" -A Win32
        ```
        *(Adjust "Visual Studio 17 2022" to your VS version if needed)*

    * **On Linux (for 32-bit .so):**
        ```bash
        cmake -B build -DCMAKE_BUILD_TYPE=Release
        ```

3.  **Build the module:**
    ```bash
    cmake --build build --config Release
    ```

4.  **Find the binary:**
    * **Windows:** `build/Release/bcrypt_amxx.dll`
    * **Linux:** `build/bcrypt_amxx_i386.so`