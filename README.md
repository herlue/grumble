# Grumble

A minimal C logging library for POSIX systems. Requires a C99-capable compiler;
CMake builds require CMake 3.16 or newer.

## Usage

```c
#include "grumble.h"

int main(void) {
    grumble_log(GRUMBLE_LEVEL_INFO, "Hello, %s!", "world");

    grumble_set_level(GRUMBLE_LEVEL_WARN);
    grumble_log(GRUMBLE_LEVEL_INFO, "This message is filtered out.");
    grumble_log(GRUMBLE_LEVEL_ERROR, "Could not open %s", "config.txt");
    return 0;
}
```

- Levels, from most to least severe: `FATAL`, `ERROR`, `WARN`, `INFO`
  (each prefixed with `GRUMBLE_LEVEL_`). The default threshold is `INFO`.
- `grumble_set_level()` sets the global threshold: only that level and more
  severe messages are emitted.
- `grumble_log()` accepts a `printf`-style format string and arguments. It writes
  a level prefix and message to `stderr`, adding a newline automatically.
- Prefixes use ANSI colors when `stderr` is a terminal; redirected output is plain.
- **`GRUMBLE_LEVEL_FATAL` logs the message and calls `exit(EXIT_FAILURE)`.**

## Build and integration

Build the static library:

```sh
cmake -S . -B build
cmake --build build
```

To use Grumble in a CMake project, place it in `external/grumble` and link your
existing executable target:

```cmake
add_subdirectory(external/grumble)
target_link_libraries(my_app PRIVATE grumble::grumble)
```

The target provides the public include directory automatically. Alternatively,
compile `src/grumble.c` alongside your own sources with `include` on the include path:

```sh
cc -std=c99 -Iexternal/grumble/include main.c external/grumble/src/grumble.c -o my_app
```

## Limitations

- POSIX only (`unistd.h` and `isatty`); no native Windows support.
- No internal thread synchronization. Concurrent reads and writes of the global
  threshold cause a data race. Set it before starting threads and leave it unchanged,
  or synchronize all logging and level changes externally. Even with a fixed
  threshold, concurrent log calls can interleave parts of their output; use a shared
  mutex around whole calls if complete lines must stay together.
- Level arguments must be one of the declared enum constants; invalid values are
  not checked and may cause undefined behavior. Format strings must be non-null
  and valid, with matching arguments as required by `printf`.
- No install or `find_package()` support is currently provided.
- No license has been specified in this repository yet.
