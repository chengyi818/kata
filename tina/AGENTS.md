# AGENTS.md — tina (C practice)

## Build & run
Each `.c` file is a standalone program. Compile individually:

    gcc -std=c99 -Wall -o <name> <name>.c && ./<name>

No Makefile, no CMake, no shared headers.

## Known issues
- `SeqStack.c` — uses `bool` without `#include <stdbool.h>`; also calls `numJewelsInStones()` (defined in `test.c`). This file is incomplete.
- `printTest.c` — exploration-only (scanf/gets/getchar patterns), contains duplicated copy-paste blocks. Do not treat as a module.
- `MaxPathGame` is a precompiled binary; source is `MaxPathGame.c`.

## Testing
No test suite exists for any file.
