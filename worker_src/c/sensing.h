#ifndef SENSING_INCLUDE
#define SENSING_INCLUDE
#include <pebble_worker.h>
extern uint32_t data_pointer[];

extern void sensing_subscribe();
extern void sensing_unsubscribe();
extern void accel_data_handler();
extern void print_screen();

#endif

