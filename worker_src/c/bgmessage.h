#ifndef BGMESSAGE_INCLUDE
#define BGMESSAGE_INCLUDE
#include <stdbool.h>
#include <pebble_worker.h>


extern void bgmessage_subscribe();
extern void bgmessage_unsubscribe();
extern bool app_flag;
extern void send_message(BatteryChargeState battery_charge);

#endif