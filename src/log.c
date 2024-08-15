#include "log.h"

#include <stdarg.h>
#include <stdio.h>

void log_output(LogLevel level, const char *file_name, int line,
                const char *format, ...) {
  const char *level_strs[6] = {"[FATAL]", "[ERROR]", "[WARN]",
                               "[INFO]",  "[DEBUG]", "[TRACE]"};

  fprintf(stderr, "[%s:%d] %s ", file_name, line, level_strs[level]);
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fprintf(stderr, "\n");
}
