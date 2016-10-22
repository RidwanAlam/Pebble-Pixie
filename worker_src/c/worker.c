#include <pebble_worker.h>
#include "worker.h"
#include "connectivity.h"
#include "logging.h"
#include "sensing.h"
#include "battery.h"
#include "bgmessage.h"

#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1


void delay_time(void){
  uint16_t t = (2 ^ 16) - 1;
  while(t>0){t--;}
}


static void prv_init() {
  
  // Initialize MESSAGE
  bgmessage_subscribe();
  // Initialize CONNECTIVITY
  bt_subscribe();  
  // Initialize BATTERY
  battery_subscribe();
  
  // Start Data Collection
  start_flag = true;
  check_logging();
  
}

static void prv_deinit() {
  
  // Stop Data Collection
  start_flag = false;
  check_logging();
  // Deinitialize CONNECTIVITY
  bt_unsubscribe();
  // Deinitialize SENSING
  sensing_unsubscribe();
  // Deinitialize BATTERY
  battery_unsubscribe();
  // Deinitialize MESSAGE
  bgmessage_unsubscribe();
  
  APP_LOG(APP_LOG_LEVEL_ERROR, "Stopped!");
  
}

int main(void) {
  prv_init();
  worker_event_loop();
  prv_deinit();
}