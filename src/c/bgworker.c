#include <pebble.h>
#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"


void bgworker_subscribe(void){
  if (!app_worker_is_running()){    // Check to see if the worker is currently active
    AppWorkerResult result = app_worker_launch();   // Launch the background worker
    if ((result == APP_WORKER_RESULT_SUCCESS)|(result == APP_WORKER_RESULT_ASKING_CONFIRMATION)){
      while(!app_worker_is_running()){
        delay_time();
      }
    }
  }
  // initialize worker message
  fgmessage_subscribe();  
}


void bgworker_unsubscribe(void){
  fgmessage_unsubscribe();
}