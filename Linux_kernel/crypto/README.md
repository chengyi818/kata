# Linux Crypto API Examples

This directory contains examples demonstrating how to use the Linux Kernel Crypto API from both kernel space (modules) and user space (via AF_ALG).

## Directory Structure

### 1. Kernel Space Examples (`kernel_example/`)

Examples of how to write kernel modules that utilize the kernel's cryptographic transforms.

*   **`hash/`**:
    *   Demonstrates allocating and using a message digest (SHA1).
    *   Key APIs: `crypto_alloc_hash`, `crypto_hash_init`, `crypto_hash_update`, `crypto_hash_final`.

### 2. User Space Examples (`userspace_example/`)

Examples of how to access the kernel's cryptographic implementations from user space programs using the `AF_ALG` socket interface.

*   **Features**:
    *   `basic_cipher`: Symmetric key cipher usage (e.g., AES-CBC).
    *   `basic_hash`: Hashing usage.
    *   `basic_aead`: Authenticated Encryption with Associated Data.
    *   `stream_hash`: Streaming data for hashing.
    *   `multi_connections`: Managing multiple crypto requests concurrently.

*   See the `userspace_example/README.md` for more detailed information on specific examples.


