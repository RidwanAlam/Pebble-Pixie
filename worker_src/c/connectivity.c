#include <pebble_worker.h>
#include "worker.h"
#include "connectivity.h"
#include "logging.h"
#include "sensing.h"
#include "battery.h"
#include "bgmessage.h"




void bt_handler(bool connected) {
  
  // Show current connection state
  if (connected) {
	  //APP_LOG(APP_LOG_LEVEL_INFO, "Connected!");
    connection_flag = true;    
    check_logging(); 
  }
  else{
    connection_flag = false;
    check_logging();
  }
}


void bt_subscribe(){
  connection_service_subscribe((ConnectionHandlers) {
    .pebble_app_connection_handler = bt_handler
  });
  
  if (connection_service_peek_pebble_app_connection()){
    connection_flag = true;
    //APP_LOG(APP_LOG_LEVEL_INFO, "BT INIT!");
  }
}


void bt_unsubscribe(){
  connection_service_unsubscribe();
}


