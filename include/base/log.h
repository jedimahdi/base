#ifndef LOG_H_
#define LOG_H_

typedef enum {
  LOG_LEVEL_FATAL = 0,
  LOG_LEVEL_ERROR = 1,
  LOG_LEVEL_WARN = 2,
  LOG_LEVEL_INFO = 3,
  LOG_LEVEL_DEBUG = 4,
  LOG_LEVEL_TRACE = 5
} LogLevel;

void log_output(LogLevel level, const char *file_name, int line,
                const char *format, ...);

#define LOG_FATAL(format, ...) \
  log_output(LOG_LEVEL_FATAL, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
  log_output(LOG_LEVEL_ERROR, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define LOG_WARN(format, ...) \
  log_output(LOG_LEVEL_WARN, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
  log_output(LOG_LEVEL_INFO, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...) \
  log_output(LOG_LEVEL_DEBUG, __FILE__, __LINE__, format, ##__VA_ARGS__)

#define LOG_TRACE(format, ...) \
  log_output(LOG_LEVEL_TRACE, __FILE__, __LINE__, format, ##__VA_ARGS__)

#endif // LOG_H_
