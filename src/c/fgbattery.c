#include <pebble.h>
#include "display.h"
#include "clicks.h"
#include "timer.h"
#include "fgbattery.h"
#include "fgmessage.h"
#include "bgworker.h"

BatteryChargeState battery_charge;

void battery_display() {
  static char battery_text[] = "----";

  if (battery_charge.is_charging) {
    snprintf(battery_text, sizeof(battery_text), ">>>>");
  } else if (battery_charge.is_plugged) {
    snprintf(battery_text, sizeof(battery_text), "||||");
  } else {
    snprintf(battery_text, sizeof(battery_text), "%d%%", battery_charge.charge_percent);
  }
  text_layer_set_text(s_battery_layer, battery_text);
}




