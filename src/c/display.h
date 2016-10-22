#ifndef DISPLAY_INCLUDE
#define DISPLAY_INCLUDE
#include <pebble.h>

extern TextLayer *s_date_layer;
extern TextLayer *s_time_layer;
extern TextLayer *s_battery_layer;

extern void display_subscribe();
extern void display_unsubscribe();

#endif
