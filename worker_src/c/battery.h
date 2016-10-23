#ifndef BATTERY_INCLUDE
#define BATTERY_INCLUDE
#include <pebble_worker.h>

extern BatteryChargeState battery_charge;
extern bool battery_flag;

extern void battery_subscribe(void);
extern void battery_unsubscribe(void);

#endif

