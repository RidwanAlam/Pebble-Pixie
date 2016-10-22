#ifndef LOG_INCLUDE
#define LOG_INCLUDE
#include <pebble_worker.h>
extern DataLoggingSessionRef logging_session;
extern DataLoggingResult logging_result;

extern bool connection_flag;
extern bool start_flag;
extern bool charging_flag;
extern bool plugged_flag;
extern bool battery_flag;

extern void check_logging(void);
extern void log_data(uint8_t log_num);

#endif

