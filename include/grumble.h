#ifndef GRUMBLE_H
#define GRUMBLE_H

typedef enum grumble_level {
  GRUMBLE_LEVEL_FATAL,
  GRUMBLE_LEVEL_ERROR,
  GRUMBLE_LEVEL_WARN,
  GRUMBLE_LEVEL_INFO
} grumble_level_t;

void grumble_set_level(grumble_level_t);
void grumble_log(grumble_level_t, const char*, ...);

#endif
