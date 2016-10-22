#include <pebble.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"



static void init() {    

  // Initialize TIMER
  timer_subscribe();
  
  // Initialize DISPLAY
  display_subscribe();
  
  // Initialize WORKER
  bgworker_subscribe();

}

static void deinit() {
  
  // Send app_flag
  send_fgmessage(false);
  // Deinitialize TIMER
  timer_unsubscribe();
  // Deinitialize DISPLAY
  display_unsubscribe();
  // Deinitialize WORKER
  bgworker_unsubscribe();
  
}

int main(void) {  
  init();
  app_event_loop();
  deinit();
}

