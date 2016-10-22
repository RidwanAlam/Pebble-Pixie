#include <pebble_worker.h>
#include "worker.h"
#include "connectivity.h"
#include "logging.h"
#include "sensing.h"
#include "battery.h"
#include "bgmessage.h"

// Used to identify the source of a message
#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1

bool app_flag;

void bgworker_message_handler(uint16_t type,AppWorkerMessage *messageData) {
  // Get the data, only if it was sent from the foreground
  if(type == SOURCE_FOREGROUND) {  
    //APP_LOG(APP_LOG_LEVEL_WARNING,"MSG RCVD by BG!");
    app_flag = ((messageData->data0 == 1)?true:false);
    APP_LOG(APP_LOG_LEVEL_WARNING,(app_flag?"Flag=True":"Flag=False"));
    if (app_flag){
      send_message(battery_state_service_peek());
    }
  }
}

void send_message(BatteryChargeState battery_charge_1){
  // Construct a message to send
  AppWorkerMessage messageData = {
    .data0 = (uint16_t) (battery_charge_1.charge_percent & 0x00ff),
    .data1 = (uint16_t) (battery_charge_1.is_charging?1:0),
    .data2 = (uint16_t) (battery_charge_1.is_plugged?1:0)
  };
  // Send the data to the background app
  app_worker_send_message(SOURCE_BACKGROUND, &messageData);
  //APP_LOG(APP_LOG_LEVEL_WARNING, "BATT SENT!");
}


void bgmessage_subscribe(){
  app_worker_message_subscribe(bgworker_message_handler);
  app_flag = true;
}

void bgmessage_unsubscribe(void){
  app_worker_message_unsubscribe();
}