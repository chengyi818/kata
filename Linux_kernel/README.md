# Linux Kernel Kata

This repository contains various examples and exercises for learning Linux Kernel internals, APIs, and data structures.

## Structure

### 1. Crypto API Examples (`crypto/`)

Examples demonstrating how to use the Linux Crypto API from both kernel space and user space.

*   **Kernel Space** (`crypto/kernel_example/`):
    *   `hash/`: A simple kernel module demonstrating how to allocate and use a SHA1 hash transform using `crypto_alloc_hash` and related functions.

*   **User Space** (`crypto/userspace_example/`):
    *   Demonstrates usage of the `AF_ALG` socket interface to access kernel cryptographic primitives from userspace.
    *   Includes examples for:
        *   Symmetric encryption (AES-CBC)
        *   Hashing (SHA)
        *   AEAD (Authenticated Encryption)

### 2. List Head (`list_head/`)

An extraction/implementation of the Linux Kernel's standard doubly linked list data structure (`struct list_head`) for userspace usage.

*   Includes implementation of standard macros like:
    *   `container_of`
    *   `list_entry`
    *   `list_for_each`

### 3. Process Scheduler (`process_schedue/`)

A study project implementing/simulating core Linux process scheduling concepts.

*   **Key Concepts Implemented**:
    *   `task_struct` (Process Descriptor)
    *   `runqueue` (Per-CPU run queue)
    *   Scheduler ticks and time slices
    *   Process states and priorities

## Usage

Each subdirectory typically contains a `Makefile`. You can build the examples by navigating to the directory and running `make`.

*   **Kernel Modules**: Requires kernel headers installed (`linux-headers-$(uname -r)`).
*   **Userspace Programs**: Standard GCC toolchain.

## License

See individual files for license information.

