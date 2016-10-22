#include <pebble.h>
#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"

// Used to identify the source of a message
#define SOURCE_FOREGROUND 0
#define SOURCE_BACKGROUND 1

void fgmessage_handler(uint16_t type,AppWorkerMessage *messageData) {
  // Get the data, only if it was sent from the background
  if(type == SOURCE_BACKGROUND) {  
    battery_charge.charge_percent = (uint8_t) (messageData->data0);
    battery_charge.is_charging = ((messageData->data1 == 1)?true:false);
    battery_charge.is_plugged = ((messageData->data2 == 1)?true:false);
    
    battery_display();
  }
}

void send_fgmessage(bool flag){
  // Construct a message to send
  AppWorkerMessage messageData = {
    .data0 = (uint16_t) (flag?1:0)
  };
  // Send the data to the background app
  app_worker_send_message(SOURCE_FOREGROUND, &messageData);
  //APP_LOG(APP_LOG_LEVEL_WARNING,"MSG SENT!");
}

void fgmessage_subscribe(void){
  app_worker_message_subscribe(fgmessage_handler);
  send_fgmessage(true);
}

void fgmessage_unsubscribe(void){
  app_worker_message_unsubscribe();
}