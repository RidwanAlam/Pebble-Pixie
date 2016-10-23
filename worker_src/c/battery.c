#include <pebble_worker.h>
#include "worker.h"
#include "connectivity.h"
#include "logging.h"
#include "sensing.h"
#include "battery.h"
#include "bgmessage.h"


BatteryChargeState battery_charge;
bool battery_flag;

void battery_handler(BatteryChargeState battery_charge_1) {
  battery_charge = battery_charge_1;
  if (app_flag){
    send_message(battery_charge_1);
  }
  bool temp = plugged_flag;
  charging_flag = battery_charge.is_charging;
  plugged_flag = battery_charge.is_plugged;
  if ((temp==false) && (plugged_flag==true)){
    APP_LOG(APP_LOG_LEVEL_WARNING,"PLUGGED IN!");
    battery_flag = false;
    check_logging();
  }
  else if ((temp==true) && (plugged_flag==false)){
    APP_LOG(APP_LOG_LEVEL_WARNING,"UNPLUGGED!");
    battery_flag = true;
    check_logging();
  }
}

void battery_subscribe(){
  battery_state_service_subscribe(battery_handler);
  battery_charge = battery_state_service_peek();
  charging_flag = battery_charge.is_charging;
  plugged_flag = battery_charge.is_plugged;
  battery_flag = (plugged_flag?false:true);
  battery_handler(battery_charge);
}

void battery_unsubscribe(){
  battery_state_service_unsubscribe();
}
