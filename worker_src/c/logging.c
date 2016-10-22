#include <pebble_worker.h>
#include "worker.h"
#include "connectivity.h"
#include "logging.h"
#include "sensing.h"
#include "battery.h"
#include "bgmessage.h"


DataLoggingSessionRef logging_session;
DataLoggingResult logging_result;

static const uint32_t LOG_TAGS = 0x54; 

bool connection_flag;
bool charging_flag;
bool plugged_flag;
bool start_flag;
bool battery_flag;

void check_logging(void){
  // if CONNECTED and NOT PLUGGED IN, start DATA_LOGGING service
  // APP_LOG(APP_LOG_LEVEL_INFO,"In Logging!");
  if (start_flag){
    if (connection_flag){  // && battery_flag
      if (logging_session==NULL){
        logging_session = data_logging_create(LOG_TAGS, DATA_LOGGING_UINT, 4, false);
        delay_time();delay_time();delay_time();delay_time();
      }
      
      sensing_subscribe();
      delay_time();delay_time();delay_time();delay_time();      
      //APP_LOG(APP_LOG_LEVEL_ERROR, "Condition 1");
    }
    else{
      sensing_unsubscribe();
      delay_time();delay_time();delay_time();delay_time();
//       if (logging_session){
//         data_logging_finish(logging_session);
//         //logging_session = NULL;
//         delay_time();delay_time();delay_time();delay_time();
//       }
    }
  }
  else{
    sensing_unsubscribe();
    delay_time();delay_time();delay_time();delay_time();
    if (logging_session){
      data_logging_finish(logging_session);
      //logging_session = NULL;
      delay_time();delay_time();delay_time();delay_time();
    }
  }  
}

void log_data(uint8_t log_num){  
  logging_result = data_logging_log(logging_session, &data_pointer, log_num);
  if (logging_result != DATA_LOGGING_SUCCESS){
    char * log_output;
    switch(logging_result){
      case DATA_LOGGING_SUCCESS: log_output = "LOGGING_SUCCESS"; break;
      case DATA_LOGGING_BUSY: log_output = "LOGGING_BUSY"; break;
      case DATA_LOGGING_NOT_FOUND: log_output = "LOGGING_NOT_FOUND"; break;
      case DATA_LOGGING_FULL: log_output = "LOGGING_FULL"; break;
      case DATA_LOGGING_CLOSED: log_output = "LOGGING_CLOSED"; break;
      case DATA_LOGGING_INTERNAL_ERR: log_output = "LOGGING_INT_ERR"; break;
      case DATA_LOGGING_INVALID_PARAMS: log_output = "LOGGING_INV_PARAM"; break;
      default: log_output = "default"; break;    
    }
    APP_LOG(APP_LOG_LEVEL_ERROR, "%s", log_output);
    //text_layer_set_text(conn_text_layer, log_out);
  }
}


