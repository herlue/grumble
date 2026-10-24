#include "grumble.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static grumble_level_t grumble_level = GRUMBLE_LEVEL_INFO;

static const char* plain[] = {
  "[FATAL]",
  "[ERROR]",
  "[WARN ]",
  "[INFO ]"
};

static const char* colored[] = {
  "\033[31m[FATAL]\033[0m ",
  "\033[31m[ERROR]\033[0m ",
  "\033[33m[WARN ]\033[0m ",
  "\033[34m[INFO ]\033[0m "
};

void grumble_set_level(grumble_level_t level) {
  grumble_level = level;
}

void grumble_log(grumble_level_t level, const char* fmt, ...) {
  if (level > grumble_level)
    return;

  fputs(isatty(STDERR_FILENO) ? colored[level] : plain[level], stderr);

  va_list args;
  va_start(args, fmt);

  vfprintf(stderr, fmt, args);

  va_end(args);

  fputc('\n', stderr);

  if (level == GRUMBLE_LEVEL_FATAL)
    exit(EXIT_FAILURE);
}
