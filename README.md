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

### Windows
-   A Visual Studio solution (`.sln`) is provided.
-   Open it in Visual Studio 2022 or later.
-   In Project Properties -> General, set the **Target Name** to `bcrypt_amxx`.
-   Set the build configuration to **Release | Win32**.
-   Build the solution. The output DLL will be in the `Release` directory.

### Linux
-   A `Makefile` is provided.
-   Ensure you have `g++` and `make` installed (and `g++-multilib` if on a 64-bit system).
-   Navigate to the project root directory and run:

    ```bash
    make
    ```
-   This will produce the `bcrypt_amxx_i386.so` binary.